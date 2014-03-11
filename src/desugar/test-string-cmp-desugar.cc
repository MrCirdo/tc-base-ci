/**
 ** Checking string comparisons desugaring.
 */

#include <ostream>
#include <string>

#include <ast/all.hh>
#include <ast/libast.hh>
#include <type/types.hh>
#include <desugar/desugar-visitor.hh>
#include <parse/libparse.hh>
#include <type/type-checker.hh>
#include <misc/file-library.hh>

using namespace ast;
using namespace desugar;

const char* program_name = "test-string-cmp-desugar";

static
void
test_string_desugaring(const std::string& oper)
{
  Exp* tree = parse::parse
    ("let primitive streq(s1 : string, s2 : string) : int\n"
     "   primitive strcmp(s1 : string, s2 : string) : int\n"
     "in\n"
     "  (\"foo\" " + oper + " \"bar\")\n"
     "end\n");
  type::TypeChecker type;
  type(tree);

  std::cout << "/* === Original tree...  */" << std::endl
            << *tree << std::endl;

  DesugarVisitor desugar(false, true);
  tree->accept(desugar);
  delete tree;
  tree = nullptr;
  std::cout << "/* === Desugared tree...  */" << std::endl
            << *desugar.result_get() << std::endl;
  delete desugar.result_get();
}

int
main()
{
  // Desugaring `"foo" = "bar"' as `streq ("foo", "bar")'.
  std::cout << "First test..." << std::endl;
  test_string_desugaring("=");
  std::cout << std::endl;

  // Desugaring `"foo" <> "bar"' as `streq ("foo", "bar") <> 0'.
  std::cout << "Second test..." << std::endl;
  test_string_desugaring("<>");
  std::cout << std::endl;

  // Desugaring `"foo" >= "bar"' as `strcmp ("foo", "bar") >= 0'.
  std::cout << "Third test..." << std::endl;
  test_string_desugaring(">=");
}
