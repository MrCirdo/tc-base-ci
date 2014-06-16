/**
 ** \file liveness/interference-graph.hh
 ** \brief Declare liveness::InterferenceGraph.
 */

#ifndef LIVENESS_INTERFERENCE_GRAPH_HH
# define LIVENESS_INTERFERENCE_GRAPH_HH

# include <list>
# include <map>

# include <misc/graph.hh>
# include <temp/fwd.hh>
# include <assem/libassem.hh>
# include <misc/set.hh>
# include <liveness/liveness.hh>
# include <target/libtarget.hh>

namespace liveness
{

  /*--------------------.
  | InterferenceGraph.  |
  `--------------------*/

  /** \brief Provide liveness analysis.
   **
   ** The liveness of variables in control-flow is analyzed,
   ** producing an InterferenceGraph. */
  class InterferenceGraph
    : public misc::undirected_graph<temp::Temp>
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /** \brief Construct an InterferenceGraph.
        \param name    its name, hopefully based on the function name
        \param instrs  the code snippet to study
        \param tempmap current Temp mapping
        \param trace   trace flag
    */
    InterferenceGraph(const std::string& name,
                      const assem::Instrs& instrs,
                      const temp::TempMap& tempmap,
                      bool trace = false);

    virtual ~InterferenceGraph();
    /** \} */

    /** \name Mapping from unique node decoration (the Temp) to
     ** the vertex_descriptor.
     ** \{ */
  private:
    /// Converting a temp::Temp into a unique integer.
    typedef std::map<const temp::Temp, vertex_descriptor> temp2vertex;
    /// The mapping from temp::Temp to vertex_descriptor (= integer).
    temp2vertex temp2node;
    /// The mapping from pseudos to actual registers.
    const temp::TempMap& tempmap_;
  public:
    /// Is the Temp \a t already part of the InterferenceGraph?
    bool has(const temp::Temp& t) const;
    /// From Temp to vertex_descriptor.  If \a t is not know yet, insert it.
    vertex_descriptor node_of(const temp::Temp& t);
    /** \} */


    /** \name Liveness analysis engine.
     ** \{ */
  protected:
    /* \brief Build the InterferenceGraph from \a liveness.

       \a Liveness remembers what is live at the exit of each
       flow-graph node.  Keep track of the moves.  Kept out of the
       ctor only to make it easier to read.  */
    void compute_liveness(const liveness::Liveness& liveness);
    /** \} */


    /** \name Moves.
        We keep track of all the moves so that we can try to coalesce
        destination and source.
        \{ */
  public:
    /** \brief A move is a pair (src, dst).

    Moves are not oriented, we chose to have pairs such that
    1st <= 2nd. */
    typedef std::pair<vertex_descriptor, vertex_descriptor> move_type;

    /// Sets of moves.
    typedef misc::set<move_type> move_set_type;

    /// Return the moves (const).
    const move_set_type& moves_get() const;
    /// Return the moves (non-const).
    move_set_type& moves_get();

  public:
    /// Get the liveness timer.
    const misc::timer& timer_get() const;

  protected:
    /// Include the move related edges in the output.
    virtual std::ostream& epilogue_print(std::ostream& ostr) const;
    /// Print the label of vertex of a graph.
    virtual std::ostream&
    vertex_print(vertex_descriptor v, std::ostream& ostr) const override;

    /// The set of moves.
    move_set_type moves_;
    /** \} */

    /** \name Trace methods.
     ** \{ */
  protected:
    /// trace flag.
    bool trace_;
    /** \} */

    /** \name Timer member.
     ** \{ */
  private:
    /// Interference timer.
    misc::timer timer_;
    /** \} */

  }; // class InterferenceGraph


  /*------------.
  | Iterators.  |
  `------------*/

  /// Iterator on the vertices of an InterferenceGraph.
  typedef boost::graph_traits<InterferenceGraph>::vertex_iterator
  interferencegraph_vertex_iter_type;
  /// Iterator on the edges of an InterferenceGraph.
  typedef boost::graph_traits<InterferenceGraph>::edge_iterator
  interferencegraph_edge_iter_type;

  /// Iterator on the neighborhood of a vertex of an InterferenceGraph.
  typedef boost::graph_traits<InterferenceGraph>::adjacency_iterator
  interferencegraph_neighb_iter_type;

} // namespace liveness

#include <liveness/interference-graph.hxx>

#endif // !LIVENESS_INTERFERENCE_GRAPH_HH
