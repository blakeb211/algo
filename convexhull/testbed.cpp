#include <bits/stdc++.h>
#include <unistd.h>

#include "convexlib.h"

using std::vector, std::cout, std::stoi, std::endl;

bool test_rnd() {
  int ans = rand_num(1, 5);
  if (ans >= 1 && ans <= 5) return true;
  return false;
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
        cout << "running test_rnd()" << endl;
        return test_rnd();
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
