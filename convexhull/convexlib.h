#pragma once
#include <vector>
#include <iostream>

//////////////////////////////////////////////////////////////
// types
//////////////////////////////////////////////////////////////
struct pt {
  float x, y; friend std::ostream& operator<<(std::ostream& os, const pt& p) {
    os << "x: " << p.x << "\ty:" << p.y;
    return os;
  }
  pt operator+(const pt& p) {
    return pt{p.x + x, p.y + y};
  }
  pt operator-(const pt& p) {
    return pt{x - p.x, y - p.y};
  }
};

// sorting predicate for pt
struct less_than
{
  inline bool operator() (const pt& p1, const pt& p2)
  {
    if (p1.x < p2.x) return true;
    if (p2.x < p1.x) return false;
    // p1=p2 for x, go to y
    if (p1.y < p2.y) return true;
    if (p2.y < p1.y) return false;
    return false;
  }
};

// sorting predicate for pt
struct greater_than
{
  inline bool operator() (const pt& p1, const pt& p2)
  {
    if (p1.x > p2.x) return true;
    if (p2.x > p1.x) return false;
    // p1=p2 for x, go to y
    if (p1.y > p2.y) return true;
    if (p2.y > p1.y) return false;
    return false;
  }
};

//////////////////////////////////////////////////////////////
// free functions
//////////////////////////////////////////////////////////////

void remove_duplicates(std::vector<pt>& pt);

int rand_num(const int lower, const int upper);

pt create_rand_pt(int first, int last);

// Determine if points a--b--c create a left hand turn
bool is_left_turn(pt a, pt b, pt c);

// Calculate the angle formed by 3 points.
float angle_formed(pt a, pt b, pt c);

// Solve for the list of points, in order, in the input that
// form the convex hull which enclosed all the remaining points.
std::vector<pt> solve_convex_hull(std::vector<pt> pts, const bool UPPER);
