#include "SDL.h"
#include <bits/stdc++.h>
#include "convexlib.h"

/*******************************************************
 * TODO:
 * Write in C++
 ******************************************************/

using std::ostream, std::cout, std::ios, std::cin,std::vector;
using std::sort;

//////////////////////////////////////////////////////////////
// globals
//////////////////////////////////////////////////////////////
inline constexpr size_t NUM_PT = 11;
inline constexpr float SCALE = 8;
inline constexpr int WINDIM = 800;

//////////////////////////////////////////////////////////////
// main function
//////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  // random points 
  srand(time(NULL));
  vector<pt> pts(NUM_PT);

  for (int i = 0; i < NUM_PT; i++) {
    pts[i] = create_rand_pt(200/SCALE,(WINDIM-200)/SCALE);
  }

  vector<pt> soln1 = solve_convex_hull(pts, true);
  vector<pt> soln2 = solve_convex_hull(pts, false);
  
  //  print out soln array
  cout << "UPPER SOLUTION POINTS (" << soln1.size() << "):\n";
  for (const auto i : soln1)
    cout << i << "\n";
  cout << "LOWER SOLUTION POINTS (" << soln2.size() << "):\n";
  for (const auto i : soln2)
    cout << i << "\n";

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

        // draw the upper half of the solution
        SDL_SetRenderDrawColor(renderer, 100, 5, 255, SDL_ALPHA_OPAQUE);
        auto num_lines = soln1.size() - 1;
        // a---b---c----d
        for (int i = 0; i < num_lines; i++) {
          SDL_RenderDrawLine(renderer, soln1[i].x, WINDIM/SCALE-soln1[i].y, \
              soln1[i+1].x, WINDIM/SCALE-soln1[i+1].y);
        }
       
        // draw the lower half of the solution
        num_lines = soln2.size() - 1;
        for (int i = 0; i < num_lines; i++) {
          SDL_RenderDrawLine(renderer, soln2[i].x, WINDIM/SCALE-soln2[i].y, \
              soln2[i+1].x, WINDIM/SCALE-soln2[i+1].y);
        }

        // draw the points so they are on top
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
