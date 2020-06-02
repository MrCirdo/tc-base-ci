#include "target/ia32/gas-codegen.hh"

namespace target {
namespace ia32 {
const guint8 mono_burg_arity [] = {
  0, /* Const */
  0, /* Name */
  0, /* Temp */
  2, /* Binop */
  1, /* Mem */
  0, /* Call */
  0, /* Eseq */
  2, /* Move */
  1, /* Sxp */
  0, /* Jump */
  2, /* Cjump */
  0, /* Seq */
  0, /* Label */
};

static const char * const mono_burg_rule_string [] = {
  NULL,
  "stm: Eseq",
  "binop: Binop(exp, Const)",
  "binop: Binop(exp, exp)",
  "exp: binop",
  "call: Call",
  "exp: call",
  "temp: Temp",
  "exp: temp",
  "mem: Mem(Binop(Const, exp))",
  "mem: Mem(Binop(exp, Const))",
  "mem: Mem(Binop(exp, exp))",
  "mem: Mem(Const)",
  "mem: Mem(exp)",
  "exp: mem",
  "exp: Const",
  "exp: Name",
  "move: Move(Mem(exp), Mem(exp))",
  "move: Move(Mem(Binop(Const, exp)), exp)",
  "move: Move(Mem(Binop(exp, Const)), exp)",
  "move: Move(Mem(binop), exp)",
  "move: Move(exp, Mem(Binop(Const, exp)))",
  "move: Move(exp, Mem(Binop(exp, Const)))",
  "move: Move(exp, Mem(binop))",
  "move: Move(Mem(Const), exp)",
  "move: Move(Mem(exp), exp)",
  "move: Move(temp, call)",
  "move: Move(temp, Const)",
  "move: Move(temp, Mem(Const))",
  "move: Move(temp, Mem(exp))",
  "move: Move(temp, exp)",
  "stm: move",
  "cjump: Cjump(exp, Const)",
  "cjump: Cjump(Const, exp)",
  "cjump: Cjump(exp, exp)",
  "stm: cjump",
  "stm: Sxp(exp)",
  "stm: Jump",
  "stm: Seq",
  "stm: Label",
};

static const guint16 mono_burg_nts_0 [] = { 0 };
static const guint16 mono_burg_nts_1 [] = { MB_NTERM_exp, 0 };
static const guint16 mono_burg_nts_2 [] = { MB_NTERM_exp, MB_NTERM_exp, 0 };
static const guint16 mono_burg_nts_3 [] = { MB_NTERM_binop, 0 };
static const guint16 mono_burg_nts_4 [] = { MB_NTERM_call, 0 };
static const guint16 mono_burg_nts_5 [] = { MB_NTERM_temp, 0 };
static const guint16 mono_burg_nts_6 [] = { MB_NTERM_mem, 0 };
static const guint16 mono_burg_nts_7 [] = { MB_NTERM_binop, MB_NTERM_exp, 0 };
static const guint16 mono_burg_nts_8 [] = { MB_NTERM_exp, MB_NTERM_binop, 0 };
static const guint16 mono_burg_nts_9 [] = { MB_NTERM_temp, MB_NTERM_call, 0 };
static const guint16 mono_burg_nts_10 [] = { MB_NTERM_temp, MB_NTERM_exp, 0 };
static const guint16 mono_burg_nts_11 [] = { MB_NTERM_move, 0 };
static const guint16 mono_burg_nts_12 [] = { MB_NTERM_cjump, 0 };

static const guint16 *const mono_burg_nts [] = {
  0,
  mono_burg_nts_0, /* stm: Eseq */
  mono_burg_nts_1, /* binop: Binop(exp, Const) */
  mono_burg_nts_2, /* binop: Binop(exp, exp) */
  mono_burg_nts_3, /* exp: binop */
  mono_burg_nts_0, /* call: Call */
  mono_burg_nts_4, /* exp: call */
  mono_burg_nts_0, /* temp: Temp */
  mono_burg_nts_5, /* exp: temp */
  mono_burg_nts_1, /* mem: Mem(Binop(Const, exp)) */
  mono_burg_nts_1, /* mem: Mem(Binop(exp, Const)) */
  mono_burg_nts_2, /* mem: Mem(Binop(exp, exp)) */
  mono_burg_nts_0, /* mem: Mem(Const) */
  mono_burg_nts_1, /* mem: Mem(exp) */
  mono_burg_nts_6, /* exp: mem */
  mono_burg_nts_0, /* exp: Const */
  mono_burg_nts_0, /* exp: Name */
  mono_burg_nts_2, /* move: Move(Mem(exp), Mem(exp)) */
  mono_burg_nts_2, /* move: Move(Mem(Binop(Const, exp)), exp) */
  mono_burg_nts_2, /* move: Move(Mem(Binop(exp, Const)), exp) */
  mono_burg_nts_7, /* move: Move(Mem(binop), exp) */
  mono_burg_nts_2, /* move: Move(exp, Mem(Binop(Const, exp))) */
  mono_burg_nts_2, /* move: Move(exp, Mem(Binop(exp, Const))) */
  mono_burg_nts_8, /* move: Move(exp, Mem(binop)) */
  mono_burg_nts_1, /* move: Move(Mem(Const), exp) */
  mono_burg_nts_2, /* move: Move(Mem(exp), exp) */
  mono_burg_nts_9, /* move: Move(temp, call) */
  mono_burg_nts_5, /* move: Move(temp, Const) */
  mono_burg_nts_5, /* move: Move(temp, Mem(Const)) */
  mono_burg_nts_10, /* move: Move(temp, Mem(exp)) */
  mono_burg_nts_10, /* move: Move(temp, exp) */
  mono_burg_nts_11, /* stm: move */
  mono_burg_nts_1, /* cjump: Cjump(exp, Const) */
  mono_burg_nts_1, /* cjump: Cjump(Const, exp) */
  mono_burg_nts_2, /* cjump: Cjump(exp, exp) */
  mono_burg_nts_12, /* stm: cjump */
  mono_burg_nts_1, /* stm: Sxp(exp) */
  mono_burg_nts_0, /* stm: Jump */
  mono_burg_nts_0, /* stm: Seq */
  mono_burg_nts_0, /* stm: Label */
};

static int mono_burg_rule (MBState *state, int goal);
static void /* stm: Eseq */
mono_burg_emit_0 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  {
#line 25 "target/ia32/tree.brg"

  unreachable();

  }
  }
}

static void /* binop: Binop(exp, Const) */
mono_burg_emit_1 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &left = *(MBTREE_LEFT((&tree)));
  MBTREE_TYPE &right = *(MBTREE_RIGHT((&tree)));
  (void) left;
  (void) right;
  {
#line 4 "target/ia32/binop.brg"

  auto binop = tree.cast<Binop>();
  auto cst = right.cast<Const>();

  EMIT(IA32_ASSEMBLY.binop_build(binop->oper_get(),
                                 left->asm_get(),
                                 cst->value_get(),
                                 tree->asm_get()));

  }
  }
}

