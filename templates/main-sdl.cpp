#include "SDL.h"

using std::cout, std::endl, std::vector, std::polar, std::arg;

//////////////////////////////////////////////////////////////
// globals
//////////////////////////////////////////////////////////////
constexpr float SCALE = 4;
constexpr int WINDIM = 800;

//////////////////////////////////////////////////////////////
// Functions that are only in this file
//////////////////////////////////////////////////////////////
int rand_num(const int lower, const int upper) {
  return (rand() % (upper - lower + 1)) + lower;
}

P create_rand_pt(int first, int last) {
  auto num1 = rand_num(first, last);
  auto num2 = rand_num(first, last);
  return P{static_cast<float>(num1), static_cast<float>(num2)};
}

//////////////////////////////////////////////////////////////
// main function
//////////////////////////////////////////////////////////////
auto main(int argc, char* argv[]) -> int {
  ////////////////////////////////////////////////////////////
  // init
  // /////////////////////////////////////////////////////////
  srand(time(NULL));

  // create window and draw solution
  if (SDL_Init(SDL_INIT_VIDEO) == 0) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_CreateWindowAndRenderer(WINDIM, WINDIM, 0, &window, &renderer) ==
        0) {
      SDL_bool done = SDL_FALSE;

      SDL_RenderSetScale(renderer, SCALE, SCALE);

      // main loop
      while (!done) {
        SDL_Event event;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Draw polygons
        // number of lines drawn equals number of vertices
        SDL_SetRenderDrawColor(renderer, 10, 250, 10, SDL_ALPHA_OPAQUE);
        for (size_t poly_idx = 0; poly_idx < NUM_POLY; poly_idx++) {
          if (!poly_draw_flag[poly_idx]) continue;
          const auto& p = polys[poly_idx];
          const auto sz = p.size();
          // draw sz-1 lines a---b---c
          for (size_t i = 0; i < sz - 1; i++) {
            SDL_RenderDrawLine(
                renderer, round(p[i].X), round(WINDIM / SCALE) - round(p[i].Y),
                round(p[i + 1].X), round(WINDIM / SCALE) - round(p[i + 1].Y));
          }
          // draw last line c----a
          SDL_RenderDrawLine(renderer, round(p[sz - 1].X),
                             round(WINDIM / SCALE) - round(p[sz - 1].Y),
                             round(p[0].X),
                             round(WINDIM / SCALE) - round(p[0].Y));
        }
        for (size_t bi = 0; bi < NUM_BOMB; bi++) {
          SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
          SDL_RenderDrawPoint(renderer, round(bombs[bi].X),
                              round(WINDIM / SCALE) - round(bombs[bi].Y + 2));
        }

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
          if (event.type == SDL_QUIT) {
            done = SDL_TRUE;
          }
        }
        SDL_Delay(16);
        if (0) break;
      }  // end of main loop
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
