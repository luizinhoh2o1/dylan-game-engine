#pragma once

#include <SDL3/SDL.h>
#include <entt/entt.hpp>

class Application {
public:
    Application();
    ~Application();

    int run(int argc, char** argv);

private:
    void process_input();
    void update(float dt);
    void render();

    bool running_;
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    entt::registry registry_;
};
