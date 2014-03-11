/**
 ** \file object/desugar-visitor.cc
 ** \brief Implementation of object::DesugarVisitor.
 */

#include <sstream>

#include <misc/symbol.hh>

#include <ast/all.hh>
#include <parse/libparse.hh>
#include <parse/tweast.hh>
#include <type/function.hh>
#include <type/record.hh>
#include <type/class.hh>
#include <object/desugar-visitor.hh>

namespace object
{
  DesugarVisitor::DesugarVisitor(const class_names_type& names)
    : super_type()
    , class_names_(names)
    , types_()
    , class_ids_()
  {
  }

  DesugarVisitor::~DesugarVisitor()
  {
  }


  /*---------------------------.
  | Handling names and types.  |
  `---------------------------*/

  namespace
  {
    // Desugar prefixes.

    // Prefix of every class id (label).
    const char* class_id_prefix = "_id_";
    // Prefix of every record holding the contents of a desugared class.
    const char* class_contents_prefix = "_contents_";
    // Prefix of every variant storing the possible dynamic type for
    // a given static type.
    const char* class_variant_prefix = "_variant_";
    // Prefix of the fields in the variant.
    const char* variant_field_prefix = "field_";
    // Prefix of constructors.
    const char* class_ctor_prefix = "_new_";
    // Prefix of methods.
    const char* method_prefix = "_method_";


    // Useful routines.

    // Try to get the class type of \a t.  If \a t has is not a class
    // type, return a null pointer.
    const type::Class*
    class_type_query(const ast::Typable& t)
    {
      const type::Type* type = &t.type_get()->actual();
      return dynamic_cast<const type::Class*>(type);
    }

    // Like class_type_query, but ensure the type is actually a class.
    const type::Class*
    class_type_get(const ast::Typable& t)
    {
      const type::Class* class_type = class_type_query(t);
      postcondition(class_type);
      return class_type;
    }
  }


  /*------------------.
  | Code generation.  |
  `------------------*/

  std::string
  DesugarVisitor::type_symbol(const type::Type* type)
  {
    if (type == &type::Int::instance())
      return "int";
    else if (type == &type::String::instance())
      return "string";
    else
      {
        auto named = dynamic_cast<const type::Named*>(type);
        // If the actual type is a class, use its new name.
        auto class_type = dynamic_cast<const type::Class*>(&named->actual());
        if (class_type)
          return std::string(class_variant_prefix)
                 + class_names_.operator()(class_type).name_get();
        // Otherwise, simply return the name.
        return named->name_get();
      }
  }

  std::string
  DesugarVisitor::upcast_fun_name(const type::Class* from,
                                  const type::Class* to)
  {
    std::stringstream s;
    s << "_upcast_" << class_names_(from) << "_to_" << class_names_(to);
    return s.str();
  }

  std::string
  DesugarVisitor::downcast_fun_name(const type::Class* from,
                                    const type::Class* to)
  {
    std::stringstream s;
    s << "_downcast_" << class_names_(from) << "_to_" << class_names_(to);
    return s.str();
  }

  std::string
  DesugarVisitor::dispatch_fun_name(const type::Class* owner,
                                    const type::Method* method)
  {
    std::stringstream s;
    s << "_dispatch_" << class_names_(owner) << "_" << method->name_get();
    return s.str();
  }


  void
  DesugarVisitor::adapt_type(ast::Exp*& source_exp,
                             const type::Class* source_type,
                             const type::Class* target_type)
  {
    // If the source type is different from the target type, (up)cast
    // the source expression to the latter.
    if (source_type && target_type && source_type != target_type)
      source_exp = parse::parse(parse::Tweast()
                                << upcast_fun_name(source_type, target_type)
                                << " (" << source_exp << ")");
  }

