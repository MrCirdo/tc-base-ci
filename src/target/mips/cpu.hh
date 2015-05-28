/**
 ** \file target/mips/cpu.hh
 ** \brief Define the MIPS CPU.
 */

#ifndef TARGET_MIPS_CPU_HH
# define TARGET_MIPS_CPU_HH

# include <target/fwd.hh>
# include <target/cpu.hh>

namespace target
{
  namespace mips
  {

    /// Describes MIPS's registers.
    class Cpu : public target::Cpu
    {
      /** \name Ctor & dtor.
       ** \{ */
    public:
      /// Construct a Cpu.
      Cpu(const CpuLimits& limits);
      /** \} */

    public:
      virtual size_t word_size_get() const override;

      /// Frame pointer.
      virtual const temp::Temp& fp_reg() const override;

      /// Stack pointer.
      virtual const temp::Temp& sp_reg() const;

      /// Result register
      virtual const temp::Temp& result_reg() const override;

      /// Return address
      virtual const temp::Temp& return_reg() const;

      /// Special register containing constant 0.
      const temp::Temp& zero_reg() const;
    };

  } // namespace mips
} // namespace target

#endif // !TARGET_MIPS_CPU_HH
