#pragma once
#include <bits/stdc++.h>

/**********************************************************
 *                    Types
 *********************************************************/
// Point struct (P) and coordinate (C)
// Access point coordinate                P.X and P.Y
// Add two points                         p1 + p2
// Print a point to stdout                cout << p1 << endl
// Vector w/ len l and ang a              std::polar(l,a)
// Angle of vec with +x axis              std::arg(vec1)
using C = long double;      // coordinate
using P = std::complex<C>;  // point or vector
#define X real()
#define Y imag()
using Poly = std::vector<P>;
// 2d vector cross product
//  > 0 means 2nd vec turns left if placed at head of first vec
//  < 0   "                 right           "
// == 0 means vec1 and vec2 are are at same angle
auto cross(const P a, const P b) -> C;

// determine if a point is on the left of a line in 2d
auto is_on_left(const P p, const P seg_start, const P seg_end) -> bool;

// determine if a point is on the right of a line in 2d
auto is_on_right(const P p, const P seg_start, const P seg_end) -> bool;

// determine if two segments (given as their head and tail points)
// are intersecting
auto are_intersecting(const P a, const P b, const P c, const P d) -> bool;

// determine if a test point is inside of a polygon given as a vector
// of points.
auto is_inside(const P p, const Poly poly) -> bool;

