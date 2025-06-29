#pragma once
#include <entt/entt.hpp>
#include <SDL3/SDL.h>
#include "../components/transform.h"
#include "../components/render.h"

void render_system(entt::registry& registry, SDL_Renderer* renderer) {
    auto view = registry.view<Position, Size, Color>();
    for (auto entity : view) {
        const auto& pos = view.get<Position>(entity);
        const auto& size = view.get<Size>(entity);
        const auto& color = view.get<Color>(entity);

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        SDL_FRect rect { pos.value.x, pos.value.y, size.w, size.h };
        SDL_RenderFillRect(renderer, &rect);
    }
}