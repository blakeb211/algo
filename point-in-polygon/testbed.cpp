#include <bits/stdc++.h>
#include <getopt.h>
#include "piplib.h"
using std::vector, std::cout, std::stoi, std::endl;
constexpr long double epsilon = 1e-6;
// function stops program execution if assert fails 
auto test1() -> void {
  P a{1.0, 2.0};
  P b{2.5, 40.3};
  P c = a + b;
  assert(fabs(c.X - 3.5) < epsilon);
  assert(fabs(c.Y - 42.3) < epsilon);
}

/*************************************************
 * To add a test,
 *  1) add the number of the test to
 *     the third argument of the getopt()
 *     function call.
 *  2) add a case statement to match the new
 *     argument
 ************************************************/

int main(int argc, char *const *argv) {
  char c = ' ';
  while ((c = getopt(argc, argv, "12")) != -1) {
    switch (c) {
      case '1': {
        cout << "running P + P test" << endl;
        // if asserts pass then test succeeded
        test1();
        break;
      }
      case '2': {
        cout << "arg 2 given" << endl;
        break;
      }
    };
  }
  return 0;
}