  ast::Exp*
  DesugarVisitor::variant_exp(const type::Class* static_type,
                              const std::string& exact_type,
                              const field_inits_type& inits)
  {
    parse::Tweast input;
    misc::symbol static_type_name = class_names_(static_type);
    input <<
          " " << class_variant_prefix << static_type_name <<
          " {"
          "   exact_type = " << exact_type;
    /* For each field of the variant, store the corresponding
       initialization value if one was given, otherwise set the field
       to `nil'.  */
    // Fields of the static type.
    for (const type::Class* c = static_type; c; c = c->super_get())
      // Don't generate slots for classes with no data.
      if (c->has_data())
        {
          input << ",\n"
                << variant_field_prefix << class_names_(c) << " = ";
          // These fields must have a value (we don't need to an
          // assertion here, misc::map::operator() already handles this.
          std::string init = inits.operator()(c);
          input << init;
        }
    // Potential fields of the dynamic type (from subclasses of the
    // static type).
    for (const type::Class* subclass : static_type->subclasses_get())
      // Don't generate slots for classes with no data.
      if (subclass->has_data())
        {
          input << ",\n"
                << variant_field_prefix << class_names_(subclass) << " = ";
          // These fields might be nil.
          field_inits_type::const_iterator i = inits.find(subclass);
          if (i != inits.end())
            input << i->second;
          else
            input << "nil";
        }
    input
        << " }\n";
    return parse::parse(input);
  }

  // Syntactic sugar.
  ast::Exp*
  DesugarVisitor::variant_exp(const type::Class* static_type,
                              const type::Class* dynamic_type,
                              const field_inits_type& inits)
  {
    std::string exact_type =
      class_id_prefix + class_names_(dynamic_type).name_get();
    return variant_exp(static_type, exact_type, inits);
  }

  // Desugar a class type as a variant (record) type.
  parse::Tweast*
  DesugarVisitor::variant_ty(const type::Class* class_type)
  {
    auto input = new parse::Tweast;
    *input
        << " {"
        << "   exact_type : int";
    // Actual data slots.
    /* First, populate the variant with mandatory fields (always non
       nil) starting with the type of the visited class, then super
       classes.  */
    for (const type::Class* c = class_type; c; c = c->super_get())
      // Don't generate slots for classes with no data.
      if (c->has_data())
        {
          misc::symbol class_name = class_names_(c);
          *input << ",\n"
                 << "   " << variant_field_prefix << class_name << " : "
                 << "   " << class_contents_prefix << class_name;
        }
    /* Then add all subclass types.  These might be nil, according to
       the exact type of the object.  */
    for (const type::Class* subclass : class_type->subclasses_get())
      // Don't generate slots for classes with no data.
      if (subclass->has_data())
        {
          misc::symbol subclass_name = class_names_(subclass);
          *input << ",\n"
                 << "   " << variant_field_prefix << subclass_name << " : "
                 << "   " << class_contents_prefix << subclass_name;
        }
    *input << " }\n";
    return input;
  }

  parse::Tweast*
  DesugarVisitor::cast_function(const std::string& name,
                                const type::Class* source,
                                const type::Class* target,
                                const type::Class* exact_type)
  {
    auto input = new parse::Tweast;
    *input <<
           " function " << name <<
           "   (source : " << class_variant_prefix << class_names_(source) << ") :"
           "   " << class_variant_prefix << class_names_(target) << " = ";


    // Copy all fields from the source.
    field_inits_type inits;
    // First, fields from the class and it super classes...
    for (const type::Class* c = source; c; c = c->super_get())
      // Populate the initialization list with classes
      // owning actual data only.
      if (c->has_data())
        {
          std::string field_name = class_names_(c);
          misc::put(inits, c,
                    std::string("source.")
                    + variant_field_prefix + field_name);
        }
    // ...then, fields from the subclasses.
    for (const type::Class* c : source->subclasses_get())
      // Populate the initialization list with classes
      // owning actual data only.
      if (c->has_data())
        {
          std::string field_name = class_names_(c);
          misc::put(inits, c,
                    std::string("source.")
                    + variant_field_prefix + field_name);
        }
    *input << variant_exp(target, exact_type, inits) << "\n";
    return input;
  }