static void /* binop: Binop(exp, exp) */
mono_burg_emit_2 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &left = *(MBTREE_LEFT((&tree)));
  MBTREE_TYPE &right = *(MBTREE_RIGHT((&tree)));
  (void) left;
  (void) right;
  {
#line 15 "target/ia32/binop.brg"

  auto binop = tree.cast<Binop>();

  EMIT(IA32_ASSEMBLY.binop_build(binop->oper_get(),
                                 left->asm_get(),
                                 right->asm_get(),
                                 tree->asm_get()));

  }
  }
}

static void /* call: Call */
mono_burg_emit_4 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  {
#line 4 "target/ia32/call.brg"

  auto call = tree.cast<Call>();
  tree_list_type& children = call->children_get();
  auto function = children.begin()->cast<Name>();

  // Consider that an IA-32 CPU does not have registers dedicated to
  // argument storage

  // FIXME: Some code was deleted here (Store all the arguments in frame).

  // Now all the arguments are stored, we can safely jump to the
  // label (i.e. the function).
  temp::temp_list_type res(MCPU.caller_save_regs().begin(),
                           MCPU.caller_save_regs().end());
  res.emplace_back(MCPU.result_reg());
  EMIT(IA32_ASSEMBLY.call_build(function->label_get(), res));

  tree->asm_set(MCPU.result_reg());

  }
  }
}

static void /* temp: Temp */
mono_burg_emit_6 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  {
#line 4 "target/ia32/temp.brg"

  auto temp = tree.cast<Temp>();

  temp->asm_set(temp->temp_get());

  }
  }
}

static void /* mem: Mem(Binop(Const, exp)) */
mono_burg_emit_8 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &binop = *(MBTREE_LEFT((&tree)));
  MBTREE_TYPE &right = *(MBTREE_RIGHT(MBTREE_LEFT((&tree))));
  (void) binop;
  (void) right;
  {
#line 4 "target/ia32/mem.brg"

  rTree move = new tree::Move(new tree::Temp(tree->asm_get()),
                              new tree::Mem(binop.cast<Binop>()));
  right->reducible_set(false);
  REDUCE(move, MB_NTERM_move);
  right->reducible_set(true);

  }
  }
}

static void /* mem: Mem(Binop(exp, Const)) */
mono_burg_emit_9 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &binop = *(MBTREE_LEFT((&tree)));
  MBTREE_TYPE &left = *(MBTREE_LEFT(MBTREE_LEFT((&tree))));
  (void) binop;
  (void) left;
  {
#line 13 "target/ia32/mem.brg"

  rTree move = new tree::Move(new tree::Temp(tree->asm_get()),
                              new tree::Mem(binop.cast<Binop>()));
  left->reducible_set(false);
  REDUCE(move, MB_NTERM_move);
  left->reducible_set(true);

  }
  }
}

static void /* mem: Mem(Binop(exp, exp)) */
mono_burg_emit_10 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &binop = *(MBTREE_LEFT((&tree)));
  MBTREE_TYPE &left = *(MBTREE_LEFT(MBTREE_LEFT((&tree))));
  MBTREE_TYPE &right = *(MBTREE_RIGHT(MBTREE_LEFT((&tree))));
  (void) binop;
  (void) left;
  (void) right;
  {
#line 22 "target/ia32/mem.brg"

  rTree move = new tree::Move(new tree::Temp(tree->asm_get()),
                              new tree::Mem(binop.cast<Binop>()));
  left->reducible_set(false);
  right->reducible_set(false);
  REDUCE(move, MB_NTERM_move);
  left->reducible_set(true);
  right->reducible_set(true);

  }
  }
}

static void /* mem: Mem(Const) */
mono_burg_emit_11 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &c = *(MBTREE_LEFT((&tree)));
  (void) c;
  {
#line 34 "target/ia32/mem.brg"

  EMIT(IA32_ASSEMBLY.load_build(c.cast<Const>()->value_get(), tree->asm_get()));

  }
  }
}

static void /* mem: Mem(exp) */
mono_burg_emit_12 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &e = *(MBTREE_LEFT((&tree)));
  (void) e;
  {
#line 39 "target/ia32/mem.brg"

  temp::Temp res;

  EMIT(IA32_ASSEMBLY.load_build(e->asm_get(), res));
  tree->asm_set(res);

  }
  }
}

static void /* exp: Const */
mono_burg_emit_14 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  {
#line 16 "target/ia32/exp.brg"

  auto cst = tree.cast<Const>();
  EMIT(IA32_ASSEMBLY.move_build(cst->value_get(), cst->asm_get()));

  }
  }
}

static void /* exp: Name */
mono_burg_emit_15 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  {
#line 22 "target/ia32/exp.brg"

  auto name = tree.cast<Name>();
  EMIT(IA32_ASSEMBLY.move_build(name->label_get(), name->asm_get()));

  }
  }
}

static void /* move: Move(Mem(exp), Mem(exp)) */
mono_burg_emit_16 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &e1 = *(MBTREE_LEFT(MBTREE_LEFT((&tree))));
  MBTREE_TYPE &e2 = *(MBTREE_LEFT(MBTREE_RIGHT((&tree))));
  (void) e1;
  (void) e2;
  {
#line 5 "target/ia32/move.brg"

  temp::Temp rval;

  rExp exp = e2.cast<Exp>();
  assertion(exp);
  EMIT(IA32_ASSEMBLY.load_build(exp->asm_get(), rval));

  exp = e1.cast<Exp>();
  assertion(exp);
  EMIT(IA32_ASSEMBLY.store_build(rval, exp->asm_get()));

  }
  }
}

static void /* move: Move(Mem(Binop(Const, exp)), exp) */
mono_burg_emit_17 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  {
#line 5 "target/ia32/move_store.brg"

  auto binop = tree->left_get()->left_get().cast<Binop>();

  precondition(binop->oper_get() == Binop::Oper::sub or
               binop->oper_get() == Binop::Oper::add);

  rExp binop_left = binop->left_get();
  rExp binop_right = binop->right_get();
  if (binop_right->kind_get() == Tree::kind_tree_type::const_kind)
    binop_left.swap(binop_right);
  auto const_left = binop_left.cast<Const>();
  short sign = 1;

  precondition(binop_right);
  precondition(binop_left);

  if(binop->oper_get() == Binop::Oper::sub)
    sign = -1;
  EMIT(IA32_ASSEMBLY.store_build(tree->right_get()->asm_get(),
                                 binop_right->asm_get(),
                                 sign * const_left->value_get()));

  }
  }
}

