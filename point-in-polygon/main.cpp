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
constexpr int NUM_POLY = 10;
vector<P> bullets;
vector<Poly> polys;

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
  const double rad = 15.0;  // set poly scale
  const double d_ang = 2 * M_PI / nvert;
  for (int i = 0; i < nvert; i++) {
    P _p = polar(rad, d_ang * (i + 1));
    tmp.push_back(_p);
  }
  assert(tmp.size() == nvert);
  return tmp;
}

// shift all points of polygon by a point
auto shift_poly(Poly poly, const P shift) -> Poly {
  const auto sz = poly.size();
  for (int i = 0; i < sz; i++) {
    poly[i] += shift;
  }
  return poly;
}

auto generate_bullet() -> P { return P{}; }

//////////////////////////////////////////////////////////////
// main function
//////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
  // random points
  srand(time(NULL));

  // generate polygons
  polys.resize(NUM_POLY);

  for (auto& p : polys) {
    p = generate_poly();  // gen poly centered on 0,0
    const C xshift = rand_num(WINDIM / SCALE * 0.10, WINDIM / SCALE * 0.90);
    const C yshift = rand_num(WINDIM / SCALE * 0.10, WINDIM / SCALE * 0.75);
    p = shift_poly(p, P{xshift, yshift});
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
  // create window and draw solution
  if (SDL_Init(SDL_INIT_VIDEO) == 0) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_CreateWindowAndRenderer(WINDIM, WINDIM, 0, &window, &renderer) ==
        0) {
      SDL_bool done = SDL_FALSE;

      SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
      SDL_RenderSetScale(renderer, SCALE, SCALE);

      while (!done) {
        SDL_Event event;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Draw polygons
        // number of lines drawn equals number of vertices
        SDL_SetRenderDrawColor(renderer, 10, 250, 10, SDL_ALPHA_OPAQUE);
        for (const auto& p : polys) {
          const auto sz = p.size();
          // a---b---c
          for (int i = 0; i < sz - 1; i++) {
            SDL_RenderDrawLine(
                renderer, round(p[i].X), round(WINDIM / SCALE - p[i].Y),
                round(p[i + 1].X), round(WINDIM / SCALE - p[i + 1].Y));
          }
          // c----a
          SDL_RenderDrawLine(renderer, round(p[sz - 1].X),
                             round(WINDIM / SCALE - p[sz - 1].Y), round(p[0].X),
                             round(WINDIM / SCALE - p[0].Y));
        }
        // draw the bullets so they are on top
        //     SDL_SetRenderDrawColor(renderer, 255, 255, 255,
        //     SDL_ALPHA_OPAQUE); for (int i = 0; i < NUM_PT; i++)
        //       SDL_RenderDrawPoint(renderer, pts[i].x,
        //       WINDIM/SCALE-pts[i].y);
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
