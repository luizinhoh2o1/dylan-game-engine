#pragma once
#include <entt/entt.hpp>
#include "../components/transform.h"

void movement_system(entt::registry& registry, float dt) {
    auto view = registry.view<Position, Velocity>();
    for (auto entity : view) {
        auto& pos = view.get<Position>(entity);
        auto& vel = view.get<Velocity>(entity);
        pos.value.x += vel.value.x * dt;
        pos.value.y += vel.value.y * dt;
    }
}