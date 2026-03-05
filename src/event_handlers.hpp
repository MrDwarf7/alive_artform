// #pragma once

#ifndef EVENT_HANDLERS_HPP
#define EVENT_HANDLERS_HPP

// #include "globals.hpp"
#include "SDL_events.h"
// #include <iostream>

void mouseDisplacementHandler(const SDL_Event &event);
void mouseSizeHandler(const SDL_Event &event);
void scrollHandler(const SDL_Event &event, const bool *scrollForDistance);
void handleEvents(SDL_Event &event, bool &quit, bool &scrollForDistance,
                  float &BASE_DT);

#endif // EVENT_HANDLERS_HPP
