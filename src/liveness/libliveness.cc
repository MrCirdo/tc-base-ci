/**
 ** \file liveness/libliveness.cc
 ** \brief Compute liveness analysis.
 */

#include <iostream>
#include <temp/temp.hh>
#include <assem/libassem.hh>
#include <assem/visitor.hh>
#include <liveness/libliveness.hh>
#include <liveness/flowgraph.hh>
#include <liveness/liveness.hh>
#include <liveness/interference-graph.hh>

namespace liveness
{

  // FIXME: This file is in a bad need of refactoring.

  void
  flowgraph_dump(const std::string& filename,
                 const assem::Fragments& fragments,
                 misc::timer& timer)
  {
    struct FlowGraphDump : public assem::ConstVisitor
    {
      using assem::ConstVisitor::operator();

      FlowGraphDump(const std::string& fname)
        : fname_(fname)
      {}

      const misc::timer& timer_get() const
      {
        return timer_;
      }

      void operator()(const assem::ProcFrag& frag) override
      {
        // First computation of FRAGMENT's flowgraph.
        // Compute it, name it, dump it if wanted.
        std::string name = frag.file_name(fname_, "flow.gv");
        FlowGraph<misc::empty> flowgraph(name, frag.instrs_get());
        std::ofstream ofs;
        ofs.open(name.c_str());
        ofs << flowgraph;
        ofs.close();

        timer_ << flowgraph.timer_get();
      }

    private:
      const std::string& fname_;
      misc::timer timer_;
    };

    FlowGraphDump v(filename);
    v(fragments);

    timer << v.timer_get();
  }


  void
  liveness_dump(const std::string& filename,
                const assem::Fragments& fragments,
                const temp::TempMap& tempmap,
                misc::timer& timer)
  {
    struct LivenessDump : public assem::ConstVisitor
    {
      using assem::ConstVisitor::operator();

      LivenessDump(const std::string& fname,
                   const temp::TempMap& tm)
        : fname_(fname)
        , tempmap_(tm)
      {}

      const misc::timer& timer_get() const
      {
        return timer_;
      }

      virtual void operator()(const assem::ProcFrag& frag) override
      {
        // First computation of FRAGMENT's flowgraph.
        // Compute it, name it, dump it if wanted.
        const std::string name = frag.file_name(fname_, "liveness.gv");
        std::ofstream ofs;
        ofs.open(name.c_str());
        temp::Temp::map(ofs) = const_cast<temp::Temp::map_type*>(&tempmap_);
        Liveness liveness(name, frag.instrs_get(), tempmap_);
        ofs << liveness;
        ofs.close();

        timer_ << liveness.timer_get();
      }

    private:
      const std::string& fname_;
      const temp::TempMap& tempmap_;
      misc::timer timer_;
    };

    LivenessDump v(filename, tempmap);
    v(fragments);

    timer << v.timer_get();
  }


  void
  interference_dump(const std::string& filename,
                    const assem::Fragments& fragments,
                    const temp::TempMap& tempmap,
                    misc::timer& timer)
  {
    struct InterferenceDump : public assem::ConstVisitor
    {
      using assem::ConstVisitor::operator();

      InterferenceDump(const std::string& fname,
                       const temp::TempMap& tm)
        : fname_(fname)
        , tempmap_(tm)
      {}

      const misc::timer& timer_get() const
      {
        return timer_;
      }

      virtual void
      operator()(const assem::ProcFrag& frag) override
      {
        // First computation of FRAGMENT's flowgraph.
        // Compute it, name it, dump it if wanted.
        const std::string name = frag.file_name(fname_);
        InterferenceGraph interference(name, frag.instrs_get(), tempmap_);
        interference.print(name + ".interference");

        timer_ << interference.timer_get();
      }

    private:
      const std::string& fname_;
      const temp::TempMap& tempmap_;
      misc::timer timer_;
    };

    InterferenceDump v(filename, tempmap);
    v(fragments);

    timer << v.timer_get();
  }

} // namespace liveness
