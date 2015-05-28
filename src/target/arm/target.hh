/**
 ** \file target/arm/target.hh
 ** \brief Define the ARM Target.
 */

#ifndef TARGET_ARM_TARGET_HH
# define TARGET_ARM_TARGET_HH

# include <target/target.hh>
# include <target/arm/cpu.hh>
# include <target/arm/arm-assembly.hh>
# include <target/arm/arm-codegen.hh>

namespace target
{
  namespace arm
  {

    /// An ARM Target is the union of an ARM Cpu and an ARM ArmCodegen.
    class Target : public target::Target
    {
      /** \name Ctor & dtor.
       ** \{ */
    public:
      Target(bool rule_trace_p = false);
      virtual ~Target() = default;
      /** \} */

    public:
      /// Access the ARM CPU (read only).
      virtual const Cpu& cpu_get() const override;
      /// Access the ARM CPU.
      virtual Cpu& cpu_get() override;

      /// Access the current assembly language (read only).
      virtual const Assembly& assembly_get() const override;
      /// Access the current assembly language.
      virtual Assembly& assembly_get() override;

      /// Access the current code generator (read only).
      virtual const ArmCodegen& codegen_get() const override;
      /// Access the current code generator.
      virtual ArmCodegen& codegen_get() override;

    protected:
      /// The description of an ARM CPU.
      arm::Cpu cpu_;
      /// The selected code generator
      arm::ArmCodegen codegen_;

      // This should be a arm::Assembly, dynamicaly set to
      // ArmAssembly or other.
      arm::ArmAssembly assembly_;
    };

  } // namespace arm
} // namespace target

#endif // !TARGET_ARM_TARGET_HH
