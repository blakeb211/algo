#include <bits/stdc++.h>
#include <getopt.h>

using std::vector, std::cout, std::stoi, std::endl;

// function stops program execution if assert fails 
void test_1() {
  assert(1);
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
        cout << "running test_1()" << endl;
        // if asserts pass then test succeeded
        test_1();
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