  parse::Tweast*
  DesugarVisitor::upcast_function(const type::Class* source,
                                  const type::Class* target)
  {
    return cast_function(upcast_fun_name(source, target),
                         source, target,
                         source);
  }

  parse::Tweast*
  DesugarVisitor::downcast_function(const type::Class* source,
                                    const type::Class* target)
  {
    return cast_function(downcast_fun_name(source, target),
                         source, target,
                         target);
  }

  ast::Exp*
  DesugarVisitor::dispatch_switch(const type::Class* class_type,
                                  const type::Method* method)
  {
    parse::Tweast input;
    misc::symbol method_name = method->name_get();
    const ast::MethodDec* def = method->def_get();
    const ast::VarDecs::Ds& formals = def->formals_get().decs_get();

    // Create a case for each method redefinition.
    classes_type overridings;
    const classes_type& subclasses = class_type->subclasses_get();
    for (const type::Class* c : subclasses)
      if (c->owned_meth_find(method_name))
        overridings.push_back(c);

    if (overridings.empty())
      // No dispatch is needed; simply call the method.
      input << method_call(class_names_(class_type), method_name,
                           "self", formals);
    else
      {
        /* FIXME: This switch implementation is naive: the search for
           the right target is linear.  Make it logarithmic using a
           dichotomous search. */
        // Emit code for self.
        input << "if self.exact_type = "
              << class_id_prefix << class_names_(class_type) << " then "
              << method_call(class_names_(class_type), method_name,
                             "self", formals);
        // Emit code for other types.
        classes_type::const_iterator c = overridings.begin();
        classes_type::const_iterator c_next = overridings.begin();
        ++c_next;
        for (/* Nothing */; c != overridings.end(); ++c)
          {
            input << " else ";
            // Don't issue a test for the last case.
            if (c_next != overridings.end())
              {
                input << " if self.exact_type = "
                      << class_id_prefix << class_names_(*c) << " then ";
                ++c_next;
              }
            input
                << method_call(class_names_(*c), method_name,
                               downcast_fun_name(class_type, *c) + " (self)",
                               formals);
          }
      }
    input << "\n";
    return parse::parse(input);
  }

  parse::Tweast*
  DesugarVisitor::method_call(const misc::symbol& class_name,
                              const misc::symbol& method_name,
                              const std::string& target,
                              const ast::VarDecs::Ds& formals)
  {
    auto input = new parse::Tweast;
    *input << method_prefix << class_name << "_" << method_name << " (";
    // Pass the target.
  // FIXME: Some code was deleted here.
    // Pass other arguments.
  // FIXME: Some code was deleted here.
    *input << ")";
    return input;
  }



  /*------------------------.
  | Visiting declarations.  |
  `------------------------*/

  void
  DesugarVisitor::operator()(const ast::DecsList& e)
  {
    const ast::Location& location = e.location_get();
    // This is an inlined and specialized version of
    // astclone::Cloner::recurse_collection.  Maybe we could factor
    // it, but it's not easy to see whether we could benefit from
    // this.  (Maybe a variant would be appropriate.)
    ast::DecsList::decs_type contents;
    for (const ast::Decs* d : e.decs_get())
      {
        d->accept(*this);
        // The result can be either an ast::Decs* or an ast::DecsList*.
        auto decs = dynamic_cast<ast::Decs*>(result_);
        if (decs)
          contents.push_back(decs);
        else
          {
            auto decslist = dynamic_cast<ast::DecsList*>(result_);
            if (decslist)
              {
                contents.splice(contents.end(), decslist->decs_get());
                delete decslist;
              }
            else
              abort();
          }
      }
    result_ = new ast::DecsList(location, contents);
  }

  /*-----------------------------.
  | Desugar class declarations.  |
  `-----------------------------*/

