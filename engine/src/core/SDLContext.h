#pragma once
#include <SDL3/SDL.h>
#include <iostream>

struct SDLContext {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    bool initialize(const char* title, int width, int height) {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
            return false;
        }

        window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
        if (!window) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
            SDL_Quit();
            return false;
        }

        renderer = SDL_CreateRenderer(window, nullptr);
        if (!renderer) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << "\n";
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }

        return true;
    }

    void shutdown() {
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);
        SDL_Quit();
    }
};
