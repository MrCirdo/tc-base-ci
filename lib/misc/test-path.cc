/**
 ** Test code for misc::Path
 */

#include <iostream>
#include <misc/path.hh>
#include <misc/contract.hh>

int main()
{
  misc::path p1 = "/usr//local";
  misc::path p2 = "bin";
  misc::path empty = "";

  assertion(empty.empty());
  assertion(!p1.empty());
  assertion(!p2.empty());

#define CHECK(Out)                                      \
  do {                                                  \
    assertion(!p1.empty());                             \
    assertion(static_cast<std::string>(p1) == Out);     \
  } while (false)

  CHECK("/usr/local");
  p1 += p2;
  CHECK("/usr/local/bin");
  p1 += "..";
  CHECK("/usr/local");
  p1 = p2;
  CHECK("bin");
  p1 = "../../";
  CHECK("../..");
}
