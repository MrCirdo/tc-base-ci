/**
 ** \file regalloc/color.cc
 ** \brief Implementation for regalloc/color.hh.
 **/

#include <climits>

#include <iostream>
#include <sstream>
#include <algorithm>

#include <misc/algorithm.hh>

#include <temp/temp.hh>
#include <target/cpu.hh>

#include <regalloc/color.hh>

/// Run the 0-ary function \a What, verbosely.
# define DO(What)                                                       \
do {                                                                    \
  if (trace_p_)                                                         \
    std::cerr << "## " #What ": begin." << std::endl;                   \
  timer_.push ("9: " #What);                                            \
  What ();                                                              \
  timer_.pop ("9: " #What);                                             \
  if (trace_p_)                                                         \
    std::cerr << "## " #What ": end." << std::endl;                     \
} while (0)


namespace regalloc
{

  Color::Color(assem::ProcFrag& frag, const target::Cpu& cpu,
               const temp::TempMap& tempmap,
               bool coalesce_p, bool trace_p)
    : ig_(InterferenceGraph(frag.file_name(),
                            frag.instrs_get(),
                            tempmap,
                            trace_p))
    , cpu_(cpu)
    , nb_regs_(cpu_.nb_regs())
    , asm_proc_frag_(frag)
    , trace_p_(trace_p)
    , coalesce_p_(coalesce_p)
    , degree_(boost::num_vertices(ig_))
    , move_list_(boost::num_vertices(ig_))
    , alias_(boost::num_vertices(ig_))
    , color_(boost::num_vertices(ig_))
  {
    timer_ << ig_.timer_get();
    // Pre-treatments.
    DO(precolor);
    DO(import_nodes);
    if (coalesce_p)
      DO(import_moves);
    DO(degrees_compute);
    DO(priorities_compute);
    DO(make_work_list);
  }

  void
  Color::import_nodes()
  {
    liveness::interferencegraph_vertex_iter_type i;
    liveness::interferencegraph_vertex_iter_type end;
    for (boost::tie(i, end) = boost::vertices(ig_); i != end; ++i)
      if (!(*i % precolored_))
        initial_ += *i;
  }

  void
  Color::import_moves()
  {
    work_list_moves_ = ig_.moves_get();
    for (const move_type& m : work_list_moves_)
      {
        move_list_[m.first].insert(m);
        move_list_[m.second].insert(m);
      }
  }

  void
  Color::precolor()
  {
  // FIXME: Some code was deleted here.
  }


  void
  Color::priorities_compute()
  {
  // FIXME: Some code was deleted here.
  }


  void
  Color::degrees_compute()
  {
  // FIXME: Some code was deleted here.
  }

  // FIXME: Some code was deleted here.

  bool
  Color::operator()()
  {
    if (trace_p_)
      std::cerr << "## color: begin." << std::endl;
    do
      {
        if (trace_p_)
          dump(std::cerr);
        if (!simplify_work_list_.empty())
          DO(simplify);
        else if (!work_list_moves_.empty())
          DO(coalesce);
        else if (!freeze_work_list_.empty())
          DO(freeze);
        else if (!spill_work_list_.empty())
          DO(select_spill);
      }
    while (!simplify_work_list_.empty()
           || !work_list_moves_.empty()
           || !freeze_work_list_.empty()
           || !spill_work_list_.empty())
      ;

    // Pop the entire stack, assigning colors.
    DO(assign_colors);
    if (trace_p_)
      std::cerr << "## color: end." << std::endl;

    return spilled_nodes_.empty();
  }


  const temp::temp_set_type
  Color::spilled_get() const
  {
    temp::temp_set_type res;
    for (const node_type& n : spilled_nodes_)
      res.insert(ig_[n]);
    return res;
  }

  temp::TempMap
  Color::tempmap_get() const
  {
    temp::TempMap res;
  // FIXME: Some code was deleted here.
    return res;
  }

  const misc::timer&
  Color::timer_get() const
  {
    return timer_;
  }

  void
  Color::trace(const std::string& what, const node_type& n) const
  {
    if (trace_p_)
      {
        dump(std::cerr, n);
        std::cerr << '\t' << what << std::endl;
      }
  }

  void
  Color::trace(const std::string& what, const move_type& m) const
  {
    if (trace_p_)
      {
        dump(std::cerr, m);
        std::cerr << '\t' << what << std::endl;
      }
  }

  void
  Color::dump(std::ostream& ostr, const node_type& n) const
  {
    // ostr << n << " (" << *ig_[n] << ")";
    ostr << ig_[n]; //  << " (" << degree_[n] << ")";
    if (n % colored_nodes_)
      std::cerr << " (" << color_[n] << ')';
  }

  void
  Color::dump(std::ostream& ostr, const node_set_type& s) const
  {
    for (node_set_type::const_iterator i = s.begin(); i != s.end(); ++i)
      {
        if (i != s.begin())
          ostr << " ";
        dump(ostr, *i);
      }
  }

  void
  Color::dump(std::ostream& ostr, const node_list_type& s) const
  {
    for (node_list_type::const_iterator i = s.begin(); i != s.end(); ++i)
      {
        if (i != s.begin())
          ostr << " ";
        dump(ostr, *i);
      }
  }

  void
  Color::dump(std::ostream& ostr, const move_type& s) const
  {
    dump(ostr, s.first);
    ostr << ":=";
    dump(ostr, s.second);
  }

  void
  Color::dump(std::ostream& ostr, const move_set_type& s) const
  {
    for (move_set_type::const_iterator i = s.begin(); i != s.end(); ++i)
      {
        if (i != s.begin())
          ostr << " ";
        dump(ostr, *i);
      }
  }

  void
  Color::dump(std::ostream& ostr) const
  {
#   define REPORT(Title, What)                          \
    do {                                                \
      ostr << Title << " (" << (What).size () << "): "; \
      dump (ostr, What);                                \
      ostr << std::endl;                                \
    } while (0)

    size_t size = 0;
    size += precolored_.size();
    size += initial_.size();
    size += simplify_work_list_.size();
    size += freeze_work_list_.size();
    size += spill_work_list_.size();
    size += spilled_nodes_.size();
    size += coalesced_nodes_.size();
    size += colored_nodes_.size();
    size += select_stack_.size();

    ostr << "===================="
         << " Nodes " << ig_.name_get() << " (" << size << ") "
         << "====================" << std::endl;

    REPORT("Precolor   ", precolored_);
    REPORT("Initial    ", initial_);
    REPORT("Simplify WL", simplify_work_list_);
    REPORT("Freeze WL  ", freeze_work_list_);
    REPORT("Spill WL   ", spill_work_list_);
    REPORT("Spilled    ", spilled_nodes_);
    REPORT("Coalesced  ", coalesced_nodes_);
    REPORT("Colored    ", colored_nodes_);
    REPORT("Select     ", select_stack_);

    if (coalesce_p_)
      {
        size = 0;
        size += coalesced_moves_.size();
        size += constrained_moves_.size();
        size += frozen_moves_.size();
        size += work_list_moves_.size();
        size += active_moves_.size();

        ostr << "--------------------"
             << " Moves " << ig_.name_get() << " (" << size << ") "
             << "--------------------" << std::endl;

        REPORT("Coalesced  ", coalesced_moves_);
        REPORT("Constrained", constrained_moves_);
        REPORT("Frozen     ", frozen_moves_);
        REPORT("Moves WL   ", work_list_moves_);
        REPORT("Active     ", active_moves_);
      }
#   undef REPORT
  }

} // namespace regalloc


# undef DO