/* move: Move(Mem(Binop(exp, Const)), exp) */
#define mono_burg_emit_18 mono_burg_emit_17

static void /* move: Move(Mem(binop), exp) */
mono_burg_emit_19 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &b = *(MBTREE_LEFT(MBTREE_LEFT((&tree))));
  MBTREE_TYPE &e = *(MBTREE_RIGHT((&tree)));
  (void) b;
  (void) e;
  {
#line 29 "target/ia32/move_store.brg"

  EMIT(IA32_ASSEMBLY.store_build(e->asm_get(), b->asm_get()));

  }
  }
}

static void /* move: Move(exp, Mem(Binop(Const, exp))) */
mono_burg_emit_20 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &b = *(MBTREE_LEFT(MBTREE_RIGHT((&tree))));
  MBTREE_TYPE &binop_left = *(MBTREE_LEFT(MBTREE_LEFT(MBTREE_RIGHT((&tree)))));
  MBTREE_TYPE &binop_right = *(MBTREE_RIGHT(MBTREE_LEFT(MBTREE_RIGHT((&tree)))));
  (void) b;
  (void) binop_left;
  (void) binop_right;
  {
#line 4 "target/ia32/move_load.brg"

  auto binop = b.cast<Binop>();

  precondition(binop->oper_get() == Binop::Oper::sub or
               binop->oper_get() == Binop::Oper::add);

  auto const_left = binop_left.cast<Const>();
  short sign = 1;

  precondition(binop_right);
  precondition(binop_left);

  if (binop->oper_get() == Binop::Oper::sub)
    sign = -1;
  EMIT(IA32_ASSEMBLY.load_build(binop_right->asm_get(),
                                sign * const_left->value_get(),
                                tree->left_get()->asm_get()));

  }
  }
}

static void /* move: Move(exp, Mem(Binop(exp, Const))) */
mono_burg_emit_21 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &b = *(MBTREE_LEFT(MBTREE_RIGHT((&tree))));
  MBTREE_TYPE &binop_left = *(MBTREE_LEFT(MBTREE_LEFT(MBTREE_RIGHT((&tree)))));
  MBTREE_TYPE &binop_right = *(MBTREE_RIGHT(MBTREE_LEFT(MBTREE_RIGHT((&tree)))));
  (void) b;
  (void) binop_left;
  (void) binop_right;
  {
#line 24 "target/ia32/move_load.brg"

  auto binop = b.cast<Binop>();

  precondition(binop->oper_get() == Binop::Oper::sub or
               binop->oper_get() == Binop::Oper::add);

  auto const_right = binop_right.cast<Const>();
  short sign = 1;

  precondition(binop_right);
  precondition(binop_left);

  if (binop->oper_get() == Binop::Oper::sub)
    sign = -1;
  EMIT(IA32_ASSEMBLY.load_build(binop_left->asm_get(),
                                sign * const_right->value_get(),
                                tree->left_get()->asm_get()));

  }
  }
}

static void /* move: Move(exp, Mem(binop)) */
mono_burg_emit_22 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &e = *(MBTREE_LEFT((&tree)));
  MBTREE_TYPE &b = *(MBTREE_LEFT(MBTREE_RIGHT((&tree))));
  (void) e;
  (void) b;
  {
#line 44 "target/ia32/move_load.brg"

  EMIT(IA32_ASSEMBLY.load_build(b->asm_get(), e->asm_get()));

  }
  }
}

static void /* move: Move(Mem(Const), exp) */
mono_burg_emit_23 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &c = *(MBTREE_LEFT(MBTREE_LEFT((&tree))));
  MBTREE_TYPE &e = *(MBTREE_RIGHT((&tree)));
  (void) c;
  (void) e;
  {
#line 21 "target/ia32/move.brg"

  // FIXME: Some code was deleted here.

  }
  }
}

static void /* move: Move(Mem(exp), exp) */
mono_burg_emit_24 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &e1 = *(MBTREE_LEFT(MBTREE_LEFT((&tree))));
  MBTREE_TYPE &e2 = *(MBTREE_RIGHT((&tree)));
  (void) e1;
  (void) e2;
  {
#line 28 "target/ia32/move.brg"

  EMIT(IA32_ASSEMBLY.store_build(e2->asm_get(), e1->asm_get()));

  }
  }
}

static void /* move: Move(temp, call) */
mono_burg_emit_25 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &dst = *(MBTREE_LEFT((&tree)));
  MBTREE_TYPE &src = *(MBTREE_RIGHT((&tree)));
  (void) dst;
  (void) src;
  {
#line 33 "target/ia32/move.brg"

  EMIT(IA32_ASSEMBLY.move_build(src->asm_get(), dst->asm_get()));

  }
  }
}

static void /* move: Move(temp, Const) */
mono_burg_emit_26 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &dst = *(MBTREE_LEFT((&tree)));
  MBTREE_TYPE &src = *(MBTREE_RIGHT((&tree)));
  (void) dst;
  (void) src;
  {
#line 38 "target/ia32/move.brg"

  EMIT(IA32_ASSEMBLY.move_build(src.cast<Const>()->value_get(),
                                dst->asm_get()));

  }
  }
}

static void /* move: Move(temp, Mem(Const)) */
mono_burg_emit_27 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &dst = *(MBTREE_LEFT((&tree)));
  MBTREE_TYPE &c = *(MBTREE_LEFT(MBTREE_RIGHT((&tree))));
  (void) dst;
  (void) c;
  {
#line 44 "target/ia32/move.brg"

  EMIT(IA32_ASSEMBLY.load_build(c.cast<Const>()->value_get(),
                                dst->asm_get()));

  }
  }
}

static void /* move: Move(temp, Mem(exp)) */
mono_burg_emit_28 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &dst = *(MBTREE_LEFT((&tree)));
  MBTREE_TYPE &e = *(MBTREE_LEFT(MBTREE_RIGHT((&tree))));
  (void) dst;
  (void) e;
  {
#line 50 "target/ia32/move.brg"

  EMIT(IA32_ASSEMBLY.load_build(e->asm_get(), dst->asm_get()));

  }
  }
}

static void /* move: Move(temp, exp) */
mono_burg_emit_29 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &dst = *(MBTREE_LEFT((&tree)));
  MBTREE_TYPE &src = *(MBTREE_RIGHT((&tree)));
  (void) dst;
  (void) src;
  {
#line 55 "target/ia32/move.brg"

  // FIXME: Some code was deleted here.

  }
  }
}

