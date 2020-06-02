#ifndef TARGET_MIPS_CODEGEN
# define TARGET_MIPS_CODEGEN

/**                                                      -*- C++ -*-
 ** \file target/mips/codegen.hh
 ** \brief Entry point of the Tree grammar.
 */

#line 1 "target/mips/prologue.hh"
#include <algorithm>
#include <cstring>
#include <map>
#include <ostream>

#include <assem/libassem.hh>
#include <frame/access.hh>
#include <frame/frame.hh>
#include <misc/contract.hh>
#include <target/assembly.hh>
#include <target/codegen.hh>
#include <target/cpu.hh>
#include <target/fwd.hh>
#include <target/mips/cpu.hh>
#include <target/mips/spim-assembly.hh>
#include <target/target.hh>
#include <temp/temp.hh>
#include <tree/all.hh>

namespace target::mips
{
  using namespace tree;
  using namespace frame;

  /// Generate Mips code.
  class SpimCodegen : public target::Codegen
  {
  public:
    using super_type = target::Codegen;

    /// Construct a MIPS code generator.
    SpimCodegen(bool rule_trace_p = false);

    /// Define the targeted Cpu.
    void cpu_set(const target::mips::Cpu& cpu);
    /// Access concrete CPU.
    const target::mips::Cpu* cpu_get();

    /// Set the MIPS assembly language to use.
    void assembly_set(SpimAssembly& assembly);
    /// Access the current concrete assembly language.
    SpimAssembly& assembly_get();

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
    void
    rewrite_program(assem::ProcFrag& frag2rw,
                    const temp::temp_set_type& spilled_trees) const override;

  protected:
    /** \brief Emit an instruction to save \a word at the adress
        \a addr + the offset stored in the access (which is, in fact,
        an InFrame).

        ACCESS is of course an InFrame, but prototyped as Access to
        factor the dynamic_casts in here.  */
    assem::Instrs store_inframe(const frame::Access* access,
                                const temp::Temp& word,
                                const temp::Temp& addr) const;
    /** \brief same as store_inframe() except that it emit an instruction
        to load a word.  */
    assem::Instrs load_inframe(const frame::Access* access,
                               const temp::Temp& word,
                               const temp::Temp& addr) const;

    /// Entry point for code generation
    void codegen(const tree::rStm& root) override;

  protected:
    /// The current Cpu with its real type: NolimipsCpu.
    const target::mips::Cpu* cpu_;

    /// Assembly language.
    SpimAssembly* assembly_;
  }; // class SpimCodegen

  /** Current codegen running monoburg.  It has to be defined in the
      header for mono_burg_emit_N to know about it. */
  extern SpimCodegen* cg;
} // namespace target::mips

// Monoburg types.
#define MBTREE_TYPE rTree
#define MBCGEN_TYPE int
#define MBCOST_DATA void*

// Monoburg operators for tree manipulation.
#define MBTREE_OP(t) (static_cast<unsigned>((*t)->kind_get()))
#define MBTREE_LEFT(t)                                                         \
  ((*t)->children_get().empty() ? nullptr : &((*t)->left_get()))
#define MBTREE_RIGHT(t)                                                        \
  ((*t)->children_get().size() < 2 ? nullptr : &((*t)->right_get()))
#define MBTREE_STATE(t) ((*t)->state_get())

// Convenient macros for Monoburg use of SpimCodegen's methods.
#define EMIT (cg->emit)
#define MIPS_ASSEMBLY (cg->assembly_get())
#define FRAME (cg->frame_get())
#define MCPU (*(cg->cpu_get()))
#define REDUCE (cg->reduce)

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#ifndef guint8
# define guint8 unsigned char
#endif /* !guint8 */
#ifndef guint16
# define guint16 unsigned short
#endif /* !guint16 */
#ifndef gpointer
# define gpointer void*
#endif /* !gpointer */

#ifndef g_new
inline static void *
mono_burg_xmalloc_ (size_t size)
{
       void *p;

       p = malloc (size);
       if (!p) {
               fprintf (stderr, "Not enough memory\n");
               exit (1);
       }
       return p;
}
# define g_new(struct_type, n_structs) ((struct_type *) mono_burg_xmalloc_ (sizeof(struct_type) * n_structs))
#endif /* !g_new */

#ifndef g_error
inline static int
mono_burg_error_ (const char *format, ...)
{
       int n = 0;
       va_list ap;

       n = fprintf (stderr, "Error: ");
       va_start (ap, format);
       n += vfprintf (stderr, format, ap);
       va_end (ap);

       return n;
}
# define g_error mono_burg_error_
#endif /* !g_error */
#ifndef g_assert
# define g_assert assert
#endif /* !g_assert */

#ifndef g_return_val_if_fail
# ifdef NDEBUG
#  define g_return_val_if_fail(expr, val)
# else /* !NDEBUG */
#  define g_return_val_if_fail(expr, val) do { if (! (expr)) return val; } while (0)
# endif /* NDEBUG */
#endif /* !g_return_val_if_fail */
#ifndef g_assert_not_reached
# define g_assert_not_reached(X) assert (!"Should not be there")
#endif /* !g_assert_not_reached */

#ifndef MBTREE_TYPE
#error MBTREE_TYPE undefined
#endif
#ifndef MBTREE_OP
#define MBTREE_OP(t) ((t)->op)
#endif
#ifndef MBTREE_LEFT
#define MBTREE_LEFT(t) ((t)->left)
#endif
#ifndef MBTREE_RIGHT
#define MBTREE_RIGHT(t) ((t)->right)
#endif
#ifndef MBTREE_STATE
#define MBTREE_STATE(t) ((t)->state)
#endif
#ifndef MBCGEN_TYPE
#define MBCGEN_TYPE int
#endif
#ifndef MBALLOC_STATE
#define MBALLOC_STATE g_new (MBState, 1)
#endif
#ifndef MBCOST_DATA
#define MBCOST_DATA gpointer
#endif

#define MBMAXCOST 32768

#define MBCOND(x) if (!(x)) return MBMAXCOST;

namespace target {
namespace mips {
typedef enum {
  MB_TERM_Const = 0,
  MB_TERM_Name = 1,
  MB_TERM_Temp = 2,
  MB_TERM_Binop = 3,
  MB_TERM_Mem = 4,
  MB_TERM_Call = 5,
  MB_TERM_Eseq = 6,
  MB_TERM_Move = 7,
  MB_TERM_Sxp = 8,
  MB_TERM_Jump = 9,
  MB_TERM_Cjump = 10,
  MB_TERM_Seq = 11,
  MB_TERM_Label = 12
} MBTerms;

typedef enum {
  MB_NTERM_stm = 1,
  MB_NTERM_exp = 2,
  MB_NTERM_binop = 3,
  MB_NTERM_call = 4,
  MB_NTERM_temp = 5,
  MB_NTERM_mem = 6,
  MB_NTERM_move = 7,
  MB_NTERM_cjump = 8
} MBNTerms;

#define MB_MAX_NTERMS  8

struct _MBState {
  int    op;
  struct _MBState  *left, *right;
  guint16    cost[9];
  unsigned int   rule_stm:3;
  unsigned int   rule_exp:3;
  unsigned int   rule_binop:2;
  unsigned int   rule_call:1;
  unsigned int   rule_temp:1;
  unsigned int   rule_mem:3;
  unsigned int   rule_move:4;
  unsigned int   rule_cjump:2;
};

typedef struct _MBState MBState;
typedef void (*MBEmitFunc) (MBTREE_TYPE &tree, MBCGEN_TYPE *s);


}
}
#endif /* TARGET_MIPS_CODEGEN */
