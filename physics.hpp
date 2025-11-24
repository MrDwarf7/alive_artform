#pragma once

// #include "globals.hpp"

// // Function prototypes
float xBaseCalc(int s);
float laplacian(int s, int i);
void updatePhysics(float dt);
void render(SDL_Renderer *renderer);
void updateDT(Uint32 *lastTime, float *accumulator);
