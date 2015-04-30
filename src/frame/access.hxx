/**
 ** \file frame/access.hxx
 ** \brief Inline methods for frame/access.hh.
 */

#ifndef FRAME_ACCESS_HXX
# define FRAME_ACCESS_HXX

# include <frame/access.hh>

namespace frame
{

  inline
  temp::Temp
  In_Register::temp_get() const
  {
    return temp_;
  }

  inline
  int
  In_Frame::offset_get() const
  {
    return offset_;
  }

}

#endif // !FRAME_ACCESS_HXX
