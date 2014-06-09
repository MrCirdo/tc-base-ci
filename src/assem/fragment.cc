/**
 ** \file assem/fragment.cc
 ** \brief Fragments of assembly.
 */

#include <string>
#include <misc/escape.hh>
#include <temp/label.hh>
#include <assem/fragment.hh>
#include <assem/fragments.hh>
#include <assem/visitor.hh>

namespace assem
{

  /*-----------.
  | Fragment.  |
  `-----------*/

  Fragment::~Fragment()
  {}


  /*-----------.
  | DataFrag.  |
  `-----------*/

  DataFrag::~DataFrag()
  {}

  void
  DataFrag::accept(Visitor& v)
  {
    v(*this);
  }

  void
  DataFrag::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  std::ostream&
  DataFrag::dump(std::ostream& ostr) const
  {
    ostr << ".data" << std::endl
         << data_frag_.label_get()
         << ":" << std::endl
         << "\t.word " << data_frag_.data_get().length() << std::endl
         << "\t.asciiz \"" << misc::escape(data_frag_.data_get())
         << "\"" << std::endl
         << ".text" << std::endl;
    return ostr;
  }


  /*-----------.
  | ProcFrag.  |
  `-----------*/

  ProcFrag::~ProcFrag()
  {}

  void
  ProcFrag::accept(Visitor& v)
  {
    v(*this);
  }

  void
  ProcFrag::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  std::string
  ProcFrag::file_name(const std::string& p, const std::string& s) const
  {
    return (p == "" ? "" : (p + "."))
            + label_.string_get()
            + "."
            + name_.name_get()
            + (s == "" ? "" : ("." + s));
  }


  std::ostream&
  ProcFrag::dump(std::ostream& ostr) const
  {
    return ostr
      << "# Routine: " << name_ << std::endl
      << instrs_ << std::endl;
  }

} // namespace assem
