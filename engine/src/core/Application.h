#pragma once

#include <SDL3/SDL.h>
#include <entt/entt.hpp>

class Application {
public:
    Application();
    ~Application();

    void update(float dt);
    void render();
    void init_imgui();
    void stop();

    // Getters
    bool is_running() const;
    SDL_Renderer* get_renderer() const;
    entt::registry& get_registry();
    float get_player_speed() const;

private:
    void init_entities();

    bool running_ = true;
    float player_speed_ = 200.0f;

    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
    entt::registry registry_;
};
