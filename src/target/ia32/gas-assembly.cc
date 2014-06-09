/**
 ** \file target/ia32/gas-assembly.cc
 ** \brief Implementation of target::ia32::GasAssembly.
 */

#include <boost/lexical_cast.hpp>

#include <misc/contract.hh>
#include <temp/label.hh>
#include <assem/libassem.hh>
#include <target/ia32/gas-layout.hh>
#include <target/ia32/gas-assembly.hh>

namespace target
{
  namespace ia32
  {
    typedef temp::temp_list_type Ts;
    typedef temp::label_list_type Ls;

    GasAssembly::GasAssembly()
      : Assembly(GasLayout::instance())
    {
    }

    GasAssembly::~GasAssembly()
    {
    }

    /*------------------------.
    | Arithmetic operations.  |
    `------------------------*/

    std::string
    GasAssembly::binop_inst(const tree::Binop::Oper& op) const
    {
      switch (op)
        {
        case tree::Binop::add:  return "addl\t";
        case tree::Binop::sub:  return "subl\t";
        case tree::Binop::mul:  return "imull\t";
          // Let tree::Binop::div fail, since it needs a dedicated
          // construction.
        default:
          die("Should not be there.");
        };
    }

    assem::Instrs
    GasAssembly::binop_build(const tree::Binop::Oper& op,
                             const temp::Temp& left,
                             const temp::Temp& right,
                             const temp::Temp& dst) const
    {
      if (op == tree::Binop::div)
        {
          return {
            new assem::Move("movl\t%'s, %'d",
                            left, temp::Temp("eax")),
            /* Emit instruction

                 cltd

               which is equivalent to

                 movl    %eax, %edx
                 sarl    $31, %edx

               See http://www.cs.mun.ca/~rod/winter2004/cs3724/notes/asm.html
               for more information.  */
            new assem::Oper("cltd",
                            Ts(temp::Temp("eax")),
                            Ts(temp::Temp("edx"))),
            new assem::Oper("idivl\t%'s",
                            Ts(right), Ts(temp::Temp("eax"),
                                          temp::Temp("edx"))),
            new assem::Move("movl\t%'s, %'d",
                            temp::Temp("eax"), dst)
          };
        }
      else
        {
          assem::Instrs res;
          // x86 use two-address instructions
          // { add $left with $right into $dst } is equivalent to:
          // { move $left into $dst; add $right with and into $dst }
          if (&dst != &left)
            res.push_back(new assem::Move("movl\t%'s, %'d", left, dst));

          std::string opcode = binop_inst(op) + "%'s, %'d";
          res.push_back(new assem::Oper(opcode,
                                        Ts(right, dst), Ts(dst)));
          return res;
        }
    }

    assem::Instrs
    GasAssembly::binop_build(const tree::Binop::Oper& op,
                             const temp::Temp& left,
                             int right,
                             const temp::Temp& dst) const
    {
      assem::Instrs res;

      if (op == tree::Binop::div)
        {
          res.splice(res.end(), move_build(right, temp::Temp("ebx")));

          res.push_back(new assem::Move("movl\t%'s, %'d",
                                        left, temp::Temp("eax")));
          // See comment above about `cltd'.
          res.push_back(new assem::Oper("cltd",
                                        Ts(temp::Temp("eax")),
                                        Ts(temp::Temp("edx"))));
          res.push_back(new assem::Oper("idivl\t%'s",
                                        Ts(temp::Temp("ebx")),
                                        Ts(temp::Temp("eax"),
                                           temp::Temp("edx"))));
          res.push_back(new assem::Move("movl\t%'s, %'d",
                                        temp::Temp("eax"), dst));
        }
      else
        {
          // x86 use two-address instructions
          if (&dst != &left)
            res.push_back(new assem::Move("movl\t%'s, %'d", left, dst));

          std::string opcode = binop_inst(op) + "$" +
            boost::lexical_cast<std::string>(right) + ", %'d";
          res.push_back(new assem::Oper(opcode,
                                        Ts(dst), Ts(dst)));
        }
      return res;
    }

    /*------------------.
    | Move operations.  |
    `------------------*/

    assem::Instrs
    GasAssembly::move_build(const temp::Temp& src,
                            const temp::Temp& dst) const
    {
      return { new assem::Move("movl\t%'s, %'d", src, dst) };
    }

    assem::Instrs
    GasAssembly::move_build(int immediate, const temp::Temp& dst) const
    {
      std::string opcode = "movl\t$" +
        boost::lexical_cast<std::string>(immediate) + ", %'d";
      return { new assem::Oper(opcode,
                               Ts(), Ts(dst)) };
    }

    assem::Instrs
    GasAssembly::move_build(const temp::Label& label,
                            const temp::Temp& dst) const
    {
      return { new assem::Oper("lea\t" + label.string_get() + ", %'d",
                               Ts(), Ts(dst)) };
    }

