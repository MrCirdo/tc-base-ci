/**
 ** Testing the symbols and the symbol tables.
 */

#include <ostream>

#include <misc/contract.hh>
#include <misc/symbol.hh>

using misc::symbol;

int main()
{
  const symbol toto1("toto");
  assertion(symbol::object_map_size() == 1);
  const symbol toto2("toto");
  assertion(symbol::object_map_size() == 1);
  const symbol titi1("titi");
  assertion(symbol::object_map_size() == 2);

  // Checking symbol.
  assertion(toto1.get() == "toto");
  assertion(&(toto1.get()) == &(toto2.get()));

  assertion(toto1 == "toto");
  assertion(toto1 != "titi");

  assertion(toto1 == toto2);
  assertion(toto1 != titi1);
  assertion(symbol::object_map_size() == 2);

  std::string junk = "tata";
  const symbol tata1(junk);
  assertion(symbol::object_map_size() == 3);
  junk = "toto";
  assertion(symbol::object_map_size() == 3);
  assertion(tata1 == "tata");
  const symbol empty;
  assertion(symbol::object_map_size() == 4);
  const symbol empty1 = "";
  assertion(symbol::object_map_size() == 4);
}
