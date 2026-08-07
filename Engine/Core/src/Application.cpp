#include "Primitive/Core/Application.hpp"
#include "Primitive/Core/Engine.hpp"

#include <iostream>

namespace primitive
{
    Application::Application()
        : m_engine(std::make_unique<Engine>())
    {
        std::cout << "[Application] Starting application...\n";
    }

    Application::~Application()
    {
        std::cout << "[Application] Application shutdown.\n";
    }

    void Application::Run()
    {
        m_engine->Run();
    }
}