    /*------------------.
    | Load operations.  |
    `------------------*/

    assem::Instrs
    GasAssembly::load_build(const temp::Temp& base,
                            int offset,
                            const temp::Temp& dst) const
    {
      std::string opcode =
        offset
        ? "movl\t" + boost::lexical_cast<std::string>(offset) + "(%'s), %'d"
        : "movl\t(%'s), %'d";
      return { new assem::Oper(opcode, Ts(base), Ts(dst)) };
    }

    assem::Instrs
    GasAssembly::load_build(const temp::Temp& base,
                            const temp::Temp& dst) const
    {
      return load_build(base, 0, dst);
    }

    assem::Instrs
    GasAssembly::load_build(int,
                            const temp::Temp&) const
    {
      die("FIXME: Don't know what it is.");
      return assem::Instrs();
    }


    /*-------------------.
    | Store operations.  |
    `-------------------*/

    assem::Instrs
    GasAssembly::store_build(const temp::Temp& src,
                             const temp::Temp& base,
                             int offset) const
    {
      std::string opcode =
        offset
        ? "movl\t%'s, " + boost::lexical_cast<std::string>(offset) + " (%'s)"
        : "movl\t%'s, (%'s)";
      return { new assem::Oper(opcode, Ts(src, base), Ts()) };
    }

    assem::Instrs
    GasAssembly::store_build(const temp::Temp&,
                             int) const
    {
      die("FIXME: Don't know what it is.");
      return assem::Instrs();
    }

    /*--------.
    | Label.  |
    `--------*/

    assem::Instrs
    GasAssembly::label_build(const temp::Label& label) const
    {
      return { new assem::Label(label.string_get() + ":", label) };
    }

    /*-------------------.
    | Conditional jump.  |
    `-------------------*/

    std::string
    GasAssembly::cjump_inst(const tree::Cjump::Relop& op) const
    {
      switch (op)
        {
        case tree::Cjump::eq:   return "je\t'j";
        case tree::Cjump::ne:   return "jne\t'j";

        case tree::Cjump::lt:   return "jl\t'j";
        case tree::Cjump::gt:   return "jg\t'j";

        case tree::Cjump::le:   return "jle\t'j";
        case tree::Cjump::ge:   return "jge\t'j";

        case tree::Cjump::ult:  return "jb\t'j";
        case tree::Cjump::ugt:  return "ja\t'j";

        case tree::Cjump::ule:  return "jbe\t'j";
        case tree::Cjump::uge:  return "jae\t'j";
        default:
          die("Should not be here.");
        };
    }

    // if(left cc right) then jump to label_true
    //
    // cmpl right, left
    // jcc  label_true

    assem::Instrs
    GasAssembly::cjump_build(const tree::Cjump::Relop& op,
                             const temp::Temp& left,
                             const temp::Temp& right,
                             const temp::Label& label_true,
                             const temp::Label& label_false) const
    {
  // FIXME: Some code was deleted here.
    }

    assem::Instrs
    GasAssembly::cjump_build(const tree::Cjump::Relop& op,
                             const temp::Temp& left,
                             int right,
                             const temp::Label& label_true,
                             const temp::Label& label_false) const
    {
  // FIXME: Some code was deleted here.
    }

    assem::Instrs
    GasAssembly::cjump_build(const tree::Cjump::Relop& op,
                             int left,
                             const temp::Temp& right,
                             const temp::Label& label_true,
                             const temp::Label& label_false) const
    {
      return cjump_build(tree::symmetrize(op), right, left,
                          label_true, label_false);
    }


    /*---------------------.
    | Unconditional jump.  |
    `---------------------*/

    assem::Instrs
    GasAssembly::jump_build(const temp::Label& label) const
    {
      return { new assem::Oper("jmp\t'j", Ts(), Ts(), Ls(label)) };
    }


    /*-----------.
    | Function.  |
    `-----------*/

    assem::Instrs
    GasAssembly::push_build(const temp::Temp& src)
    {
      return { new assem::Oper("pushl\t%'s", src, Ts()) };
    }

    assem::Instrs
    GasAssembly::call_build(const temp::Label& label,
                            const temp::temp_list_type& dst) const
    {
      return { new assem::Oper("call\t" "tc_" + label.string_get(),
                               Ts(), dst) };
    }

    assem::Instrs
    GasAssembly::leave_build() const
    {
      return { new assem::Oper("leave", Ts(), Ts()) };
    }

    assem::Instrs
    GasAssembly::ret_build(size_t i) const
    {
      std::string opcode = "ret\t$" + boost::lexical_cast<std::string>(i);

      return { new assem::Oper(opcode, Ts(), Ts()) };
    }


  } // namespace ia32

} // namespace target
