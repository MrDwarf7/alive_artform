#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include "src/constants.hpp"
#include "src/event_handlers.hpp"
#include "src/globals.hpp"
#include "src/physics.hpp"
#include "src/string_manipulation.hpp"

#include <SDL2/SDL.h>

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

////// No idea why this is needed - but header files suck
// #include "event_handlers.cpp"
// #include "physics.cpp"
// #include "string_manipulation.cpp"

// Time step
float BASE_DT = 0.05f; // Initial time step

// Interaction params
float MOUSE_STRENGTH_DISPLACEMENT =
    500.0f; // strength & Distance of the 'pluck', initial value
int MOUSE_SIZE_THRESHOLD =
    30; // size/rows/cols of the 'plucking' area, initial value

float strings[NUM_STRINGS][N_POINTS];
float stringsPrev[NUM_STRINGS][N_POINTS];

// Wave simulation params
float CWAVE_SPEED = 4.0f; // wave speed
float GAMMA = 0.10f;      // damping factor

inline std::mt19937 generator(std::random_device{}());
inline std::uniform_int_distribution<int> randGen(0, 100);

// int main(int argc, char *argv[]) {
int main(void) {
  SDL_SetMainReady();
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window =
      SDL_CreateWindow("Wave Harp", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  initializeStrings();

  bool quit = false;
  bool scrollForDistance = false;
  // const float dt = BASE_DT;
  float accumulator = 0.0f;
  Uint32 prevTime = SDL_GetTicks();
  // Move this into a MousePointerTracker class or similar, don't modify global
  // variables directly.
  int mouseX, mouseY;
  int prevMouseX, prevMouseY;
  SDL_GetMouseState(&prevMouseX, &prevMouseY);

  while (!quit) {
    SDL_Event event;

    // TODO: @dwarf : on game reset - we're not resetting the BASE_DT lol.
    handleEvents(event, quit, scrollForDistance, BASE_DT);

    const Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
    const int deltaX = mouseX - prevMouseX; // Calculate horizontal movement

    if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
      strumStrings(mouseX, mouseY, deltaX);
    }

    updateDT(&prevTime, &accumulator);
    while (accumulator >= BASE_DT) {
      updatePhysics(BASE_DT);
      accumulator -= BASE_DT;
    }

    SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_RenderClear(renderer);
    render(renderer);
    SDL_RenderPresent(renderer);

    // Update prevs to current frame's values
    prevMouseX = mouseX;
    prevMouseY = mouseY;
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
