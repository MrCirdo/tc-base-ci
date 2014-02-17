/**
 ** Test code for misc::generic_variant.
 */

#include <cstdlib>
#include <string>
#include <misc/generic-variant.hh>

int
main()
{
  typedef misc::generic_variant<int, std::string> variant_type;

  // Sucessful conversion.
  {
    variant_type v("Hello");
    std::string s = v;
  }

  // Failing conversion (trying to convert to the a bad dynamic type
  // among the variant's ones).
  {
    variant_type v(42);
    try
      {
        std::string s = v;
      }
    catch (boost::bad_get& e)
      {
        exit(EXIT_SUCCESS);
      }
    exit(EXIT_FAILURE);
  }

  // Failing conversion (trying to convert to the a bad dynamic type
  // out of the variant's ones).
  {
    variant_type v(42);
    try
      {
        float f = v;
      }
    catch (boost::bad_get& e)
      {
        exit(EXIT_SUCCESS);
      }
    exit(EXIT_FAILURE);
  }
}
