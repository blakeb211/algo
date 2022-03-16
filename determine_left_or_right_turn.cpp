#include <bits/stdc++.h>

using namespace std;

struct pt {
  float x, y;
  friend ostream& operator<<(ostream& os, const pt& p) {
    os << "x: " << p.x << "\ty:" << p.y;
    return os;
  }
  // comparator
};

  auto angle_formed = [](pt a, pt b, pt c) {
    pt ba = pt{a.x-b.x, a.y-b.y}; 
    pt bc = pt{c.x-b.x, c.y-b.y}; 
    float dotprod = ba.x * bc.x + ba.y * bc.y;
    float lenAB = sqrt(ba.x*ba.x + ba.y*ba.y);
    float lenBC = sqrt(bc.x*bc.x + bc.y*bc.y);
    auto ans_radians = acos( (float)dotprod / lenAB / lenBC);
    return ans_radians * 180.0 / M_PI;
  };

// function to determine if points a--b--c create a left hand turn
bool is_left_turn(pt a, pt b, pt c) {
  // Calculate the angle formed by 3 points.
  // e.g. for a---b---c, it is the angle <(ba,bc)

  /* For the convex hull Andrews algorithm, need to be able to check
   * if the last 3 points are a left turn or a right turn. If a left
   * turn, throw out the 2nd to last point and start again.
   *
   * create a perpendicular line to the right of the ab.
   * transform ab with the rotation matrix.
   * add b to the transformed coordinates to get d, the point
   * out 90 degrees clockwise to a-b.
   * calculate angle <dbc. If that is less than or equal
   * to 90, it is a righthand turn.*/

  pt ab{b.x - a.x, b.y - a.y};
  // The 90 degrees clockwise rotation matrix is 
  //  0   1
  // -1   0
  //  Obtain d by rotating ab 90 degrees clockwise and adding
  //  it to point b.
  pt d{ab.y + b.x, -ab.x + b.y};
  // If the angle formed by dbc is <= 90, its a right hand turn or
  // abc is a straight line. 
  // Convex hulls are made from all right hand turns.
  // If the angle formed is > 90, it is a left turn.
  return angle_formed(d,b,c) > 90.f;
} 





int main() {
  pt a{1,2};
  pt b{2,3.5};
  pt c{1.5, 4.5};

  cout << angle_formed(a,b,c) << endl;
  cout << is_left_turn(a,b,c) << endl;


  return 0;
}
