#include "event_handlers.hpp"
#include <iostream>
#include "globals.hpp"
#include "string_manipulation.hpp"

void mouseDisplacementHandler(const SDL_Event &event) {
    if (event.wheel.y > 0) { // scroll up
        MOUSE_STRENGTH_DISPLACEMENT += 100.0f;
        if (MOUSE_STRENGTH_DISPLACEMENT > 5000.0f) {
            MOUSE_STRENGTH_DISPLACEMENT = 5000.0f;
        }
        std::cout << "DISPLACEMENT_STRENGTH: " << MOUSE_STRENGTH_DISPLACEMENT << std::endl;

    } else if (event.wheel.y < 0) { // scroll down
        MOUSE_STRENGTH_DISPLACEMENT -= 100.0f;
        if (MOUSE_STRENGTH_DISPLACEMENT < 10.0f) {
            MOUSE_STRENGTH_DISPLACEMENT = 10.0f;
            std::cout << "DISPLACEMENT_STRENGTH: " << MOUSE_STRENGTH_DISPLACEMENT << std::endl;
        }
    }
}

void mouseSizeHandler(const SDL_Event &event) {
    if (event.wheel.y > 0) { // scroll up
        MOUSE_SIZE_THRESHOLD += 1;
        if (MOUSE_SIZE_THRESHOLD > 100) {
            MOUSE_SIZE_THRESHOLD = 100;
        }
        std::cout << "MOUSE_DISTANCE_THRESHOLD: " << MOUSE_SIZE_THRESHOLD << std::endl;

    } else if (event.wheel.y < 0) { // scroll down
        MOUSE_SIZE_THRESHOLD -= 1;
        if (MOUSE_SIZE_THRESHOLD < 1) {
            MOUSE_SIZE_THRESHOLD = 1;
            std::cout << "MOUSE_DISTANCE_THRESHOLD: " << MOUSE_SIZE_THRESHOLD << std::endl;
        }
    }
}

void scrollHandler(const SDL_Event &event, const bool *scrollForDistance) {
    if (*scrollForDistance) {
        mouseDisplacementHandler(event);
    } else {
        mouseSizeHandler(event);
    }
}

void handleEvents(SDL_Event &event, bool &quit, bool &scrollForDistance, float &BASE_DT) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                case SDLK_q:
                    quit = true;
                    break;
                case SDLK_r:
                    initializeStrings();
                    break;
                case SDLK_KP_PLUS:
                case SDLK_UP:
                case SDLK_PLUS:
                    BASE_DT += 0.0005f;
                    if (BASE_DT > 0.06f) {
                        BASE_DT = 0.06f;
                    }
                    std::cout << "BASE_DT: " << BASE_DT << std::endl;
                    break;
                case SDLK_KP_MINUS:
                case SDLK_DOWN:
                case SDLK_MINUS:
                    BASE_DT -= 0.0005f;
                    if (BASE_DT < 0.001f) {
                        BASE_DT = 0.001f;
                    }
                    std::cout << "BASE_DT: " << BASE_DT << std::endl;
                    break;
                case SDLK_t:
                    scrollForDistance = true;
                    std::cout << "Scrolling for distance" << std::endl;
                default:
                    continue;
            }
        } else if (event.type == SDL_MOUSEWHEEL) {
            std::cout << "MOUSE_WHEEL: " << event.wheel.y << std::endl;
            scrollHandler(event, &scrollForDistance);
        }
    }
}
