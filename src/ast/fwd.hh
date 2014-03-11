/**
 ** \file ast/fwd.hh
 ** \brief Forward declarations of all AST classes
 ** (needed by the visitors).
 */

#ifndef AST_FWD_HH
# define AST_FWD_HH


# include <list>
# include <misc/fwd.hh>
# include <misc/xalloc.hh>


namespace ast
{

  class ArrayExp;
  class ArrayTy;
  class AssignExp;
  class Ast;
  class BreakExp;
  class CallExp;
  class CastExp;
  class CastVar;
  class ClassTy;
  class Dec;
  class DecsList;
  class Escapable;
  class Exp;
  class Field;
  class FieldInit;
  class FieldVar;
  class ForExp;
  class FunctionDec;
  class IfExp;
  class IntExp;
  class LetExp;
  class MethodCallExp;
  class MethodDec;
  class NameTy;
  class NilExp;
  class ObjectExp;
  class OpExp;
  class RecordExp;
  class RecordTy;
  class SeqExp;
  class SimpleVar;
  class StringExp;
  class SubscriptVar;
  class Ty;
  class Typable;
  class TypeConstructor;
  class TypeDec;
  class Var;
  class VarDec;
  class WhileExp;


  // From visitor.hh
  template <template <typename> class Const>
  class GenVisitor;
  typedef GenVisitor<misc::constify_traits> ConstVisitor;
  typedef GenVisitor<misc::id_traits> Visitor;

  // Collections of nodes.
  typedef std::list<Exp*> exps_type;
  typedef std::list<FieldInit*> fieldinits_type;
  typedef std::list<Field*> fields_type;

  // From decs.hh.
  class Decs;

  // From decs-list.hh.
  class DecsList;

  // From anydecs.hh.
  template <typename T>
  class AnyDecs;
  typedef AnyDecs<FunctionDec> FunctionDecs;
  typedef AnyDecs<MethodDec> MethodDecs;
  typedef AnyDecs<TypeDec> TypeDecs;
  typedef AnyDecs<VarDec> VarDecs;


} // namespace ast

#endif // !AST_FWD_HH
