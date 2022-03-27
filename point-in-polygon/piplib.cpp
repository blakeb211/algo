#include "piplib.h"

auto cross(const P a, const P b) -> C {
  return a.X * b.Y - a.Y * b.X;
}

auto is_on_left(const P p, const P seg_start, const P seg_end) -> bool {
  if (cross(p - seg_start, p - seg_end) > 0.0)
    return true;
  return false;
}

auto is_on_right(const P p, const P seg_start, const P seg_end) -> bool {
  if (cross(p - seg_start, p - seg_end) < 0.0)
    return true;
  return false;
}

auto are_intersecting(const P a, const P b, const P c, const P d) -> bool {
  















  return true;
}

auto is_inside(const P p, const Poly poly) -> bool {
  return true;
}
