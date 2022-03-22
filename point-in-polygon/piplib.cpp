#include <bits/stdc++.h>
using std::complex, std::cout, std::endl, std::polar, std::arg;

using C = long double;  // coordinate
using P = complex<C>;   // point or vector
#define X real()
#define Y imag()

auto main() -> int {
  P a = {2, 3};
  P b = {1, 2};
  P c = a + b;
  cout << "c:" << c.X << " " << c.Y << endl;
  // std::polar - creates a vector of length arg1 at angle arg 2
  P d = polar(1.0, 0.5);
  // std::arg - calc angle of vector with positive X axis
  cout << "angle of d in radians: " << arg(d) << endl;
  cout << d << endl;
  return 0;
}
