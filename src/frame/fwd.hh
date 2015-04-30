/**
 ** \file frame/fwd.hh
 ** \brief Forward declarations for frame:: items.
 */

#ifndef FRAME_FWD_HH
# define FRAME_FWD_HH

# include <list>
# include <vector>

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

  using bool_list_type = std::vector<bool>;
  using access_list_type = std::list<const Access*>;

}

#endif // !FRAME_FWD_HH
