#include "Application.h"
#include <iostream>

namespace dylan {

    Application::Application() {
        std::cout << "Engine inicializada!\n";
    }

    Application::~Application() {
        std::cout << "Finalizando engine.\n";
    }

    void Application::Run() {
        std::cout << "Executando game loop...\n";
    }

}
