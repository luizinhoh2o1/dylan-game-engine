#include "GameLoop.h"
#include "../ecs/systems/player_control_system.h"
#include <SDL3/SDL.h>

#include "imgui_impl_sdl3.h"

#define FPS 60

int run_game_loop(Application& app) {
    const float dt = 1.0f / FPS;

    SDL_Event e;

    while (app.is_running()) {
        Uint64 start = SDL_GetTicksNS();

        while (SDL_PollEvent(&e)) {
            ImGui_ImplSDL3_ProcessEvent(&e);
            if (e.type == SDL_EVENT_QUIT) {
                app.stop();
            }

            player_control_system(app.get_registry(), e, app.get_player_speed());
        }

        app.update(dt);
        app.render();

        Uint64 elapsed = SDL_GetTicksNS() - start;
        int delay_ms = int(1000 * dt) - (elapsed / 1000000ULL);
        if (delay_ms > 0) {
            SDL_Delay(delay_ms);
        }
    }

    return 0;
}
