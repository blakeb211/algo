#include "convexlib.h"
#include <bits/stdc++.h> 
using std::vector, std::cout;
//////////////////////////////////////////////////////////////
// free functions
//////////////////////////////////////////////////////////////

int rand_num(const int lower, const int upper) {
  return ( rand() % (upper - lower + 1)) + lower; 
}

pt create_rand_pt(int first, int last) {
  auto num1 = rand_num(first,last);
  auto num2 = rand_num(first,last);
  return pt{ static_cast<float>(num1), static_cast<float>(num2) };
}

// Calculate the angle formed by 3 points.
// e.g. for a---b---c, it is the angle <(ba,bc)
float angle_formed(pt a, pt b, pt c) {
  pt ba = pt{a.x-b.x, a.y-b.y}; 
  pt bc = pt{c.x-b.x, c.y-b.y}; 
  float dotprod = ba.x * bc.x + ba.y * bc.y;
  float lenAB = sqrt(ba.x*ba.x + ba.y*ba.y);
  float lenBC = sqrt(bc.x*bc.x + bc.y*bc.y);
  auto ans_radians = acos( (float)dotprod / lenAB / lenBC);
  return ans_radians * 180.0 / M_PI;
}

void remove_duplicates(vector<pt>& pt) {}

// function to determine if points a--b--c create a left hand turn
bool is_left_turn(pt a, pt b, pt c) {

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

  pt ab = b - a;
  // The 90 degrees clockwise rotation matrix is 
  //  0   1
  // -1   0
  //  Obtain d by rotating ab 90 degrees clockwise and adding
  //  it to point b.
  pt d = pt{ab.y, -ab.x} + b;
  // If the angle formed by dbc is <= 90, its a right hand turn or
  // abc is a straight line. 
  // Convex hulls are made from all right hand turns.
  // If the angle formed is > 90, it is a left turn.
  return angle_formed(d,b,c) > 90.f;
} 

vector<pt> solve_convex_hull(vector<pt> pts, const bool UPPER) {
  vector<pt> soln;
  soln.resize(pts.size()); // one allocation
  soln.resize(0);
  // step 1, sort by x then y
  // add first 3 points
  // Loop:
  // if left_turn == 1, remove 2nd to last point
  // add a point
  // go until no more pts
  if (UPPER) {
    sort(pts.begin(), pts.end(), less_than());
  } else {
    sort(pts.begin(), pts.end(), greater_than());
  }
  //  print out sorted pts array
  cout << "SORTED POINTS:\n";
  auto sz = pts.size();
  for (int i = 0; i < sz; i++)
    cout << pts[i] << "\n";
  size_t nextpt = 0;
  // add first two points to soln
  soln.push_back(pts[0]);
  soln.push_back(pts[1]);
  nextpt = 2;
  while(nextpt <= pts.size()) {
    if (nextpt < pts.size()) soln.push_back(pts[nextpt]);
    auto sz = soln.size();
    while (sz >= 3 && is_left_turn(soln[sz-3],soln[sz-2],soln[sz-1]))
    {
      soln.erase(soln.end()-2);
      sz = soln.size();
    }
    nextpt++;
  }

  return soln;
}
