#pragma once
#include <SDL3/SDL.h>
#include <entt/entt.hpp>
#include "../components/transform.h"
#include "../components/player.h"

inline void player_control_system(entt::registry& registry, SDL_Event& event, float speed) {
    if (event.type != SDL_EVENT_KEY_DOWN && event.type != SDL_EVENT_KEY_UP)
        return;

    bool pressed = event.type == SDL_EVENT_KEY_DOWN;

    auto view = registry.view<Velocity, PlayerTag>();

    for (auto entity : view) {
        auto& velocity = view.get<Velocity>(entity);

        if (!pressed) {
            velocity.value = {0.f, 0.f};
            continue;
        }

        switch (event.key.scancode) {
            case SDL_SCANCODE_UP:    velocity.value.y = -speed; break;
            case SDL_SCANCODE_DOWN:  velocity.value.y =  speed; break;
            case SDL_SCANCODE_LEFT:  velocity.value.x = -speed; break;
            case SDL_SCANCODE_RIGHT: velocity.value.x =  speed; break;
            default: break;
        }
    }
}