  /* All type-related code is emitted into the top-level decs-list, so
     that all classes are stored in the same typedecs, allowing them
     to see their subclasses and be able to build a variant for each
     of them.  */
  void
  DesugarVisitor::operator()(const ast::TypeDecs& e)
  {
    parse::Tweast functions;
    for (const ast::TypeDec* t : e.decs_get())
      {
        /* If this is a declaration of a class, then remove it and
           replace it with

           (1) a class type label (integer constant),
           (2) new data structures:
               - an actual structure holding the data of the class,
               - a variant able to store any concrete type for this
                 class;
           (3) new functions:
               - a constructor,
               - conversion routines used in polymorphic assignments (upcasts),
               - conversion routines used in dynamic dispatch (downcasts),
               - (desugared) methods,
               - dispatch functions.

           We must take care of the order in which these declarations
           are injected, since (1), (2) and (3) are declaration of
           different kinds (variable, type and function respectively).
           Mixing them would break the block of type declarations
           (TypeDecs, or ``chunk'' of TypeDec's) being currently
           visited.  Thus we collect all class definitions from E,
           replace them by new data structures ((2)) and inject the
           rest of the new material *after* the TypeDecs ((1) and
           (3)).  */
        const type::Class* class_type = class_type_query(*t);
        if (class_type)
          {
            misc::symbol class_name = class_names_(class_type);

            /*---------------------------.
            | Introduce a new class id.  |
            `---------------------------*/

            class_ids_ << " var " << class_id_prefix << class_name
                       << " := " << class_type->id_get() << "\n";

            /*----------------------------------------------------.
            | Create a record holding the actual class contents.  |
            `----------------------------------------------------*/

            if (class_type->has_data())
              {
                types_
                    << " type " << class_contents_prefix << class_name << " ="
                    << " { ";
  // FIXME: Some code was deleted here (Populate the record with attributes (names and types)).
                types_ << " }\n";
              }

            /*------------------------------------------------.
            | Create a variant able to store any dynamic type |
            | corresponding to this (static) class type.      |
            `------------------------------------------------*/

            types_
                << " type " << class_variant_prefix << class_name << " ="
                << variant_ty(class_type);

            /*-----------------------.
            | Create a constructor.  |
            `-----------------------*/

            functions <<
                      " function " << class_ctor_prefix << class_name << " () : "
                      " " << class_variant_prefix << class_name << " = "
                      " let";
            // Initialize each mandatory field of the variant (i.e.,
            // the fields holding the attributes of the classes and
            // its super classes).
            for (const type::Class* c = class_type; c; c = c->super_get())
              if (c->has_data())
                {
                  functions
                      << " var contents_" << class_names_(c) << " := "
                      << " " << class_contents_prefix << class_names_(c)
                      << " { ";
                  bool is_first_attr_p = true;
                  for (const type::Attribute& a : c->attrs_get())
                    {
                      if (is_first_attr_p)
                        is_first_attr_p = false;
                      else
                        functions << ", ";
                      const ast::VarDec* attr = a.def_get();
                      misc::symbol attr_name = attr->name_get();
                      // Partially clone the contents of the VarDec
                      // (cloning the whole VarDec would leak memory).
                      ast::Exp* attr_init = recurse(attr->init_get());
                      // Cast the initialization value if needed.
                      if (attr->init_get() && attr->type_name_get())
                        adapt_type(attr_init,
                                   class_type_query(*attr->init_get()),
                                   class_type_query(*attr->type_name_get()));
                      functions << attr_name << " = " << attr_init;
                    }
                  functions << " } ";
                }
            functions << " in ";
            // Create a list of initializations for each field of the
            // variant being constructed.
            field_inits_type inits;
            for (const type::Class* c = class_type; c; c = c->super_get())
              if (c->has_data())
                {
  // FIXME: Some code was deleted here.
                }
            // Create the contents of the variant.
            functions << variant_exp(class_type, class_type, inits)
                      << " end\n";

            /*------------------------------------------------------.
            | Create conversion routines from the class type to any |
            | of its super types.                                   |
            `------------------------------------------------------*/

            for (const type::Class* super_type = class_type->super_get();
                 super_type; super_type = super_type->super_get())
              functions << upcast_function(class_type, super_type);

            /*------------------------------------------------------.
            | Create conversion routines from the class type to any |
            | of its subtypes.                                      |
            `------------------------------------------------------*/

            for (const type::Class* subclass : class_type->subclasses_get())
              functions << downcast_function(class_type, subclass);

            /*--------------------.
            | Desugared methods.  |
            `--------------------*/

            for (const type::Method* m : class_type->meths_get())
              {
                functions <<
                          " function " <<
                          method_prefix << class_name << "_" << m->name_get() <<
                          " (self : " << class_variant_prefix << class_name;
                // Get the other arguments.
                const ast::MethodDec* def = m->def_get();
                const ast::VarDecs::Ds& formals =
                  def->formals_get().decs_get();
                for (const ast::VarDec* arg : formals)
                  functions << ", "
                            << arg->name_get() << " : "
                            << recurse(*arg->type_name_get());
                functions << ")";
                if (def->result_get())
                  functions << " : " << recurse(def->result_get());
                ast::Exp* body = recurse(def->body_get());
                // Cast the return value of the function if needed.
                if (def->result_get())
                  adapt_type(body,
                             class_type_query(*def->body_get()),
                             class_type_query(*def->result_get()));
                functions << " = " << body << "\n";
              }

            /*---------------------.
            | Dispatch functions.  |
            `---------------------*/

            for (const type::Method* m : class_type->meths_get())
              {
                functions <<
                          " function " << dispatch_fun_name(class_type, m) <<
                          " (self : " << class_variant_prefix << class_name;
                // Get the other arguments.
                const ast::MethodDec* def = m->def_get();
                const ast::VarDecs::Ds& formals =
                  def->formals_get().decs_get();
                for (const ast::VarDec* arg : formals)
                  functions << ", "
                            << arg->name_get() << " : "
                            << recurse(*arg->type_name_get());
                functions << ")";
                if (def->result_get() != nullptr)
                  functions << " : " << recurse(def->result_get());
                functions << " = " << dispatch_switch(class_type, m);
              }
          }
        else
          {
            /* FIXME: In the rest of the visitor, the
               simply-clone-this-node case is handled before the
               desugar-this-node case.  */
            // Otherwise, clone the type declaration.
            ast::TypeDec* typedec = recurse(*t);
            assertion(typedec);
            types_ << *typedec << "\n";
          }
      }

    ast::DecsList* funs_list = parse::parse(functions);
    result_ = funs_list;
  }


