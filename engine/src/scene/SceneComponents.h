#pragma once

#include <unordered_set>
#include <SDL3/SDL.h>
#include <entt/entt.hpp>
#include "../math/mat3x3.h"

struct local_transform {
    SDL_FPoint position{0,0};
    SDL_FPoint scale{1,1};
    float rotation{0};
};

struct parent {
    entt::entity entity{entt::null};
};

namespace internal {
    struct local_to_world {
        mat3x3 mat;
    };

    struct children {
        std::unordered_set<entt::entity> entities;
    };
}
