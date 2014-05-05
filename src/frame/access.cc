/**
 ** \file frame/access.cc
 ** \brief Location of a local variable.
 */

#include <temp/temp.hh>
#include <tree/all.hh>
#include <frame/access.hh>
#include <frame/frame.hh>

namespace frame
{

  /*---------.
  | Access.  |
  `---------*/

  Access::Access()
  {}

  Access::~Access()
  {}

  // When called without specifying the value of the frame pointer,
  // assume it is relatively to the *current* frame pointer.
  tree::rExp
  Access::exp() const
  {
    temp::Temp fp("fp");
    return exp(new tree::Temp(fp));
  }

  std::ostream&
  operator<<(std::ostream& ostr, const Access& acc)
  {
    return acc.dump(ostr);
  }


  /*--------------.
  | In_Register.  |
  `--------------*/

  In_Register::In_Register()
    : temp_(temp::Temp())
  {}

  In_Register::In_Register(const temp::Temp& temp)
    : temp_(temp)
  {}

  tree::rExp
  In_Register::exp(const tree::rExp&) const
  {
    return new tree::Temp(temp_);
  }

  In_Register*
  In_Register::clone() const
  {
    return new In_Register(temp_get());
  }

  std::ostream&
  In_Register::dump(std::ostream& ostr) const
  {
    return ostr << "InReg (" << temp_ << ")";
  }


  /*-----------.
  | In_Frame.  |
  `-----------*/

  In_Frame::In_Frame(int offset)
    : offset_(offset)
  {}

  tree::rExp
  In_Frame::exp(const tree::rExp& fp) const
  {
    tree::rExp indir;
    if (offset_)
      indir = new tree::Binop(tree::Binop::add,
                              fp,
                              new tree::Const(offset_));
    else
      indir = fp;
    return new tree::Mem(indir);
  }

  In_Frame*
  In_Frame::clone() const
  {
    return new In_Frame(offset_get());
  }

  std::ostream&
  In_Frame::dump(std::ostream& ostr) const
  {
    return ostr << "InFrame (" << offset_ << ")";
  }

}
