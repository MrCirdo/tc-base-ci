/**
 ** \file liveness/interference-graph.hxx
 ** \brief Inline methods for liveness/interference-graph.hh.
 */

#ifndef LIVENESS_INTERFERENCE_GRAPH_HXX
# define LIVENESS_INTERFERENCE_GRAPH_HXX

namespace liveness
{

  inline
  const InterferenceGraph::move_set_type&
  InterferenceGraph::moves_get() const
  {
    return moves_;
  }

  inline
  InterferenceGraph::move_set_type&
  InterferenceGraph::moves_get()
  {
    return moves_;
  }

  inline
  const misc::timer&
  InterferenceGraph::timer_get() const
  {
    return timer_;
  }

} // namespace liveness

#endif // !LIVENESS_INTERFERENCE_GRAPH_HXX
