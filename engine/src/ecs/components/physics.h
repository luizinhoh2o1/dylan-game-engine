#pragma once

struct RigidBody {
    float mass = 1.f;
    bool is_static = false;
};

struct BoxCollider {
    float width = 32.f;
    float height = 32.f;
};
