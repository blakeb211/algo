#include "SDL.h"
#include "piplib.h"

/* Visual demonstration of the point-in-polygon algorithm.
 * Generate a few random polys that bounce around the screen.
 * Generate bombs drawn as little circles that come from
 * the top of the screen and destroy the polygons when they
 * collide with (i.e. are inside of) them.
 */

using std::cout, std::endl, std::vector, std::polar, std::arg;

//////////////////////////////////////////////////////////////
// globals
//////////////////////////////////////////////////////////////
constexpr size_t NUM_PT = 11;
constexpr float SCALE = 4;
constexpr int WINDIM = 800;
constexpr size_t NUM_POLY = 12;
constexpr size_t NUM_BOMB = 6;
vector<P> bombs;
vector<Poly> polys;
vector<bool> poly_draw_flag;

//////////////////////////////////////////////////////////////
// Functions that are only in this file, not the pip library
//////////////////////////////////////////////////////////////
int rand_num(const int lower, const int upper) {
  return (rand() % (upper - lower + 1)) + lower;
}

P create_rand_pt(int first, int last) {
  auto num1 = rand_num(first, last);
  auto num2 = rand_num(first, last);
  return P{static_cast<float>(num1), static_cast<float>(num2)};
}

auto generate_poly() -> Poly {
  Poly tmp;
  const int nvert = rand_num(3, 10);
  const double rad = 30.0/SCALE;  // set poly scale
  const double d_ang = 2 * M_PI / nvert;
  for (int i = 0; i < nvert; i++) {
    P _p = polar(rad, d_ang * (i + 1));
    tmp.push_back(_p);
  }
  assert(tmp.size() == (size_t)nvert);
  return tmp;
}

// shift all points of polygon by a point
auto shift_poly(Poly poly, const P shift) -> Poly {
  const auto sz = poly.size();
  for (size_t i = 0; i < sz; i++) {
    poly[i] += shift;
  }
  return poly;
}

auto generate_bomb() -> P {
  const C x = rand_num(WINDIM / SCALE * 0.10, WINDIM / SCALE * 0.90);
  return P{x, WINDIM / SCALE - rand_num(3, 10)};
}

auto update_bombs() -> void {
  for (auto& b : bombs) {
    b = b + P{0.0, -1.0};
    if (b.Y <= 0.0) b = generate_bomb();
  }
}

auto check_collisions() -> void {
for (auto & b : bombs) {
  for (size_t poly_idx = 0; poly_idx < NUM_POLY; poly_idx++) {
    if (is_inside(b, polys[poly_idx])) {
      poly_draw_flag[poly_idx] = false;
    }
  }
}

}
//////////////////////////////////////////////////////////////
// main function
//////////////////////////////////////////////////////////////
auto main(int argc, char* argv[]) -> int {
  // random points
  srand(time(NULL));

  ////////////////////////////////////////////////////////////
  // init
  // /////////////////////////////////////////////////////////
  polys.resize(NUM_POLY);
  poly_draw_flag.resize(NUM_POLY);
  std::fill(poly_draw_flag.begin(), poly_draw_flag.end(), true);
  bombs.resize(NUM_BOMB);

  // generate polygons
  for (auto& p : polys) {
    p = generate_poly();  // gen poly centered on 0,0
    const C xshift = rand_num(WINDIM / SCALE * 0.10, WINDIM / SCALE * 0.90);
    const C yshift = rand_num(WINDIM / SCALE * 0.10, WINDIM / SCALE * 0.75);
    p = shift_poly(p, P{xshift, yshift});
  }

  // generate falling bombs
  for (auto& b : bombs) {
    b = generate_bomb();
  }

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
        update_bombs();
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
        // draw the bombs so they are on top
        for (size_t bi = 0; bi < NUM_BOMB; bi++) {
          SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
          SDL_RenderDrawPoint(renderer, round(bombs[bi].X),
                              round(WINDIM / SCALE) - round(bombs[bi].Y + 2));
          SDL_RenderDrawPoint(renderer, round(bombs[bi].X),
                              round(WINDIM / SCALE) - round(bombs[bi].Y - 2));
          SDL_RenderDrawPoint(renderer, round(bombs[bi].X + 2),
                              round(WINDIM / SCALE) - round(bombs[bi].Y));
          SDL_RenderDrawPoint(renderer, round(bombs[bi].X - 2),
                              round(WINDIM / SCALE) - round(bombs[bi].Y));
          SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
          SDL_RenderDrawPoint(renderer, round(bombs[bi].X),
                              round(WINDIM / SCALE) - round(bombs[bi].Y));
        }

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
          if (event.type == SDL_QUIT) {
            done = SDL_TRUE;
          }
        }
        check_collisions();
        SDL_Delay(16);
        // exit if all polygons destroyed
        if (std::accumulate(poly_draw_flag.begin(), poly_draw_flag.end(),0) == 0)
          break;
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