  /*------------------------------------------------.
  | Desugar class instantiations and object usage.  |
  `------------------------------------------------*/

  void
  DesugarVisitor::operator()(const ast::VarDec& e)
  {
    /* We don't desugar everything using concrete syntax here, because
       it would require a lot of additional manipulations, as we
       cannot easily produce a single VarDec from a parsing.  And
       working from VarDecs (with an `s') doesn't help much either, as
       VarDec's (with no `s') are also found in FunctionDec's.  */

    // If this is not an object instantiation, delegate to the cloner.
    const type::Class* class_type = class_type_query(e);
    if (!class_type)
      return super_type::operator()(e);

    // Otherwise, handle the different cases.
    const ast::Location& location = e.location_get();
    ast::NameTy* type_name = nullptr;
    ast::Exp* init = nullptr;
    if (e.init_get())
      {
        // Object (variable) declaration.
        if (e.type_name_get())
          {
            type_name = recurse(e.type_name_get());
            init = recurse(e.init_get());
            // If the dynamic type is non-nil and different from the
            // static type, cast INIT to the latter.
            if (e.init_get()->type_get() != &type::Nil::instance())
              adapt_type(init, class_type_get(*e.init_get()), class_type);
          }
        else
          // No manifest type: simply clone the declaration as-is.
          return super_type::operator()(e);
      }
    else
      // Formal declaration.
      type_name = recurse(e.type_name_get());

    const misc::symbol& name = e.name_get();
    result_ = new ast::VarDec(location, name,
                              type_name, init);
    postcondition(type_name || init);
  }


