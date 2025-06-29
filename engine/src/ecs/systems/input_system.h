#pragma once
#include <entt/entt.hpp>
#include "../components/transform.h"
#include "../components/player.h"

void input_system(entt::registry& registry, bool up, bool down, bool left, bool right, float speed) {
    auto view = registry.view<Velocity, PlayerTag>();
    for (auto entity : view) {
        SDL_FPoint v{0.f, 0.f};
        if (up)    v.y -= 1.f;
        if (down)  v.y += 1.f;
        if (left)  v.x -= 1.f;
        if (right) v.x += 1.f;

        if (v.x != 0 || v.y != 0) {
            float len = std::sqrt(v.x * v.x + v.y * v.y);
            v.x = (v.x / len) * speed;
            v.y = (v.y / len) * speed;
        }

        view.get<Velocity>(entity).value = v;
    }
}