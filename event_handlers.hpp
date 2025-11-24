#pragma once

#include <iostream>
#include "globals.hpp"

void mouseDisplacementHandler(const SDL_Event &event);
void mouseSizeHandler(const SDL_Event &event);
void scrollHandler(const SDL_Event &event, const bool *scrollForDistance);
void handleEvents(SDL_Event &event, bool &quit, bool &scrollForDistance, float &BASE_DT);
