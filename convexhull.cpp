#include "SDL.h"
#include <bits/stdc++.h>

/*******************************************************
 * TODO:
 * Read through andrews algorithm in book and online
 * Sketch out solution
 * Finish coding
 ******************************************************/






using std::ostream, std::cout, std::ios, std::cin,std::vector;
using std::sort;
//////////////////////////////////////////////////////////////
// globals
//////////////////////////////////////////////////////////////
constexpr size_t NUM_PT = 11;
constexpr int SCALE = 4;
constexpr int WINDIM = 600;

//////////////////////////////////////////////////////////////
// types
//////////////////////////////////////////////////////////////
struct pt {
  float x, y;
  friend ostream& operator<<(ostream& os, const pt& p) {
    os << "x: " << p.x << "\ty:" << p.y;
    return os;
  }
  // comparator
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

int rand_num(const int lower, const int upper) {
  return ( rand() % (upper - lower + 1)) + lower; 
}

pt create_rand_pt(int first, int last) {
  auto num1 = rand_num(first,last);
  auto num2 = rand_num(first,last);
  return pt{ static_cast<float>(num1), static_cast<float>(num2) };
}

// function to determine if points a--b--c create a left hand turn
bool is_left_turn(pt a, pt b, pt c) {
  // Calculate the angle formed by 3 points.
  // e.g. for a---b---c, it is the angle <(ba,bc)
  auto angle_formed = [](pt a, pt b, pt c) {
    pt ba = pt{a.x-b.x, a.y-b.y}; 
    pt bc = pt{c.x-b.x, c.y-b.y}; 
    float dotprod = ba.x * bc.x + ba.y * bc.y;
    float lenAB = sqrt(ba.x*ba.x + ba.y*ba.y);
    float lenBC = sqrt(bc.x*bc.x + bc.y*bc.y);
    auto ans_radians = acos( (float)dotprod / lenAB / lenBC);
    return ans_radians * 180.0 / M_PI;
  };

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



vector<pt> solve_convex_hull(vector<pt> pts) {
  vector<pt> soln(NUM_PT);
  assert(soln.size() == NUM_PT);
  soln.resize(0);
  // step 1, sort by x then y
  // add first 3 points
  // Loop:
  // if left_turn == 1, remove 2nd to last point
  // add a point
  // go until no more pts
  sort(pts.begin(), pts.end(), less_than());
  //  print out sorted pts array
  cout << "SORTED POINTS:\n";
  for (int i = 0; i < NUM_PT; i++)
    cout << pts[i] << "\n";
  size_t nextpt = 0;
  // add first three points to soln
  soln.push_back(pts[0]);
  soln.push_back(pts[1]);
  nextpt = 2;
  while(nextpt != pts.size()+1) {
    soln.push_back(pts[nextpt]);
    auto sz = soln.size();
    if (is_left_turn(soln[sz-3],soln[sz-2],soln[sz-1]))
      soln.erase(soln.end()-2);
    nextpt++;
  }
  // do one final check in case the last point added was bad
  auto sz = soln.size();
  if (is_left_turn(soln[sz-3],soln[sz-2],soln[sz-1]))
    soln.erase(soln.end()-2);

  //  print out soln array
  cout << "SOLUTION POINTS (" << soln.size() << "%ld):\n";
  for (int i = 0; i < soln.size(); i++)
    cout << soln[i] << "\n";

  return soln;

}

//////////////////////////////////////////////////////////////
// main function
//////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  // random points 
  srand(time(NULL));
  vector<pt> pts(NUM_PT);

  for (int i = 0; i < NUM_PT; i++) {
    pts[i] = create_rand_pt(80/SCALE,(WINDIM-80)/SCALE);
  }

  vector<pt> soln = solve_convex_hull(pts);



  // create window and draw solution

  if (SDL_Init(SDL_INIT_VIDEO) == 0) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_CreateWindowAndRenderer(WINDIM, WINDIM, 0, &window, &renderer) == 0) {
      SDL_bool done = SDL_FALSE;

      SDL_RenderSetScale(renderer, SCALE, SCALE);

      while (!done) {
        SDL_Event event;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // draw the solution
        SDL_SetRenderDrawColor(renderer, 100, 5, 200, SDL_ALPHA_OPAQUE);
        auto num_lines = soln.size() - 1;
        // a---b---c----d
        for (int i = 0; i < num_lines -1; i++) {
          SDL_RenderDrawLine(renderer, soln[i].x, WINDIM/SCALE-soln[i].y, \
              soln[i+1].x, WINDIM/SCALE-soln[i+1].y);
        }
       
        // draw the points
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        for (int i = 0; i < NUM_PT; i++) 
          SDL_RenderDrawPoint(renderer, pts[i].x, WINDIM/SCALE-pts[i].y);

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
          if (event.type == SDL_QUIT) {
            done = SDL_TRUE;
          }
        }
      }
    }

    if (renderer) {
      SDL_DestroyRenderer(renderer);
    }
    if (window) {
      SDL_DestroyWindow(window);
    }
  }
  SDL_Quit();
  return 0;
}