static void /* cjump: Cjump(exp, Const) */
mono_burg_emit_31 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &e = *(MBTREE_LEFT((&tree)));
  MBTREE_TYPE &c = *(MBTREE_RIGHT((&tree)));
  (void) e;
  (void) c;
  {
#line 4 "target/ia32/cjump.brg"

  auto cjump = tree.cast<Cjump>();
  auto cst = c.cast<Const>();

  EMIT(IA32_ASSEMBLY.cjump_build(cjump->relop_get(),
                                 e->asm_get(),
                                 cst->value_get(),
                                 cjump->label_true_get(),
                                 cjump->label_false_get()));

  }
  }
}

static void /* cjump: Cjump(Const, exp) */
mono_burg_emit_32 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &c = *(MBTREE_LEFT((&tree)));
  MBTREE_TYPE &e = *(MBTREE_RIGHT((&tree)));
  (void) c;
  (void) e;
  {
#line 16 "target/ia32/cjump.brg"

  auto cjump = tree.cast<Cjump>();
  auto cst = c.cast<Const>();

  EMIT(IA32_ASSEMBLY.cjump_build(cjump->relop_get(),
                                 cst->value_get(),
                                 e->asm_get(),
                                 cjump->label_true_get(),
                                 cjump->label_false_get()));

  }
  }
}

static void /* cjump: Cjump(exp, exp) */
mono_burg_emit_33 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  MBTREE_TYPE &e1 = *(MBTREE_LEFT((&tree)));
  MBTREE_TYPE &e2 = *(MBTREE_RIGHT((&tree)));
  (void) e1;
  (void) e2;
  {
#line 28 "target/ia32/cjump.brg"

  auto cjump = tree.cast<Cjump>();

  EMIT(IA32_ASSEMBLY.cjump_build(cjump->relop_get(),
                                 e1->asm_get(),
                                 e2->asm_get(),
                                 cjump->label_true_get(),
                                 cjump->label_false_get()));

  }
  }
}

static void /* stm: Jump */
mono_burg_emit_36 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  {
#line 12 "target/ia32/stm.brg"

  auto jump = tree.cast<Jump>();
  temp::Label dest = jump->label_get().front();
  EMIT(IA32_ASSEMBLY.jump_build(dest));

  }
  }
}

static void /* stm: Seq */
mono_burg_emit_37 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  {
#line 19 "target/ia32/stm.brg"

  tree_list_type& children = tree->children_get();
  for (rTree& t : children)
    REDUCE(t, MB_NTERM_stm);

  }
  }
}

static void /* stm: Label */
mono_burg_emit_38 (MBTREE_TYPE &tree, MBCGEN_TYPE *s)
{
  (void) tree; (void) s;
  {
  {
#line 26 "target/ia32/stm.brg"

  auto lab = tree.cast<Label>();
  EMIT(IA32_ASSEMBLY.label_build(lab->label_get()));

  }
  }
}

static MBEmitFunc const mono_burg_func [] = {
  NULL,
  mono_burg_emit_0,
  mono_burg_emit_1,
  mono_burg_emit_2,
  NULL,
  mono_burg_emit_4,
  NULL,
  mono_burg_emit_6,
  NULL,
  mono_burg_emit_8,
  mono_burg_emit_9,
  mono_burg_emit_10,
  mono_burg_emit_11,
  mono_burg_emit_12,
  NULL,
  mono_burg_emit_14,
  mono_burg_emit_15,
  mono_burg_emit_16,
  mono_burg_emit_17,
  mono_burg_emit_18,
  mono_burg_emit_19,
  mono_burg_emit_20,
  mono_burg_emit_21,
  mono_burg_emit_22,
  mono_burg_emit_23,
  mono_burg_emit_24,
  mono_burg_emit_25,
  mono_burg_emit_26,
  mono_burg_emit_27,
  mono_burg_emit_28,
  mono_burg_emit_29,
  NULL,
  mono_burg_emit_31,
  mono_burg_emit_32,
  mono_burg_emit_33,
  NULL,
  NULL,
  mono_burg_emit_36,
  mono_burg_emit_37,
  mono_burg_emit_38,
};

const int mono_burg_decode_stm[] = {
  0,
  1,
  31,
  35,
  36,
  37,
  38,
  39,
};

const int mono_burg_decode_exp[] = {
  0,
  4,
  6,
  8,
  14,
  15,
  16,
};

const int mono_burg_decode_binop[] = {
  0,
  2,
  3,
};

const int mono_burg_decode_call[] = {
  0,
  5,
};

const int mono_burg_decode_temp[] = {
  0,
  7,
};

const int mono_burg_decode_mem[] = {
  0,
  9,
  10,
  11,
  12,
  13,
};

const int mono_burg_decode_move[] = {
  0,
  17,
  18,
  19,
  20,
  21,
  22,
  23,
  24,
  25,
  26,
  27,
  28,
  29,
  30,
};

const int mono_burg_decode_cjump[] = {
  0,
  32,
  33,
  34,
};

static void closure_binop (MBState *p, int c);
static void closure_call (MBState *p, int c);
static void closure_temp (MBState *p, int c);
static void closure_mem (MBState *p, int c);
static void closure_move (MBState *p, int c);
static void closure_cjump (MBState *p, int c);

static void
closure_binop (MBState *p, int c)
{
  /* exp: binop */
  if (c + 0 < p->cost[MB_NTERM_exp]) {
    p->cost[MB_NTERM_exp] = c + 0;
    p->rule_exp = 1;
  }
}

static void
closure_call (MBState *p, int c)
{
  /* exp: call */
  if (c + 0 < p->cost[MB_NTERM_exp]) {
    p->cost[MB_NTERM_exp] = c + 0;
    p->rule_exp = 2;
  }
}

static void
closure_temp (MBState *p, int c)
{
  /* exp: temp */
  if (c + 0 < p->cost[MB_NTERM_exp]) {
    p->cost[MB_NTERM_exp] = c + 0;
    p->rule_exp = 3;
  }
}

static void
closure_mem (MBState *p, int c)
{
  /* exp: mem */
  if (c + 0 < p->cost[MB_NTERM_exp]) {
    p->cost[MB_NTERM_exp] = c + 0;
    p->rule_exp = 4;
  }
}

static void
closure_move (MBState *p, int c)
{
  /* stm: move */
  if (c + 0 < p->cost[MB_NTERM_stm]) {
    p->cost[MB_NTERM_stm] = c + 0;
    p->rule_stm = 2;
  }
}

static void
closure_cjump (MBState *p, int c)
{
  /* stm: cjump */
  if (c + 0 < p->cost[MB_NTERM_stm]) {
    p->cost[MB_NTERM_stm] = c + 0;
    p->rule_stm = 3;
  }
}

