#include "SDL.h"
#include <bits/stdc++.h>

using std::ostream, std::cout, std::ios, std::cin,std::vector, std::array;
//////////////////////////////////////////////////////////////
// globals
//////////////////////////////////////////////////////////////
constexpr size_t NUM_PT = 20;

//////////////////////////////////////////////////////////////
// types
//////////////////////////////////////////////////////////////
struct pt {
  int x, y;
  friend ostream& operator<<(ostream& os, const pt& p) {
    os << "x: " << p.x << "\ty:" << p.y;
    return os;
  }
};

//////////////////////////////////////////////////////////////
// free functions
//////////////////////////////////////////////////////////////
pt create_rand_pt(int first, int last) {
  return pt{rand() % (last - first) + first, rand() % (last - first) + first};
}

vector<pt> solve_convex_hull(array<pt, NUM_PT> pts) {
  vector<pt> soln(NUM_PT);
  return soln;

}

//////////////////////////////////////////////////////////////
// main function
//////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  // generate random points 
  array<pt,NUM_PT> pts;
  // soln can't have more points than the pts themselves
  vector<pt> soln(NUM_PT); 

  for (int i = 0; i < NUM_PT; i++) {
    pts[i] = create_rand_pt(5,80);
  }

  soln = solve_convex_hull(pts);

  // create window and draw solution

  if (SDL_Init(SDL_INIT_VIDEO) == 0) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_CreateWindowAndRenderer(400, 400, 0, &window, &renderer) == 0) {
      SDL_bool done = SDL_FALSE;

      SDL_RenderSetScale(renderer, 4.f, 4.f);

      while (!done) {
        SDL_Event event;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        // draw the points
        for (int i = 0; i < NUM_PT; i++) 
          SDL_RenderDrawPoint(renderer, pts[i].x, pts[i].y);

        // draw the solution
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
