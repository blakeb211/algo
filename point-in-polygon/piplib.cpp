#include "piplib.h"

auto cross(const P a, const P b) -> C {
  return a.X * b.Y - a.Y * b.X;
}

auto is_on_left(const P p, const P seg_start, const P seg_end) -> bool {
  return true;
}

auto is_on_right(const P p, const P seg_start, const P seg_end) -> bool {
  return true;
}

auto are_intersecting(const P a, const P b, const P c, const P d) -> bool {
  return true;
}

auto is_inside(const P p, const Poly poly) -> bool {
  return true;
}