static MBState *
mono_burg_label_priv (MBTREE_TYPE *tree, MBCOST_DATA *data) {
  int arity;
  int c;
  MBState *p;
  MBState *left = NULL, *right = NULL;

  switch (mono_burg_arity [MBTREE_OP(tree)]) {
  case 0:
    break;
  case 1:
    left = mono_burg_label_priv (MBTREE_LEFT(tree), data);
    right = NULL;
    break;
  case 2:
    left = mono_burg_label_priv (MBTREE_LEFT(tree), data);
    right = mono_burg_label_priv (MBTREE_RIGHT(tree), data);
  }

  arity = (left != NULL) + (right != NULL);
  g_assert (arity == mono_burg_arity [MBTREE_OP(tree)]);
  (void)arity;

  p = MBALLOC_STATE;
  memset (p, 0, sizeof (MBState));
  p->op = MBTREE_OP(tree);
  p->left = left;
  p->right = right;
  p->cost [1] = 32767;
  p->cost [2] = 32767;
  p->cost [3] = 32767;
  p->cost [4] = 32767;
  p->cost [5] = 32767;
  p->cost [6] = 32767;
  p->cost [7] = 32767;
  p->cost [8] = 32767;

  switch (MBTREE_OP(tree)) {
  case 0: /* Const */
    /* exp: Const */
    {
      c = 0;
      if (c < p->cost[MB_NTERM_exp]) {
        p->cost[MB_NTERM_exp] = c;
        p->rule_exp = 5;
      }
    }
    break;
  case 1: /* Name */
    /* exp: Name */
    {
      c = 0;
      if (c < p->cost[MB_NTERM_exp]) {
        p->cost[MB_NTERM_exp] = c;
        p->rule_exp = 6;
      }
    }
    break;
  case 2: /* Temp */
    /* temp: Temp */
    {
      c = 0;
      if (c < p->cost[MB_NTERM_temp]) {
        p->cost[MB_NTERM_temp] = c;
        p->rule_temp = 1;
        closure_temp (p, c);
      }
    }
    break;
  case 3: /* Binop */
    /* binop: Binop(exp, Const) */
    if (
      p->right->op == 0 /* Const */
    )
    {
      c = left->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_binop]) {
        p->cost[MB_NTERM_binop] = c;
        p->rule_binop = 1;
        closure_binop (p, c);
      }
    }
    /* binop: Binop(exp, exp) */
    {
      c = left->cost[MB_NTERM_exp] + right->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_binop]) {
        p->cost[MB_NTERM_binop] = c;
        p->rule_binop = 2;
        closure_binop (p, c);
      }
    }
    break;
  case 4: /* Mem */
    /* mem: Mem(Binop(Const, exp)) */
    if (
      p->left->op == 3 /* Binop */ &&
      p->left->left->op == 0 /* Const */
    )
    {
      c = left->right->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_mem]) {
        p->cost[MB_NTERM_mem] = c;
        p->rule_mem = 1;
        closure_mem (p, c);
      }
    }
    /* mem: Mem(Binop(exp, Const)) */
    if (
      p->left->op == 3 /* Binop */ &&
      p->left->right->op == 0 /* Const */
    )
    {
      c = left->left->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_mem]) {
        p->cost[MB_NTERM_mem] = c;
        p->rule_mem = 2;
        closure_mem (p, c);
      }
    }
    /* mem: Mem(Binop(exp, exp)) */
    if (
      p->left->op == 3 /* Binop */
    )
    {
      c = left->left->cost[MB_NTERM_exp] + left->right->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_mem]) {
        p->cost[MB_NTERM_mem] = c;
        p->rule_mem = 3;
        closure_mem (p, c);
      }
    }
    /* mem: Mem(Const) */
    if (
      p->left->op == 0 /* Const */
    )
    {
      c = 0;
      if (c < p->cost[MB_NTERM_mem]) {
        p->cost[MB_NTERM_mem] = c;
        p->rule_mem = 4;
        closure_mem (p, c);
      }
    }
    /* mem: Mem(exp) */
    {
      c = left->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_mem]) {
        p->cost[MB_NTERM_mem] = c;
        p->rule_mem = 5;
        closure_mem (p, c);
      }
    }
    break;
  case 5: /* Call */
    /* call: Call */
    {
      c = 0;
      if (c < p->cost[MB_NTERM_call]) {
        p->cost[MB_NTERM_call] = c;
        p->rule_call = 1;
        closure_call (p, c);
      }
    }
    break;
  case 6: /* Eseq */
    /* stm: Eseq */
    {
      c = 0;
      if (c < p->cost[MB_NTERM_stm]) {
        p->cost[MB_NTERM_stm] = c;
        p->rule_stm = 1;
      }
    }
    break;
  case 7: /* Move */
    /* move: Move(Mem(exp), Mem(exp)) */
    if (
      p->left->op == 4 /* Mem */ &&
      p->right->op == 4 /* Mem */
    )
    {
      c = left->left->cost[MB_NTERM_exp] + right->left->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_move]) {
        p->cost[MB_NTERM_move] = c;
        p->rule_move = 1;
        closure_move (p, c);
      }
    }
    /* move: Move(Mem(Binop(Const, exp)), exp) */
    if (
      p->left->op == 4 /* Mem */ &&
      p->left->left->op == 3 /* Binop */ &&
      p->left->left->left->op == 0 /* Const */
    )
    {
      c = left->left->right->cost[MB_NTERM_exp] + right->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_move]) {
        p->cost[MB_NTERM_move] = c;
        p->rule_move = 2;
        closure_move (p, c);
      }
    }
    /* move: Move(Mem(Binop(exp, Const)), exp) */
    if (
      p->left->op == 4 /* Mem */ &&
      p->left->left->op == 3 /* Binop */ &&
      p->left->left->right->op == 0 /* Const */
    )
    {
      c = left->left->left->cost[MB_NTERM_exp] + right->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_move]) {
        p->cost[MB_NTERM_move] = c;
        p->rule_move = 3;
        closure_move (p, c);
      }
    }
    /* move: Move(Mem(binop), exp) */
    if (
      p->left->op == 4 /* Mem */
    )
    {
      c = left->left->cost[MB_NTERM_binop] + right->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_move]) {
        p->cost[MB_NTERM_move] = c;
        p->rule_move = 4;
        closure_move (p, c);
      }
    }
    /* move: Move(exp, Mem(Binop(Const, exp))) */
    if (
      p->right->op == 4 /* Mem */ &&
      p->right->left->op == 3 /* Binop */ &&
      p->right->left->left->op == 0 /* Const */
    )
    {
      c = left->cost[MB_NTERM_exp] + right->left->right->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_move]) {
        p->cost[MB_NTERM_move] = c;
        p->rule_move = 5;
        closure_move (p, c);
      }
    }
    /* move: Move(exp, Mem(Binop(exp, Const))) */
    if (
      p->right->op == 4 /* Mem */ &&
      p->right->left->op == 3 /* Binop */ &&
      p->right->left->right->op == 0 /* Const */
    )
    {
      c = left->cost[MB_NTERM_exp] + right->left->left->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_move]) {
        p->cost[MB_NTERM_move] = c;
        p->rule_move = 6;
        closure_move (p, c);
      }
    }
    /* move: Move(exp, Mem(binop)) */
    if (
      p->right->op == 4 /* Mem */
    )
    {
      c = left->cost[MB_NTERM_exp] + right->left->cost[MB_NTERM_binop] + 0;
      if (c < p->cost[MB_NTERM_move]) {
        p->cost[MB_NTERM_move] = c;
        p->rule_move = 7;
        closure_move (p, c);
      }
    }
    /* move: Move(Mem(Const), exp) */
    if (
      p->left->op == 4 /* Mem */ &&
      p->left->left->op == 0 /* Const */
    )
    {
      c = right->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_move]) {
        p->cost[MB_NTERM_move] = c;
        p->rule_move = 8;
        closure_move (p, c);
      }
    }
    /* move: Move(Mem(exp), exp) */
    if (
      p->left->op == 4 /* Mem */
    )
    {
      c = left->left->cost[MB_NTERM_exp] + right->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_move]) {
        p->cost[MB_NTERM_move] = c;
        p->rule_move = 9;
        closure_move (p, c);
      }
    }
    /* move: Move(temp, call) */
    {
      c = left->cost[MB_NTERM_temp] + right->cost[MB_NTERM_call] + 0;
      if (c < p->cost[MB_NTERM_move]) {
        p->cost[MB_NTERM_move] = c;
        p->rule_move = 10;
        closure_move (p, c);
      }
    }
    /* move: Move(temp, Const) */
    if (
      p->right->op == 0 /* Const */
    )
    {
      c = left->cost[MB_NTERM_temp] + 0;
      if (c < p->cost[MB_NTERM_move]) {
        p->cost[MB_NTERM_move] = c;
        p->rule_move = 11;
        closure_move (p, c);
      }
    }
    /* move: Move(temp, Mem(Const)) */
    if (
      p->right->op == 4 /* Mem */ &&
      p->right->left->op == 0 /* Const */
    )
    {
      c = left->cost[MB_NTERM_temp] + 0;
      if (c < p->cost[MB_NTERM_move]) {
        p->cost[MB_NTERM_move] = c;
        p->rule_move = 12;
        closure_move (p, c);
      }
    }
    /* move: Move(temp, Mem(exp)) */
    if (
      p->right->op == 4 /* Mem */
    )
    {
      c = left->cost[MB_NTERM_temp] + right->left->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_move]) {
        p->cost[MB_NTERM_move] = c;
        p->rule_move = 13;
        closure_move (p, c);
      }
    }
    /* move: Move(temp, exp) */
    {
      c = left->cost[MB_NTERM_temp] + right->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_move]) {
        p->cost[MB_NTERM_move] = c;
        p->rule_move = 14;
        closure_move (p, c);
      }
    }
    break;
  case 8: /* Sxp */
    /* stm: Sxp(exp) */
    {
      c = left->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_stm]) {
        p->cost[MB_NTERM_stm] = c;
        p->rule_stm = 4;
      }
    }
    break;
  case 9: /* Jump */
    /* stm: Jump */
    {
      c = 0;
      if (c < p->cost[MB_NTERM_stm]) {
        p->cost[MB_NTERM_stm] = c;
        p->rule_stm = 5;
      }
    }
    break;
  case 10: /* Cjump */
    /* cjump: Cjump(exp, Const) */
    if (
      p->right->op == 0 /* Const */
    )
    {
      c = left->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_cjump]) {
        p->cost[MB_NTERM_cjump] = c;
        p->rule_cjump = 1;
        closure_cjump (p, c);
      }
    }
    /* cjump: Cjump(Const, exp) */
    if (
      p->left->op == 0 /* Const */
    )
    {
      c = right->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_cjump]) {
        p->cost[MB_NTERM_cjump] = c;
        p->rule_cjump = 2;
        closure_cjump (p, c);
      }
    }
    /* cjump: Cjump(exp, exp) */
    {
      c = left->cost[MB_NTERM_exp] + right->cost[MB_NTERM_exp] + 0;
      if (c < p->cost[MB_NTERM_cjump]) {
        p->cost[MB_NTERM_cjump] = c;
        p->rule_cjump = 3;
        closure_cjump (p, c);
      }
    }
    break;
  case 11: /* Seq */
    /* stm: Seq */
    {
      c = 0;
      if (c < p->cost[MB_NTERM_stm]) {
        p->cost[MB_NTERM_stm] = c;
        p->rule_stm = 6;
      }
    }
    break;
  case 12: /* Label */
    /* stm: Label */
    {
      c = 0;
      if (c < p->cost[MB_NTERM_stm]) {
        p->cost[MB_NTERM_stm] = c;
        p->rule_stm = 7;
      }
    }
    break;
  default:
