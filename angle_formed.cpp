#include <bits/stdc++.h>

using namespace std;

struct pt {
  int x, y;
  friend ostream& operator<<(ostream& os, const pt& p) {
    os << "x: " << p.x << "\ty:" << p.y;
    return os;
  }
  // comparator
};

// sorting predicate for pt

int main() {
  pt a{0,0};
  pt b{0,2};
  pt c{1, 3};

  auto angle_formed = [](pt a, pt b, pt c) {
    pt ab = pt{b.x-a.x, b.y-a.y}; 
    pt bc = pt{c.x-b.x, c.y-b.y}; 
    int dotprod = ab.x * bc.x + ab.y * bc.y;
    float lenAB = sqrt(ab.x*ab.x + ab.y*ab.y);
    float lenBC = sqrt(bc.x*bc.x + bc.y*bc.y);
    auto ans_radians = acos( (float)dotprod / lenAB / lenBC);
    return ans_radians * 180.0 / M_PI;
  };

  cout << angle_formed(a,b,c) << " " << endl;


  return 0;
}
