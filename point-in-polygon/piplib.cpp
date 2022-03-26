#include "piplib.h"

auto cross(const P a, const P b) -> C {
  return a.X * b.Y - a.Y * b.X;
}