#ifdef MBGET_OP_NAME
    g_error ("unknown operator: %s", MBGET_OP_NAME(MBTREE_OP(tree)));
#else
    g_error ("unknown operator: 0x%04x", MBTREE_OP(tree));
#endif
  }

  MBTREE_STATE(tree) = p;
  return p;
}

static MBState *
mono_burg_label (MBTREE_TYPE *tree, MBCOST_DATA *data)
{
  MBState *p = mono_burg_label_priv (tree, data);
  return p->rule_stm ? p : NULL;
}

static int
mono_burg_rule (MBState *state, int goal)
{
  g_return_val_if_fail (state != NULL, 0);
  g_return_val_if_fail (goal > 0, 0);

  switch (goal) {
  case MB_NTERM_stm:
    return mono_burg_decode_stm [state->rule_stm];
  case MB_NTERM_exp:
    return mono_burg_decode_exp [state->rule_exp];
  case MB_NTERM_binop:
    return mono_burg_decode_binop [state->rule_binop];
  case MB_NTERM_call:
    return mono_burg_decode_call [state->rule_call];
  case MB_NTERM_temp:
    return mono_burg_decode_temp [state->rule_temp];
  case MB_NTERM_mem:
    return mono_burg_decode_mem [state->rule_mem];
  case MB_NTERM_move:
    return mono_burg_decode_move [state->rule_move];
  case MB_NTERM_cjump:
    return mono_burg_decode_cjump [state->rule_cjump];
  default: g_assert_not_reached ();
  }
  return 0;
}

