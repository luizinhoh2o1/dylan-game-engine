#include "Application.h"

#include "SDLContext.h"
#include "scene/SceneSystem.h"
#include "ecs/systems/systems.h"
#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>

static SDLContext sdl;

Application::Application() {
    if (!sdl.initialize("Dylan Game Engine", 800, 600)) {
        running_ = false;
        return;
    }

    window_ = sdl.window;
    renderer_ = sdl.renderer;

    init_imgui();
    init_entities();

    running_ = true;
}

Application::~Application() {
    if (renderer_) SDL_DestroyRenderer(renderer_);
    if (window_) SDL_DestroyWindow(window_);

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_Quit();
}

void Application::update(float dt) {
    movement_system(registry_, dt);
    update_scene(registry_);
}

void Application::render() {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
    render_system(registry_, renderer_);

    // ImGui Begin
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    // Desenha uma janela de teste
    ImGui::ShowDemoWindow();  // <-- Janela de testes com vários widgets

    // Fim do ImGui
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer_);

    SDL_RenderPresent(renderer_);
}

void Application::stop() {
    running_ = false;
}

bool Application::is_running() const {
    return running_;
}

SDL_Renderer* Application::get_renderer() const {
    return renderer_;
}

entt::registry& Application::get_registry() {
    return registry_;
}

float Application::get_player_speed() const {
    return player_speed_;
}

void Application::init_entities() {
    auto player = registry_.create();
    registry_.emplace<Position>(player, SDL_FPoint{100.f, 100.f});
    registry_.emplace<Velocity>(player);
    registry_.emplace<Size>(player, 100.f, 100.f);
    registry_.emplace<Color>(player, 255, 0, 0, 255);
    registry_.emplace<PlayerTag>(player);
}

void Application::init_imgui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark(); // ou ImGui::StyleColorsClassic();

    ImGui_ImplSDL3_InitForSDLRenderer(window_, renderer_);
    ImGui_ImplSDLRenderer3_Init(renderer_);
}