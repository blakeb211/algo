#include <bits/stdc++.h>
#include <getopt.h>

#include "convexlib.h"

using std::vector, std::cout, std::stoi, std::endl;

// function stops program execution if assert fails 
void test_rnd() {
  srand(time(NULL));
  const int LOWER = 1;
  const int UPPER = 10;
  bool lower_end_hit = false;
  bool upper_end_hit = false;
  for (int i = 0; i < 10'000; i++) {
    int ans = rand_num(LOWER, UPPER);
    if (ans == LOWER) lower_end_hit = true;
    if (ans == UPPER) upper_end_hit = true;
    assert(ans >= LOWER && ans <= UPPER);
  }
  assert(lower_end_hit && upper_end_hit);
  assert(0);
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
        // if testrnd's asserts pass then the test
        // was successful
        test_rnd();
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
