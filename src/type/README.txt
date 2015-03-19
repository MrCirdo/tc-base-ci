* README

Hierarchy of types for the Tiger language, with (most of) their
interfaces.


ostream& operator<< (ostream& ostr, const Type& t)
bool operator== (const Type& lhs, const Type& rhs);
bool operator!= (const Type& lhs, const Type& rhs);

/Type/
    virtual ~Type() {}
    virtual ostream& print (ostream&) const;
    virtual const Type& actual (void) const;
    virtual bool compatible_with (const Type& other) const;

  Nil

  Void

  Int

  String

  Named (const Symbol& name, const Type* type)
    void type_set (const Type *type)
    void type_set (const Type *type) const
    const bool sound () const

  Array (const Type& type)
    const Type& type_get () const

  Record (const list<Field*> &fields)
    const list<Field*>& fields_get () const
    const Type* field_type (const Symbol &key) const
    void field_add (Field *field)
    void field_add (const Symbol& name, const Type& type)

  Class (const Class* super = 0)
    const Type* attr_type (const Symbol& key) const
    const Method* meth_type (const Symbol& key) const
    const attrs_type& attrs_get () const
    const meths_type& meths_get () const
    void attr_add (const Attribute& attr)
    void attr_add (const Symbol& name, const Type& type, const VarDec* def)
    const Class* super_get () const
    void super_set (const Class* type)
    bool sound () const
    static const Class& object_instance ()

  Function (const Record* formals, const Type& result)

    Method (const Symbol& name, const Record* formals,
            const Type& result, MethodDec* def)
      Symbol name_get () const
      const MethodDec* def_get () const
      MethodDec* def_get ()
      void name_set (const Symbol& name)
      void def_set (MethodDec* def)

Field (const Symbol& name, const Type& type)

Attribute (const ast::VarDec* def)

