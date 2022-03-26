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
using C = long double;                    // coordinate
using P = std::complex<C>;                // point or vector
#define X real()
#define Y imag()

// 2d vector cross product
//  > 0 means 2nd vec turns left if placed at head of first vec
//  < 0   "                 right           "
// == 0 means vec1 and vec2 are are at same angle 
auto cross(const P a, const P b) -> C;


