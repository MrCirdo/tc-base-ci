/**
 ** \file target/ia32/target.hh
 ** \brief Define the IA-32 Target.
 */

#ifndef TARGET_IA32_TARGET_HH
# define TARGET_IA32_TARGET_HH

# include <target/target.hh>
# include <target/ia32/cpu.hh>
# include <target/ia32/gas-assembly.hh>
# include <target/ia32/codegen.hh>

namespace target
{
  namespace ia32
  {

    /// An IA-32 Target is the union of an IA-32 Cpu and an IA-32 Codegen.
    class Target : public target::Target
    {
      /** \name Ctor & dtor.
       ** \{ */
    public:
      Target(bool rule_trace_p = false);
      virtual ~Target();
      /** \} */

    public:
      /// Access the IA-32 CPU (read only).
      virtual const Cpu& cpu_get() const override;
      /// Access the IA-32 CPU.
      virtual Cpu& cpu_get() override;

      /// Access the current assembly language (read only).
      virtual const Assembly& assembly_get() const override;
      /// Access the current assembly language.
      virtual Assembly& assembly_get() override;

      /// Access the current code generator (read only).
      virtual const Codegen& codegen_get() const override;
      /// Access the current code generator.
      virtual Codegen& codegen_get() override;

    protected:
      /// The description of an IA-32 CPU.
      ia32::Cpu cpu_;
      /// The selected code generator
      ia32::Codegen codegen_;

      // This should be a ia32::Assembly, dynamicaly set to
      // GasAssembly or other.
      ia32::GasAssembly assembly_;
    };

  } // namespace ia32
} // namespace target

#endif // !TARGET_IA32_TARGET_HH
