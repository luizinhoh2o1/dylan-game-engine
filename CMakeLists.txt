cmake_minimum_required(VERSION 3.31)
project(dylan_game_engine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL3
include(FetchContent)
FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG main
)
FetchContent_MakeAvailable(SDL3)

# EnTT
FetchContent_Declare(
        entt
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG v3.13.0
)
FetchContent_MakeAvailable(entt)

# Busca todos os arquivos .cpp e .h da engine
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
        "engine/src/*.cpp"
        "engine/src/*.h"
)

# Executável principal
add_executable(dylan_game_engine ${ENGINE_SOURCES}
        engine/src/scene/SceneComponents.h
        engine/src/scene/SceneSystem.cpp
        engine/src/scene/SceneSystem.h
        engine/src/math/mat3x3.h
        engine/src/ecs/components/transform.h
        engine/src/ecs/components/render.h
        engine/src/ecs/components/physics.h
        engine/src/ecs/components/player.h
        engine/src/ecs/components/components.h
        engine/src/ecs/systems/input_system.h
        engine/src/ecs/systems/movement_system.h
        engine/src/ecs/systems/render_system.h
        engine/src/ecs/systems/systems.h
        engine/src/ecs/systems/player_control_system.h
        engine/src/core/GameLoop.h
        engine/src/core/SDLContext.h)

# Include para arquivos dentro de engine/src
target_include_directories(dylan_game_engine PRIVATE engine/src)

# Link SDL3
target_link_libraries(dylan_game_engine PRIVATE SDL3::SDL3 EnTT::EnTT)