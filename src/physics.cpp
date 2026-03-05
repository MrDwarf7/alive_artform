#include "src/physics.hpp"
#include "src/globals.hpp"
#include <SDL2/SDL_timer.h>
// #include <cmath>

float xBaseCalc(const int s) {
  return static_cast<float>(s) * WIDTH / (NUM_STRINGS - 1);
}

float laplacian(const int s, const int i) {
  return strings[s][i + 1] - 2 * strings[s][i] + strings[s][i - 1];
}

void updatePhysics(const float dt) {
  constexpr float dx = 1.0f;
  const float cfl = CWAVE_SPEED * CWAVE_SPEED * dt * dt / (dx * dx);
  for (int s = 0; s < NUM_STRINGS; s++) {
    for (int i = 1; i < N_POINTS - 1; i++) {
      const float lap = laplacian(s, i);
      const float vel = strings[s][i] - stringsPrev[s][i];
      stringsPrev[s][i] = strings[s][i];
      strings[s][i] =
          2 * strings[s][i] - stringsPrev[s][i] + cfl * lap - GAMMA * dt * vel;
    }
    strings[s][0] = strings[s][N_POINTS - 1] = 0.0f;
  }
}

void render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
  for (int s = 0; s < NUM_STRINGS; s++) {
    SDL_Point pts[N_POINTS];
    const float xBase = xBaseCalc(s);
    for (int i = 0; i < N_POINTS; i++) {
      const float y = static_cast<float>(i) * HEIGHT / (N_POINTS - 1);
      const float displace =
          strings[s][i] * MOUSE_STRENGTH_DISPLACEMENT; // displacement
      pts[i] = {static_cast<int>(xBase + displace), static_cast<int>(y)};
    }
    SDL_RenderDrawLines(renderer, &pts[0], N_POINTS);
  }
}

void updateDT(Uint32 *lastTime, float *accumulator) {
  const Uint32 currentTime = SDL_GetTicks();
  const float frameTime = static_cast<float>(currentTime - *lastTime) / 1000.0f;
  *lastTime = currentTime;
  *accumulator += frameTime;
}
