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
// main function
//////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  // handle flags
  // random points 
  srand(time(NULL));
  vector<pt> pts(NUM_PT);

  for (int i = 0; i < NUM_PT; i++) {
    pts[i] = create_rand_pt(100/SCALE,(WINDIM-100)/SCALE);
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
