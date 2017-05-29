/**
 ** \file assem/comment.hxx
 ** \brief Implementation for assem/comment.hxx.
 */
#pragma once

#include <sstream>
#include <ostream>
#include <assem/comment.hh>

namespace assem
{
  inline
  Comment::Comment(const std::string& comment)
    : Instr(comment)
  {}

  inline
  std::ostream&
  Comment::dump(std::ostream& ostr) const
  {
    std::string s;
    std::istringstream icomment(this->assem_);

    while (not icomment.eof())
      {
        getline(icomment, s);
        ostr << "\t# " << s;
      }
    return ostr;
  }

} // namespace assem
