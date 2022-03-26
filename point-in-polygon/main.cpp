#include "SDL.h"
#include "piplib.h"

/* Visual demonstration of the point-in-polygon algorithm.
 * Generate a few random polys that bounce around the screen.
 * Generate bullets drawn as little circles that come from
 * the top of the screen and destroy the polygons when they
 * are collide with (i.e. are inside of) them.
 */

using std::cout, std::endl, std::vector, std::polar, std::arg;

//////////////////////////////////////////////////////////////
// Functions that are only in this file, not the pip library 
//////////////////////////////////////////////////////////////
auto generate_poly() -> Poly;
auto generate_bullet() -> P;

auto test1() -> void {
  P a{1.0, 2.0};
  P b{2.5, 40.3};
  cout << "a: " << a << "b: " << b << endl;
  cout << "a + b" << a + b << endl;
  cout << "cross(a,b) : " << cross(a, b) << endl;
}

//////////////////////////////////////////////////////////////
// globals
//////////////////////////////////////////////////////////////
inline constexpr size_t NUM_PT = 11;
inline constexpr float SCALE = 8;
inline constexpr int WINDIM = 800;
vector<P> bullets;
vector<Poly> polys;

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

        //    // draw the upper half of the solution
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