  // Desugar a class instantiation as a call to the desugared ctor routine.
  void
  DesugarVisitor::operator()(const ast::ObjectExp& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  DesugarVisitor::operator()(const ast::AssignExp& e)
  {
    // If this is not an object assignment, delegate to the cloner.
    const type::Class* lhs_class_type = class_type_query(e.var_get());
    if (!lhs_class_type)
      return super_type::operator()(e);

    // Duplicate the subtrees of E.
    ast::Var* var = recurse(e.var_get());
    ast::Exp* exp = recurse(e.exp_get());
    // If the RHS type is non-nil and different from the LHS type,
    // cast EXP to the latter.
    if (e.exp_get().type_get() != &type::Nil::instance())
      adapt_type(exp, class_type_get(e.exp_get()), lhs_class_type);
    ast::Exp* assignment =
      parse::parse(parse::Tweast() << var << " := " << exp);
    result_ = assignment;
  }


  ast::exps_type*
  DesugarVisitor::recurse_args(const ast::exps_type& actuals,
                               const type::Record& formals)
  {
    // For each argument, check the type of the actual argument
    // against the formal one.  If they are two different class types,
    // convert the actual argument to the expected type.
    auto args = new ast::exps_type;
    ast::exps_type::const_iterator i;
    type::Record::const_iterator j;
    for (i = actuals.begin(), j = formals.begin();
         i != actuals.end() && j != formals.end();
         ++i, ++j)
      {
        // Clone the argument.
        ast::Exp* arg = recurse(**i);

        // In the case of a class, handle the case of a (non-nil) actual
        // argument having a different type than the corresponding
        // formal.
        const type::Type* formal_type = &j->type_get().actual();
        auto formal_class_type = dynamic_cast<const type::Class*>(formal_type);
        if (formal_class_type && (*i)->type_get() != &type::Nil::instance())
          adapt_type(arg, class_type_get(**i), formal_class_type);
        args->push_back(arg);
      }
    return args;
  }

  void
  DesugarVisitor::operator()(const ast::CallExp& e)
  {
    auto function_type =
      dynamic_cast<const type::Function*>(e.def_get()->type_get());

    const ast::Location& location = e.location_get();
    const misc::symbol& name = e.name_get();

    // Actual arguments.
    const ast::exps_type& actuals = e.args_get();
    // (Types of) formal arguments.
    const type::Record& formals = function_type->formals_get();
    // Desugar the arguments and handle possible polymorphic assignements.
    ast::exps_type* args = recurse_args(actuals, formals);

    result_ = new ast::CallExp(location, name, args);
  }


  /*------------------------------------.
  | Desugar accesses to class members.  |
  `------------------------------------*/

  void
  DesugarVisitor::operator()(const ast::FieldVar& e)
  {
    // Check the type of the variable to see whether it is a class or
    // a record.
    const type::Class* class_type = class_type_query(e.var_get());
    // If this is not a class, delegate to the cloner.
    if (!class_type)
      return super_type::operator()(e);

    // Otherwise, desugar this FieldVar as an access to an attribute.
    const misc::symbol& attr = e.name_get();
    // Look for the attribute within the class and its base classes.
    const type::Class* owner = nullptr;
    for (const type::Class* c = class_type; c; c = c->super_get())
      if (c->owned_attr_find(attr))
        {
          owner = c;
          break;
        }
    assertion(owner);

    ast::Var* var = recurse(e.var_get());
    ast::Exp* attr_var =
      parse::parse(parse::Tweast() <<
                   var <<
                   "." << variant_field_prefix << class_names_(owner) <<
                   "." << attr);
    result_ = attr_var;
  }

  void
  DesugarVisitor::operator()(const ast::MethodCallExp& e)
  {
    auto method_type =
      dynamic_cast<const type::Method*>(e.def_get()->type_get());
    const type::Class* owner_type = method_type->owner_get();

    const ast::Location& location = e.location_get();
    std::string name = dispatch_fun_name(owner_type, method_type);

    // Actual arguments.
    const ast::exps_type& actuals = e.args_get();
    // (Types of) formal arguments.
    const type::Record& formals = method_type->formals_get();
    // Desugar the arguments and handle possible polymorphic assignements.
    ast::exps_type* args = recurse_args(actuals, formals);

    // Process the target of the method call, and convert it to the
    // expected type if needed.
    ast::Exp* object = recurse(e.object_get());
    adapt_type(object, class_type_get(e.object_get()), owner_type);
    // Prepend the target to the actual arguments, as the desugared
    // method expects to find it as its first arguments.
    args->push_front(object);

    // Turn the method call into a function call to the desugared method.
    result_ = new ast::CallExp(location, name, args);
  }


  /*--------------------------.
  | New types and functions.  |
  `--------------------------*/

  // Introduce a desugared builtin Object in the top-level function.
  void
  DesugarVisitor::operator()(const ast::FunctionDec& e)
  {
    if (e.name_get() == "_main")
      {
        // Desugared data structures of the builtin Object.
        types_
            << "   type " << class_variant_prefix << "Object ="
            << variant_ty(&type::Class::object_instance());
        // Object's class id.
        class_ids_ <<
                   "   var  " << class_id_prefix << "Object := "
                   "        " << type::Class::object_instance().id_get();
      }

    // Process E.
    super_type::operator()(e);

    if (e.name_get() == "_main")
      {
        // Object's ctor.
        parse::Tweast funs_tweast;
        funs_tweast <<
                    "   function " << class_ctor_prefix << "Object () :"
                    "     " << class_variant_prefix << "Object =";
        // Initialize the variant (a single field is filled, the one
        // corresponding to Object).
        field_inits_type object_init;
        misc::put(object_init, &type::Class::object_instance(),
                  std::string(class_contents_prefix) + "Object {}");
        // Create the variant.
        funs_tweast << variant_exp(&type::Class::object_instance(),
                                   &type::Class::object_instance(),
                                   object_init);

        // Parse the built TWEASTs.
        ast::DecsList* types = parse::parse(types_);
        ast::DecsList* class_ids = parse::parse(class_ids_);
        ast::DecsList* funs = parse::parse(funs_tweast);
        // Gather these declarations.
        ast::DecsList* decs = types;
        decs->splice_back(*class_ids);
        decs->splice_back(*funs);
        // Add them to the top of the program.
        auto res = dynamic_cast <ast::FunctionDec*>(result_);
        parse::Tweast input;
        input << "let " << decs << " in " << res->body_get() << " end";
        res->body_set(parse::parse(input));
      }

    // Cast the return value of the function if needed.
    if (e.body_get() && e.result_get())
      {
        const type::Class* body_type = class_type_query(*e.body_get());
        const type::Class* result_type = class_type_query(*e.result_get());
        if (body_type && result_type && body_type != result_type)
          {
            auto res = dynamic_cast <ast::FunctionDec*>(result_);
            parse::Tweast input;
            input << upcast_fun_name(body_type, result_type)
                  << " (" << res->body_get() << ")";
            res->body_set(parse::parse(input));
          }
      }
  }

  void
  DesugarVisitor::operator()(const ast::NameTy& e)
  {
    // Check if E is the name of a class; if not, just clone it.
    const type::Class* class_type = class_type_query(e);
    if (!class_type)
      return super_type::operator()(e);

    // Otherwise, desugar the name of E.
    const ast::Location& location = e.location_get();
    result_ = new ast::NameTy(location,
                              class_variant_prefix +
                              class_names_(class_type).name_get());
  }


} // namespace object
