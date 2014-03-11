/**
 ** \file callgraph/call-graph-visitor.hh
 ** \brief Definition of callgraph::CallGraphVisitor.
 **/
#ifndef CALLGRAPH_CALL_GRAPH_VISITOR_HH
# define CALLGRAPH_CALL_GRAPH_VISITOR_HH

# include <ast/default-visitor.hh>
# include <ast/non-object-visitor.hh>
# include <callgraph/fundec-graph.hh>

namespace callgraph
{

  /// Computes the CallGraph.
  class CallGraphVisitor
    : protected ast::DefaultConstVisitor
    , protected ast::NonObjectConstVisitor
  {
  public:
    typedef ast::DefaultConstVisitor super_type;
    using super_type::operator();

  public:
    virtual ~CallGraphVisitor();

  public:
    const CallGraph* create(const ast::Ast& tree);
    CallGraph* create(ast::Ast& tree);

  protected:
    virtual void operator()(const ast::CallExp& e) override;
    virtual void operator()(const ast::FunctionDecs& e) override;
    virtual void operator()(const ast::FunctionDec& e) override;

  protected:
    /// Current function.
    ast::FunctionDec* caller = nullptr;
    /// Call graph.
    CallGraph* callgraph = nullptr;
  };

} // namespace callgraph

#endif // !CALLGRAPH_CALL_GRAPH_VISITOR_HH
