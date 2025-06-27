#include "Application.h"
#include "scene/SceneSystem.h"
#include <iostream>

#define FPS 60

Application::Application() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        running_ = false;
        return;
    }

    window_ = SDL_CreateWindow("Dylan Game Engine", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!window_) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        running_ = false;
        return;
    }

    renderer_ = SDL_CreateRenderer(window_, nullptr);
    if (!renderer_) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << "\n";
        running_ = false;
        return;
    }

    running_ = true;
}

Application::~Application() {
    if (renderer_) SDL_DestroyRenderer(renderer_);
    if (window_) SDL_DestroyWindow(window_);
    SDL_Quit();
}

int Application::run(int argc, char** argv) {
    const float dt = 1.0f / FPS;

    while (running_) {
        Uint64 start = SDL_GetTicksNS();

        process_input();
        update(dt);
        render();

        Uint64 elapsed = SDL_GetTicksNS() - start;
        int delay_ms = int(1000 * dt) - (elapsed / 1000000ULL);
        if (delay_ms > 0) {
            SDL_Delay(delay_ms);
        }
    }

    return 0;
}

void Application::process_input() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_QUIT) {
            running_ = false;
        }
    }
}

void Application::update(float dt) {
    update_scene(registry_);
}

void Application::render() {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
    // TODO: desenhar entidades da cena aqui

    SDL_RenderPresent(renderer_);
}
