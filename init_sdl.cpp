#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

#include "constants.cpp"

struct Initializer {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    int success;


    static Initializer fail() { return {nullptr, nullptr, nullptr, 1}; }

    ~Initializer() {
        if (success > 0) {
            TTF_CloseFont(font);
            TTF_Quit();
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }
    }


    Initializer initSDL() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
            return fail();
        }

        if (TTF_Init() == -1) {
            std::cerr << "SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
            SDL_Quit();
            return fail();
        }

        TTF_Font *font = TTF_OpenFont("arial.ttf", 24); // Replace "arial.ttf" with your font file path
        if (!font) {
            std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
            TTF_Quit();
            SDL_Quit();
            return fail();
        }

        SDL_Window *window = SDL_CreateWindow("Alive Art-Form", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return fail();
        }

        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            return fail();
        }

        return {window, renderer, font, 0};
    }
};
