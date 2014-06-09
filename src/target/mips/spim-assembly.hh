/**
 ** \file target/mips/spim-assembly.hh
 ** \brief Declaration of target::mips::SpimAssembly.
 */

#ifndef TARGET_MIPS_SPIM_ASSEMBLY_HH
# define TARGET_MIPS_SPIM_ASSEMBLY_HH

# include <target/assembly.hh>

namespace target
{

  namespace mips
  {

    /** \brief Implements a SPIM compatible assembly language.
     **
     ** See SPIM, MIPS emulator. */
    class SpimAssembly : public ::target::Assembly
    {
      /** \name Ctor & dtor.
       ** \{ */
    public:
      /// Construct a SpimAssembly.
      SpimAssembly();
      /// Destroy a SpimAssembly.
      virtual ~SpimAssembly();
      /** \} */


      /** \name Arithmetic instructions.
       ** \{ */
    public:
      /// Return the instruction for \a op.
      std::string binop_inst(const tree::Binop::Oper& op) const;
      /// Build a binary (reg with reg in reg) operation in assembly.
      assem::Instrs binop_build(const tree::Binop::Oper& op,
                                const temp::Temp& left,
                                const temp::Temp& right,
                                const temp::Temp& res) const;
      /// Build a binary (imm with reg in reg) operation in assembly.
      assem::Instrs binop_build(const tree::Binop::Oper& op,
                                const temp::Temp& left,
                                int right,
                                const temp::Temp& res) const;

      // This method should be useless: the BURG generator should use
      // the precedent form.
      assem::Instrs binop_build(const tree::Binop::Oper& op,
                                int left,
                                const temp::Temp& right,
                                const temp::Temp& res) const;
      /** \} */


      /** \name Copy instructions.
       ** \{ */
    public:
      /// Build a move (register into register) operation in assembly.
      assem::Instrs move_build(const temp::Temp& src,
                               const temp::Temp& dst) const;
      /** \brief Build a move (immediate into register) operation in
       ** assembly. */
      assem::Instrs move_build(int immediate,
                               const temp::Temp& dst) const;

      /// Build a move (label into register) operation in assembly.
      assem::Instrs move_build(const temp::Label& label,
                               const temp::Temp& dst) const;

      /// Build a load (memory into register) operation in assembly.
      assem::Instrs load_build(const temp::Temp& base,
                               int offset,
                               const temp::Temp& dst) const;
      /// Build a load (memory into register) operation in assembly.
      assem::Instrs load_build(const temp::Temp& base,
                               const temp::Temp& dst) const;
      /// Build a load (memory into register) operation in assembly.
      assem::Instrs load_build(int absolute,
                               const temp::Temp& dst) const;

      /// Build a store (register into memory) operation in assembly.
      assem::Instrs store_build(const temp::Temp& src,
                                const temp::Temp& base,
                                int offset = 0) const;
      /// Build a store (register into memory) operation in assembly.
      assem::Instrs store_build(const temp::Temp& src,
                                int absolute) const;
      /** \} */


      /** \name Jump instructions.
       ** \{ */
    public:
      /// Build a label in assembly.
      assem::Instrs label_build(const temp::Label& label) const;

      /// Return the instruction for \a relop.
      std::string cjump_inst(const tree::Cjump::Relop& op) const;

      /// Build a conditional jump in assembly.
      assem::Instrs cjump_build(const tree::Cjump::Relop& relop,
                                const temp::Temp& left,
                                const temp::Temp& right,
                                const temp::Label& label_true,
                                const temp::Label& label_false) const;

      /// Build a conditional jump in assembly.
      assem::Instrs cjump_build(const tree::Cjump::Relop& relop,
                                const temp::Temp& left,
                                int right,
                                const temp::Label& label_true,
                                const temp::Label& label_false) const;
      /// Build an unconditional jump in assembly.
      assem::Instrs jump_build(const temp::Label& label) const;
      /** \} */

      /** \name Function operations.
       ** \{ */
    public:
      /// Build a function call in assembly.
      assem::Instrs call_build(const temp::Label& label,
                               const temp::temp_list_type& args,
                               const temp::temp_list_type& res) const;
      /// Build a function return in assembly.
      assem::Instrs ret_build(const temp::Temp& ret) const;
      /** \} */


      /** \name Runtime library.
       ** \{ */
    public:
      /// Return the runtime library.
      virtual const char* runtime(bool gc = false) const override;
      /** \} */
    };

  } // namespace mips

} // namespace target

#endif // !TARGET_MIPS_SPIM_ASSEMBLY_HH
