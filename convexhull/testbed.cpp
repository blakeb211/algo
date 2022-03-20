#include <bits/stdc++.h>
#include <unistd.h>

#include "convexlib.h"

using std::vector, std::cout, std::stoi, std::endl;

int test_rnd(int lower, int upper) { return 42; }

int main(int argc, char *const *argv) {
  char * optarg = nullptr;
  char c = ' ';
  while ((c = getopt(argc, argv, "12")) != -1) {
    switch (c) {
      case '1': {
        cout << "arg 1 given" << endl;
        cout << "optarg:" << optarg << endl;
        break;
      }
      case '2': {
        cout << "arg 2 given" << endl;
        cout << "optarg:" << optarg << endl;
        break;
      }
    };
  }
  return 0;
}
