#include "SDL.h"
#include "piplib.h"

/* Visual demonstration of the point-in-polygon algorithm.
 * Generate a few random polys that bounce around the screen.
 * Generate bullets drawn as little circles that come from
 * the top of the screen and destroy the polygons when they
 * collide with (i.e. are inside of) them.
 */

using std::cout, std::endl, std::vector, std::polar, std::arg;

//////////////////////////////////////////////////////////////
// globals
//////////////////////////////////////////////////////////////
constexpr size_t NUM_PT = 11;
constexpr float SCALE = 2;
constexpr int WINDIM = 800;
vector<P> bullets;
vector<Poly> polys;

//////////////////////////////////////////////////////////////
// Functions that are only in this file, not the pip library 
//////////////////////////////////////////////////////////////
int rand_num(const int lower, const int upper) {
  return ( rand() % (upper - lower + 1)) + lower; 
}

P create_rand_pt(int first, int last) {
  auto num1 = rand_num(first,last);
  auto num2 = rand_num(first,last);
  return P{ static_cast<float>(num1), static_cast<float>(num2) };
}

auto generate_poly() -> Poly {

}

auto generate_bullet() -> P {

}

//////////////////////////////////////////////////////////////
// main function
//////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
  // random points
  srand(time(NULL));

  // create window and draw solution
  if (SDL_Init(SDL_INIT_VIDEO) == 0) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_CreateWindowAndRenderer(WINDIM, WINDIM, 0, &window, &renderer) ==
        0) {
      SDL_bool done = SDL_FALSE;

      SDL_RenderSetScale(renderer, SCALE, SCALE);

      while (!done) {
        SDL_Event event;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        
        // Draw polygons
        //    SDL_SetRenderDrawColor(renderer, 100, 5, 255, SDL_ALPHA_OPAQUE);
        //    auto num_lines = soln1.size() - 1;
        //    // a---b---c----d
        //    for (int i = 0; i < num_lines; i++) {
        //      SDL_RenderDrawLine(renderer, soln1[i].x,
        //      WINDIM/SCALE-soln1[i].y, \
    //          soln1[i+1].x, WINDIM/SCALE-soln1[i+1].y);
        //    }

        // draw the bullets so they are on top
        //     SDL_SetRenderDrawColor(renderer, 255, 255, 255,
        //     SDL_ALPHA_OPAQUE); for (int i = 0; i < NUM_PT; i++)
        //       SDL_RenderDrawPoint(renderer, pts[i].x, WINDIM/SCALE-pts[i].y);

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
