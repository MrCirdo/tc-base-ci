/**
 ** \file target/arm/cpu.hh
 ** \brief Define ARM CPU.
 */

#ifndef TARGET_ARM_CPU_HH
# define TARGET_ARM_CPU_HH

# include <target/cpu.hh>

namespace target
{
  namespace arm
  {

    /// Describes ARM-32's registers.
    class Cpu : public target::Cpu
    {
      /** \name Ctor & dtor.
       ** \{ */
    public:
      /// Construct a Cpu (default).
      Cpu();
      /** \} */

    public:
      /// Word size.
      virtual size_t word_size_get() const override;

      /// Frame pointer.
      virtual const temp::Temp& fp_reg() const override;

      /// Stack pointer.
      virtual const temp::Temp& sp_reg() const;

      /// Link register
      virtual const temp::Temp& lr_reg() const;

      /// Result register.
      virtual const temp::Temp& result_reg() const override;
    };

  } // namespace arm
} // namespace target

#endif // !TARGET_ARM_CPU_HH
