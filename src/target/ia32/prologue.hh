#include <cstring>

#include <ostream>
#include <map>
#include <algorithm>

#include <target/codegen.hh>
#include <target/fwd.hh>
#include <misc/contract.hh>
#include <temp/temp.hh>
#include <tree/all.hh>
#include <frame/frame.hh>
#include <frame/access.hh>
#include <assem/libassem.hh>
#include <target/target.hh>
#include <target/ia32/cpu.hh>
#include <target/assembly.hh>
#include <target/ia32/gas-assembly.hh>

namespace target
{
  namespace ia32
  {
    using namespace tree;
    using namespace frame;

    /// GasCodegen.
    class GasCodegen
      : public target::Codegen
    {
    public:
      using super_type = target::Codegen;

    public:
      /// Construct an IA-32 code generator.
      GasCodegen(bool rule_trace_p = false);
      /// Destroy a GasCodegen.
      virtual ~GasCodegen() = default;

    public:
      /// Define the targeted Ia32Cpu.
      void cpu_set(const target::ia32::Cpu& cpu);
      /// Access concrete CPU.
      const target::ia32::Cpu* cpu_get();

      /// Set the IA-32 assembly language to use.
      void assembly_set(GasAssembly& assembly);
      /// Access the current concrete assembly language.
      GasAssembly& assembly_get();

    public:
      /** \brief Reduce a tree using monoburg. Will output assembly
          code.  */
      void reduce(tree::rTree& tree, int goal);

      /** \brief To be able to use the callee save registers (which
          are virtually live throught out the function), we move
          them into fresh temporaries.  The register allocation is
          then free either to use the callee regs and spill these
          temps, or not to use the callee and therefore coalesce the
          the temps: a big nop.  */
      virtual void free_callee_save(assem::ProcFrag& frag);

      /** \brief Receive the incoming arguments, and move them where
          appropriate. */
      virtual void view_shift(assem::ProcFrag& frag);

      /** \brief Build part of the prologue and epilogue of the function:
          free the callee save registers, and receive the arguments.
          Called as soon as the function body was translated.
          This is called "procEntryExit1" by Appel. */
      void fragment_entry_exit_build(assem::ProcFrag& frag) override;

      /** \brief Preserve fp, sp and the return address register in
          hardware frame: push them during procedure prologue, pop them
          at epilogue.  Allocate the hardware frame by subtracting its
          size from the stack pointer for the procedure body.  This is
          Appel's "procEntryExit3".  */
      void frame_build(assem::ProcFrag& frag) const override;

      /** \brief Rewrite the code to spill the \a spilled.
          \see Codegen::rewrite_program. */
      void rewrite_program(assem::ProcFrag& frag2rw,
                                   const temp::temp_set_type& spilled_trees) const override;

    protected:
      /** \brief Emit an instruction to save \a word at the adress
          \a addr + the offset stored in the access (which is, in fact,
          an In_Frame).

          ACCESS is of course an In_Frame, but prototyped as Access to
          factor the dynamic_casts in here.  */
      assem::Instrs store_inframe(const frame::Access* access,
                                  const temp::Temp& word,
                                  const temp::Temp& addr) const;
      /** \brief same as store_inframe() except that it emit an instruction
          to load a word.  */
      assem::Instrs load_inframe(const frame::Access* access,
                                 const temp::Temp& word,
                                 const temp::Temp& addr) const;

    protected:
      /// Entry point for code generation
      void codegen(const tree::rStm& root) override;

    protected:
      /// The current Cpu with its real type: NolimipsCpu.
      const target::ia32::Cpu* cpu_;

      /// Assembly language.
      GasAssembly* assembly_;
    }; // class GasCodegen

    /** Current codegen running monoburg.  It has to be defined in the
        header for mono_burg_emit_N to know about it. */
    extern GasCodegen *cg;

  } // namespace ia32
} // namespace target


// Monoburg types.
#define MBTREE_TYPE  rTree
#define MBCGEN_TYPE  int
#define MBCOST_DATA  void*

// Monoburg operators for tree manipulation.
#define MBTREE_OP(t) ((*t)->kind_get())
#define MBTREE_LEFT(t) ((*t)->children_get().empty() ?        \
                        nullptr : &((*t)->left_get()))
#define MBTREE_RIGHT(t) ((*t)->children_get().size() < 2 ?    \
                         nullptr : &((*t)->right_get()))
#define MBTREE_STATE(t) ((*t)->state_get())

// Convenient macros for Monoburg use of GasCodegen's methods.
#define EMIT (cg->emit)
#define IA32_ASSEMBLY (cg->assembly_get())
#define FRAME (cg->frame_get())
#define MCPU (*(cg->cpu_get()))
#define REDUCE (cg->reduce)