static MBTREE_TYPE **
mono_burg_kids (MBTREE_TYPE *tree, int rulenr, MBTREE_TYPE *kids [])
{
  g_return_val_if_fail (tree != NULL, NULL);
  g_return_val_if_fail (kids != NULL, NULL);

  switch (rulenr) {
  case 1:
  case 5:
  case 7:
  case 12:
  case 15:
  case 16:
  case 37:
  case 38:
  case 39:
    break;
  case 2:
  case 13:
  case 27:
  case 28:
  case 32:
  case 36:
    kids[0] = MBTREE_LEFT(tree);
    break;
  case 3:
  case 26:
  case 30:
  case 34:
    kids[0] = MBTREE_LEFT(tree);
    kids[1] = MBTREE_RIGHT(tree);
    break;
  case 4:
  case 6:
  case 8:
  case 14:
  case 31:
  case 35:
    kids[0] = tree;
    break;
  case 9:
    kids[0] = MBTREE_RIGHT(MBTREE_LEFT(tree));
    break;
  case 10:
    kids[0] = MBTREE_LEFT(MBTREE_LEFT(tree));
    break;
  case 11:
    kids[0] = MBTREE_LEFT(MBTREE_LEFT(tree));
    kids[1] = MBTREE_RIGHT(MBTREE_LEFT(tree));
    break;
  case 17:
    kids[0] = MBTREE_LEFT(MBTREE_LEFT(tree));
    kids[1] = MBTREE_LEFT(MBTREE_RIGHT(tree));
    break;
  case 18:
    kids[0] = MBTREE_RIGHT(MBTREE_LEFT(MBTREE_LEFT(tree)));
    kids[1] = MBTREE_RIGHT(tree);
    break;
  case 19:
    kids[0] = MBTREE_LEFT(MBTREE_LEFT(MBTREE_LEFT(tree)));
    kids[1] = MBTREE_RIGHT(tree);
    break;
  case 20:
  case 25:
    kids[0] = MBTREE_LEFT(MBTREE_LEFT(tree));
    kids[1] = MBTREE_RIGHT(tree);
    break;
  case 21:
    kids[0] = MBTREE_LEFT(tree);
    kids[1] = MBTREE_RIGHT(MBTREE_LEFT(MBTREE_RIGHT(tree)));
    break;
  case 22:
    kids[0] = MBTREE_LEFT(tree);
    kids[1] = MBTREE_LEFT(MBTREE_LEFT(MBTREE_RIGHT(tree)));
    break;
  case 23:
  case 29:
    kids[0] = MBTREE_LEFT(tree);
    kids[1] = MBTREE_LEFT(MBTREE_RIGHT(tree));
    break;
  case 24:
  case 33:
    kids[0] = MBTREE_RIGHT(tree);
    break;
  default:
    g_assert_not_reached ();
  }
  return kids;
}

}
}
#line 31 "target/ia32/tree.brg"

#line 1 "target/ia32/epilogue.cc"
namespace target::ia32
{
  // Current codegen object running monoburg.
  GasCodegen* cg;

  GasCodegen::GasCodegen(bool rule_trace_p)
    : target::Codegen(rule_trace_p)
    , cpu_(nullptr)
    , assembly_(nullptr)
  {}

  void GasCodegen::cpu_set(const target::ia32::Cpu& cpu) { cpu_ = &cpu; }

  inline const target::ia32::Cpu* GasCodegen::cpu_get() { return cpu_; }

  void GasCodegen::assembly_set(GasAssembly& assembly)
  {
    assembly_ = &assembly;
  }

  GasAssembly& GasCodegen::assembly_get()
  {
    assertion(assembly_);
    return *assembly_;
  }

  void GasCodegen::codegen(const tree::rStm& root)
  {
    assertion(cpu_);
    tree::rTree root_ = root.cast<Tree>();

    cg = this;
    reduce(root_, MB_NTERM_stm);
  }

  void GasCodegen::reduce(rTree& tree, int goal)
  {
    static int indent_ = -2;
    rTree* kids[10];
    int ern;
    const guint16* nts;

    if (not tree->reducible_get())
      return;

    indent_ += 2;
    mono_burg_label(&tree, nullptr);

    ern = mono_burg_rule(static_cast<MBState*>(tree->state_get()), goal);
    nts = mono_burg_nts[ern];

    if (rule_trace_p_)
      emit(new assem::Comment(std::string(indent_, ' ')
                              + mono_burg_rule_string[ern]));

    mono_burg_kids(&tree, ern, kids);

    for (int i = 0; nts[i]; ++i)
      reduce(*(kids[i]), nts[i]);

    if (mono_burg_func[ern])
      mono_burg_func[ern](tree, nullptr);
    indent_ -= 2;
  }

  assem::Instrs GasCodegen::store_inframe(const frame::Access* access,
                                          const temp::Temp& word,
                                          const temp::Temp& addr) const
  {
    auto acc_frame = dynamic_cast<const frame::InFrame&>(*access);
    return assembly_->store_build(word, addr, acc_frame.offset_get());
  }

  assem::Instrs GasCodegen::load_inframe(const frame::Access* access,
                                         const temp::Temp& word,
                                         const temp::Temp& addr) const
  {
    auto acc_frame = dynamic_cast<const frame::InFrame&>(*access);
    return assembly_->load_build(addr, acc_frame.offset_get(), word);
  }

  void GasCodegen::free_callee_save(assem::ProcFrag& frag)
  {
    // callee save registers interator.
    temp::temp_set_type callee = cpu_->callee_save_regs();

    assem::Instrs save, restore;
    for (const temp::Temp& t : callee)
      {
        // This is the temp where the callee save register is saved.
        temp::Temp temp;

        // Save the callee save register.
        misc::append_and_move(save, assembly_->move_build(t, temp));

        // Restore the callee save register.
        misc::append_and_move(restore, assembly_->move_build(temp, t));
      }

    // The instructions to modify.
    assem::Instrs& ins = frag.instrs_get();

    // Instruction iterator used to insert Moves which saves callee
    // save registers at the beginning of the fragment.
    misc::prepend_and_move(ins, save);
    misc::append_and_move(ins, restore);
  }

