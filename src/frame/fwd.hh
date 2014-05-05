/**
 ** \file frame/fwd.hh
 ** \brief Forward declarations for frame:: items.
 */

#ifndef FRAME_FWD_HH
# define FRAME_FWD_HH

# include <list>

namespace frame
{

  // frame.hh.
  class Frame;

  // access.hh.
  class Access;
  class In_Register;
  class In_Frame;

  /// Global word size, in byte.
  // FIXME: this is of course very unsatisfying, as it is a global,
  // and should be bound to the target::Cpu.
  extern size_t word_size;

  typedef std::list<bool> bool_list_type;
  typedef std::list<const Access*> access_list_type;

}

#endif // !FRAME_FWD_HH
