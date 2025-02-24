#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>

#include <cmath>
#include <iostream>
#include <vector>

#include "constants.cpp"
// #include "init_sdl.cpp"
#include "thread.cpp"

std::vector<Thread> threads;

void setup() {
    constexpr int numThreads = 50;
    int particlesPerThread = 100;
    float stiffness = 0.099f;
    for (int i = 0; i < numThreads; ++i) {
        float x = static_cast<float>(i + 1) * WIDTH / (numThreads + 1);
        threads.emplace_back(x, particlesPerThread, stiffness);
    }
}

void feed_keys(const SDL_Event &event, bool &quit, float &forceRadius, bool &isClicking, int &clickX, int &clickY) {
    switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }

        case SDL_MOUSEBUTTONDOWN:
            isClicking = true;
            SDL_GetMouseState(&clickX, &clickY);
            break;

        case SDL_MOUSEWHEEL:
            SDL_GetMouseState(&clickX, &clickY);
            const Sint32 direction = event.wheel.y;
            if (direction > 0) {
                forceRadius += 5.0f;
            } else {
                forceRadius -= 5.0f;
            }
    }
}

void render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, BLACK[0], BLACK[1], BLACK[2], BLACK[3]);
    SDL_RenderClear(renderer);
    for (auto &thread: threads) {
        thread.draw(renderer);
    }

    SDL_RenderPresent(renderer);
}

float time_delta(float &lastTime) {
    const Uint32 currentTime = SDL_GetTicks();
    const float td = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;
    return td;
}

int main(int argc, char *argv[]) {
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Alive Art-Form", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    setup();

    float td = SDL_GetTicks();

    bool quit = false;
    bool isClicking = false;
    int clickX = 0, clickY = 0;

    float forceRadius = 30.0f;

    SDL_Event event;

    while (!quit) {
        td = time_delta(td);

        while (SDL_PollEvent(&event)) {
            feed_keys(event, quit, forceRadius, isClicking, clickX, clickY);
        }

        for (auto &thread: threads) {
            thread.update(clickX, clickY, forceRadius, isClicking, td);
        }

        render(renderer);

        if (quit) {
            break;
        }

        SDL_Delay(16); // approx. 60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