  void GasCodegen::view_shift(assem::ProcFrag& frag)
  {
    // Access to current Frame.
    Frame& frame = frag.frame_get();

    // The instructions to modify.
    assem::Instrs& ins = frag.instrs_get();

    // Instruction iterator used to insert Moves which saves callee
    // save registers at the beginning of the fragment.
    auto instr_iter = ins.begin();

    // Formals: arguments as seen by the function.
    const frame::access_list_type& formals = frame.formals_get();
    auto formal_iter = formals.begin();

    // Move all the other arguments from the frame to
    // their dedicated location.
    for (size_t slot = cpu_->word_size_get() * 3; formal_iter != formals.end();
         ++formal_iter)
      {
        // A formal is either a InRegister (data is in a register) or
        // a InFrame (data is frame).
        auto acc_reg = dynamic_cast<const frame::InRegister*>(*formal_iter);

        if (acc_reg)
          // Formal type is InRegister.
          // Load the argument from the frame.
          instr_iter = std::next(misc::position_append_and_move(
            ins, instr_iter,
            assembly_->load_build(cpu_->fp_reg(), slot, acc_reg->temp_get())));
        else
          {
            // Formal type is InFrame.
            // Load the argument from the frame into a new temporary.
            temp::Temp temp;

            instr_iter = std::next(misc::position_append_and_move(
              ins, instr_iter,
              assembly_->load_build(cpu_->fp_reg(), slot, temp)));

            // Store the temporary to his dedicated location (in frame).
            instr_iter = std::next(misc::position_append_and_move(
              ins, instr_iter,
              store_inframe(*formal_iter, temp, cpu_->fp_reg())));
          }
        slot += cpu_->word_size_get();
      }
  }

  void GasCodegen::fragment_entry_exit_build(assem::ProcFrag& frag)
  {
    // Note that the order is reversed to what we want to obtain.

    // Save/restore callee save registers.
    free_callee_save(frag);

    // Implement the view shift.
    view_shift(frag);

    assem::Instrs& ins = frag.instrs_get();

    // The return adress is automatically stored-on/loaded-from
    // stack by `call' and `ret'.

    // Put frame allocation/deallocation markups
    auto frame_allocation_markup =
      new assem::Label("# Allocate frame", temp::Label("frame-allocation"));
    ins.emplace(ins.begin(), frame_allocation_markup);

    auto frame_deallocation_markup =
      new assem::Label("# Deallocate frame", temp::Label("frame-deallocation"));
    ins.emplace_back(frame_deallocation_markup);

    // Make fragment entry, prepending a definition of all the incoming
    // (conventionaly defined) registers.

    temp::Label entry_label("tc_" + frag.label_get().string_get());
    assem::Instrs frag_entry(assembly_->label_build(entry_label));

    frag_entry.front()->def() +=
      cpu_->argument_regs() + cpu_->callee_save_regs() + cpu_->special_regs();

    misc::prepend_and_move(ins, frag_entry);

    // Append the sink that specifies that some registers are really
    // special and are not to be used (e.g., $zero, $fp etc.).  We
    // also specify that callee save are live at the end, so that
    // the day we have dead code removal, they won't be thrown away
    // for lack of use.
    assem::Instrs frag_exit(assembly_->ret_build(
      frag.frame_get().formals_get().size() * cpu_->word_size_get()));
    frag_exit.back()->use() += cpu_->special_regs() + cpu_->callee_save_regs();

    misc::append_and_move(ins, frag_exit);
  }

  void GasCodegen::frame_build(assem::ProcFrag& frag) const
  {
    // Native IA-32 stack modifiers (push/pop, but also leave, ret
    // and call) follow a pre-decrementation post-incrementation
    // scheme, where %ebp and %esp always point to memory places
    // holding valid content. As TC internaly considers a
    // post-decremented pre-incrementated stack, the IA-32 back-end
    // must introduce instructions to synchronize these two
    // conventions. The most straightforward way to do it is to
    // modify base and stack pointers at the very beginning of the
    // routine.
    //
    // Thus, the famous prologue/epilogue section of an IA-32 routine:
    //
    //        pushl %ebp
    //        movl %esp, %ebp
    //
    //        # (%ebp) holds the value %esp had when entering
    //        # the routine, and must not be overwritten
    //
    //        movl %ebp, %esp
    //        popl %ebp
    //        ret $i
    //
    // Becomes:
    //
    //        pushl %ebp
    //        subl $4, %esp
    //        movl %esp, %ebp
    //
    //        # (%ebp) points to a "free" memory slot, as TC is expecting
    //
    //        movl %ebp, %esp
    //        addl $4, %esp
    //        popl %ebp
    //        ret $i
    //
    // As we prefer the "leave" instruction to restore the stack
    // ("leave" is faster than "movl %ebp, %esp; popl %ebp" since
    // the Pentium), we must generate the following, equivalent
    // epilogue:
    //
    //        addl $4, %ebp
    //        leave
    //        ret
    //
    // So don't be affraid to see "subl $4, %ESP" then "addl $4, %EBP"
    // it is exactly what we want.

    assem::Instrs& ins = frag.instrs_get();

    // 1. Prologue.

    auto frame_allocation_slot = ins.label_find("frame-allocation");
    assertion(frame_allocation_slot != ins.end());

    // Save the frame pointer in frame
    frame_allocation_slot = std::next(misc::position_append_and_move(
      ins, frame_allocation_slot, assembly_->push_build(cpu_->fp_reg())));

    // Counter the pre-dec/post-incrementation effect
    frame_allocation_slot = std::next(misc::position_append_and_move(
      ins, frame_allocation_slot,
      assembly_->binop_build(Binop::Oper::sub, cpu_->sp_reg(),
                             cpu_->word_size_get(), cpu_->sp_reg())));

    // Move the stack pointer to the frame pointer (i.e. FP <= SP).
    frame_allocation_slot = std::next(misc::position_append_and_move(
      ins, frame_allocation_slot,
      assembly_->move_build(cpu_->sp_reg(), cpu_->fp_reg())));

    // Allocate the frame by decrementing the stack pointer.
    frame_allocation_slot = std::next(misc::position_append_and_move(
      ins, frame_allocation_slot,
      assembly_->binop_build(Binop::Oper::sub, cpu_->sp_reg(),
                             frag.frame_get().get_current_frame_size(),
                             cpu_->sp_reg())));

    // Remove frame allocation markup
    delete *frame_allocation_slot;
    ins.erase(frame_allocation_slot);

    // 2. Epilogue.

    auto frame_deallocation_slot = ins.label_find("frame-deallocation");
    assertion(frame_deallocation_slot != ins.end());

    // Prepare frame restoration
    frame_deallocation_slot = std::next(misc::position_append_and_move(
      ins, frame_deallocation_slot,
      assembly_->binop_build(Binop::Oper::add, cpu_->fp_reg(),
                             cpu_->word_size_get(), cpu_->fp_reg())));

    // Destroy the frame
    frame_deallocation_slot = std::next(misc::position_append_and_move(
      ins, frame_deallocation_slot, assembly_->leave_build()));

    // Remove frame deallocation markup
    delete *frame_deallocation_slot;
    ins.erase(frame_deallocation_slot);
  }

  void GasCodegen::rewrite_program(assem::ProcFrag& frag,
                                   const temp::temp_set_type& spilled) const
  {
  // FIXME: Some code was deleted here (Needed in TC-9, when there are actual spills).
  }
} // namespace target::ia32
