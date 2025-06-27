#include "SceneSystem.h"
#include "SceneComponents.h"

void update_scene(entt::registry& registry) {
    auto view = registry.view<local_transform, internal::local_to_world>();

    for (auto entity : view) {
        auto& local = view.get<local_transform>(entity);
        auto& world = view.get<internal::local_to_world>(entity);

        mat3x3 T = mat3x3::translate(local.position.x, local.position.y);
        mat3x3 R = mat3x3::rotate(local.rotation);
        mat3x3 S = mat3x3::scale(local.scale.x, local.scale.y);

        world.mat = T * R * S;

        if (auto* p = registry.try_get<parent>(entity)) {
            if (registry.valid(p->entity) && registry.all_of<internal::local_to_world>(p->entity)) {
                world.mat = registry.get<internal::local_to_world>(p->entity).mat * world.mat;
            }
        }
    }
}
