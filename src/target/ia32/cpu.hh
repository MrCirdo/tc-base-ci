/**
 ** \file target/ia32/cpu.hh
 ** \brief Define IA32 CPU.
 */

#ifndef TARGET_IA32_CPU_HH
# define TARGET_IA32_CPU_HH

# include <target/cpu.hh>

namespace target
{
  namespace ia32
  {

    /// Describes IA-32's registers.
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

      /// Result register.
      virtual const temp::Temp& result_reg() const override;
    };

  } // namespace ia32
} // namespace target

#endif // !TARGET_IA32_CPU_HH
