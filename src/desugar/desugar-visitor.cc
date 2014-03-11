/**
 ** \file desugar/desugar-visitor.cc
 ** \brief Implementation of desugar::DesugarVisitor.
 */

#include <misc/algorithm.hh>
#include <ast/all.hh>
#include <ast/libast.hh>
#include <parse/libparse.hh>
#include <parse/tweast.hh>
#include <desugar/desugar-visitor.hh>
#include <misc/symbol.hh>

namespace desugar
{

  DesugarVisitor::DesugarVisitor(bool desugar_for_p,
                                 bool desugar_string_cmp_p)
    : super_type()
    , desugar_for_p_(desugar_for_p)
    , desugar_string_cmp_p_(desugar_string_cmp_p)
  {
  }

  DesugarVisitor::~DesugarVisitor()
  {
  }


  /*-----------------------------.
  | Desugar string comparisons.  |
  `-----------------------------*/
  // FIXME: Some code was deleted here.

  /*----------------------.
  | Desugar `for' loops.  |
  `----------------------*/

  // FIXME: Some code was deleted here.

} // namespace desugar
