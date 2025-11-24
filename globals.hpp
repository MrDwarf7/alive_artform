#pragma once

#include <SDL.h>
#include <cmath>
#include <iostream>
#include <random>

#include "constants.hpp"
#include "globals.hpp"

extern float strings[NUM_STRINGS][N_POINTS];
extern float stringsPrev[NUM_STRINGS][N_POINTS];

extern float MOUSE_STRENGTH_DISPLACEMENT; // strength & Distance of the 'pluck', initial value
extern int MOUSE_SIZE_THRESHOLD; // size/rows/cols of the 'plucking' area, initial value

extern float CWAVE_SPEED; // wave speed
extern float GAMMA; // damping factor

// inline std::mt19937 generator(std::random_device{}());
extern std::mt19937 generator;
extern std::uniform_int_distribution<int> randGen;
