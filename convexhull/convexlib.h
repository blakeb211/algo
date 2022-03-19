#pragma once
#include <vector>
#include <iostream>
//////////////////////////////////////////////////////////////
// globals
//////////////////////////////////////////////////////////////
inline constexpr size_t NUM_PT = 11;
inline constexpr int SCALE = 4;
inline constexpr int WINDIM = 600;
//////////////////////////////////////////////////////////////
// types
//////////////////////////////////////////////////////////////
struct pt {
  float x, y;
  friend std::ostream& operator<<(std::ostream& os, const pt& p) {
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

//////////////////////////////////////////////////////////////
// free functions
//////////////////////////////////////////////////////////////

int rand_num(const int lower, const int upper);

pt create_rand_pt(int first, int last);

// function to determine if points a--b--c create a left hand turn
bool is_left_turn(pt a, pt b, pt c);

std::vector<pt> solve_convex_hull(std::vector<pt> pts);
