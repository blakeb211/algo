#include "piplib.h"

auto cross(const P a, const P b) -> C { return a.X * b.Y - a.Y * b.X; }

auto is_on_left(const P p, const P seg_start, const P seg_end) -> bool {
  if (cross(p - seg_start, p - seg_end) > 0.0) return true;
  return false;
}

auto is_on_right(const P p, const P seg_start, const P seg_end) -> bool {
  if (cross(p - seg_start, p - seg_end) < 0.0) return true;
  return false;
}

auto are_intersecting(const P a, const P b, const P c, const P d) -> bool {
  bool case3 = false;
  // Only need to code case 3, intersection at exactly one non-vertex point.
  // Case 3: a--b and c--d intersect at exactly one
  // non-vertex point
  // a and b are on diff sides of line c--d. also points c and d are on
  // diff sides of a line through a--b.
  bool check1 = (is_on_left(a, c, d) && is_on_right(b, c, d)) ||
                (is_on_left(b, c, d) && is_on_right(a, c, d));
  bool check2 = (is_on_left(c, a, b) && is_on_right(d, a, b)) ||
                (is_on_left(d, a, b) && is_on_right(c, a, b));
  if (check1 && check2) {
    case3 = true;
  }
  if (case3) {
    return true;
  }
  return false;
}

auto is_inside(const P pt, const Poly poly) -> bool {
  //  Pick arbitrary direction.
  //  Cast a ray by building a segment from the point in arbitrary direction
  //  with a very long length.
  //  Loop through polygon segments and add 1 to a counter for each segment
  //  that the ray intersects.
  //  If the counter is 0, 2, 4, etc then the point is outside the polygon.
  //  if the counter is 1, 3, 5, etc then the point is inside the polygon.
  P ray_st = pt;
  P ray_end = pt + P{40, 0};  // pick 0 degree direction
  //   1 2 3 4 5 6 7 8 9 10
  //  - - - - - - - - -
  size_t count = 0;
  const auto sz = poly.size();
  // check sz-1 segments a---b---c
  for (size_t i = 0; i < sz - 1; i++) {
    if (are_intersecting(ray_st, ray_end, poly[i], poly[i + 1])) {
      count = count + 1;
    }
  }
  // check last line c----a (last point of poly to first point of poly)
  if (are_intersecting(ray_st, ray_end, poly[sz - 1], poly[0]))

    if (count % 2 == 0) {
      return false;
    }
  return true;
}
