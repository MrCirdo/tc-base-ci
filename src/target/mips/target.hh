/**
 ** \file target/mips/target.hh
 ** \brief Define the MIPS Target.
 */

#ifndef TARGET_MIPS_TARGET_HH
# define TARGET_MIPS_TARGET_HH

# include <target/target.hh>
# include <target/mips/cpu.hh>
# include <target/mips/spim-assembly.hh>
# include <target/mips/codegen.hh>

namespace target
{
  namespace mips
  {

    /// A MIPS Target is the union of a MIPS Cpu and a MIPS Codegen.
    class Target : public target::Target
    {
      /** \name Ctor & dtor.
       ** \{ */
    public:
      /// Build a Target.
      Target(const CpuLimits& limits, bool rule_trace_p = false);
      virtual ~Target();
      /** \} */

    public:
      virtual const Cpu& cpu_get() const override;
      virtual Cpu& cpu_get() override;

      virtual const Assembly& assembly_get() const override;
      virtual Assembly& assembly_get() override;

      virtual const Codegen& codegen_get() const override;
      virtual Codegen& codegen_get() override;

    protected:
      mips::Cpu cpu_;

      mips::Codegen codegen_;

      // This should be a target::mips::Assembly, dynamicaly set to
      // SpimAssembly or other.
      mips::SpimAssembly assembly_;
    };

  } // namespace mips
} // namespace target

#endif // !TARGET_MIPS_TARGET_HH
