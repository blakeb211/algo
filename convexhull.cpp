#include "SDL.h"
#include <bits/stdc++.h>

using std::ostream, std::cout, std::ios, std::cin,std::vector;
using std::array, std::sort;
//////////////////////////////////////////////////////////////
// globals
//////////////////////////////////////////////////////////////
constexpr size_t NUM_PT = 11;
constexpr int SCALE = 4;

//////////////////////////////////////////////////////////////
// types
//////////////////////////////////////////////////////////////
struct pt {
  int x, y;
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
  return pt{ rand_num(first,last), rand_num(first,last) };
}

vector<pt> solve_convex_hull(array<pt, NUM_PT> pts) {
  auto angle_formed = [](pt a, pt b, pt c) {
    pt ab = pt{b.x-a.x, b.y-a.y}; 
    pt bc = pt{c.x-b.x, c.y-b.y}; 
    int dotprod = ab.x * bc.x + ab.y * bc.y;
    float lenAB = sqrt(ab.x*ab.x + ab.y*ab.y);
    float lenBC = sqrt(bc.x*bc.x + bc.y*bc.y);
    float ans_radians = acos( (float)dotprod / lenAB / lenBC);
    return ans_radians * 180.0 / M_PI;
  };

  
  vector<pt> soln;
  // step 1, sort by x then y
  sort(pts.begin(), pts.end(), less_than());
  // add first 3 points
  //
  return soln;

}

//////////////////////////////////////////////////////////////
// main function
//////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  // random points 
  srand(time(NULL));
  array<pt,NUM_PT> pts;
  // soln can't have more points than the pts themselves
  vector<pt> soln(NUM_PT); 

  for (int i = 0; i < NUM_PT; i++) {
    pts[i] = create_rand_pt(80/SCALE,(600-80)/SCALE);
  }

  soln = solve_convex_hull(pts);

  // create window and draw solution

  if (SDL_Init(SDL_INIT_VIDEO) == 0) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_CreateWindowAndRenderer(600, 600, 0, &window, &renderer) == 0) {
      SDL_bool done = SDL_FALSE;

      SDL_RenderSetScale(renderer, SCALE, SCALE);

      while (!done) {
        SDL_Event event;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        // draw the points
        for (int i = 0; i < NUM_PT; i++) 
          SDL_RenderDrawPoint(renderer, pts[i].x, pts[i].y);

        // draw the solution
        SDL_SetRenderDrawColor(renderer, 100, 5, 200, SDL_ALPHA_OPAQUE);
        auto num_lines = soln.size();
        for (int i = 0; i < num_lines; i++) {
          if (i != num_lines - 1) {
            SDL_RenderDrawLine(renderer, soln[i].x, soln[i].y, \
                soln[i+1].x, soln[i+1].y);
          } else {
            SDL_RenderDrawLine(renderer, soln[i].x, soln[i].y, \
                soln[0].x, soln[0].y);
          }
        }

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
