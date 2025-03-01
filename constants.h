#pragma once
#include <SDL.h> // SDL_Color

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

// Both time-steps are really cool, I want to add a key to switch between them in the future,
// or perhaps + and - keys to increase or decrease the time step
// constexpr float BASE_DT = 0.005f; // time step -- fairly slow, methodical and hipnotic

// Colors
constexpr SDL_Color WHITE = {255, 255, 255, 255};
constexpr SDL_Color BLACK = {0, 0, 0, 255};

// Window dimensions
constexpr int WIDTH = 1600;
constexpr int HEIGHT = 800;

// String simulation params
constexpr int NUM_STRINGS = 120;
constexpr int N_POINTS = 110;
