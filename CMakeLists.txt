cmake_minimum_required(VERSION 3.31)
project(dylan_game_engine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# SDL3
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

# ImGui
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG master
)
FetchContent_MakeAvailable(imgui)

# ImGui custom build
add_library(imgui_custom STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)

target_include_directories(imgui_custom PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
        ${SDL3_SOURCE_DIR}/include
        ${SDL3_BINARY_DIR}/include-revision
)

add_library(imgui::imgui ALIAS imgui_custom)

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
        engine/src/*.cpp
        engine/src/*.h
)

add_executable(dylan_game_engine ${ENGINE_SOURCES})

target_include_directories(dylan_game_engine PRIVATE
        engine/src
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
        ${SDL3_SOURCE_DIR}/include
        ${SDL3_BINARY_DIR}/include-revision
)

target_link_libraries(dylan_game_engine PRIVATE
        imgui::imgui
        EnTT::EnTT
        SDL3::SDL3
)