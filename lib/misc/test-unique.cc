/**
 ** Testing the Flyweight pattern.
 */

#include <iostream>
#include <string>

#include <misc/contract.hh>
#include <misc/unique.hh>
void test_with_int()
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

void test_with_string()
{
  using unique_str = misc::unique<std::string>;
  unique_str the_answer = std::string{"coucou"};
  unique_str the_same_answer =  std::string{"coucou"};
  unique_str the_solution = std::string{"coucou mais un peu différent"};

  // Checking misc::unique<int>.
  assertion(the_answer == unique_str(std::string{"coucou"}));
  assertion(the_answer == the_same_answer);
  assertion(the_answer != the_solution);

  std::cout << the_answer << '\n';
}

int main()
{
  test_with_string();
  test_with_int();
}
