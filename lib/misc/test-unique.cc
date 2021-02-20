/**
 ** Testing the Flyweight pattern.
 */

#include <iostream>
#include <string>

#include <misc/contract.hh>
#include <misc/unique.hh>
static void test_with_int()
{
  using unique_int = misc::unique<int>;
  unique_int the_answer = 42;
  unique_int the_same_answer = 42;
  unique_int the_solution = 51;

  // Checking misc::unique<int>.
  assertion(the_answer == unique_int(42));
  assertion(the_answer == the_same_answer);
  assertion(the_answer != the_solution);

  std::cout << the_answer << '\n';
}

static void test_with_string()
{
  using unique_str = misc::unique<std::string>;
  unique_str the_answer = std::string{"coucou"};
  unique_str the_same_answer = std::string{"coucou"};
  unique_str the_solution = std::string{"coucou mais un peu différent"};
  std::string the_same_answer2 = the_same_answer;

  // Checking misc::unique<std::string>.
  assertion(the_answer == unique_str(std::string{"coucou"}));
  assertion(the_answer == the_same_answer);
  assertion(the_answer != the_solution);

  assertion(the_same_answer.get() == the_same_answer2);
  assertion(&the_same_answer.get() != &the_same_answer2);

  std::cout << the_answer << '\n';
}

int main()
{
  test_with_string();
  test_with_int();
}
