#ifndef PHYSICS_HPP
#define PHYSICS_HPP

// #include "globals.hpp"

// // Function prototypes
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

float xBaseCalc(int s);
float laplacian(int s, int i);
void updatePhysics(float dt);
void render(SDL_Renderer *renderer);
void updateDT(Uint32 *lastTime, float *accumulator);

#endif // PHYSICS_HPP
