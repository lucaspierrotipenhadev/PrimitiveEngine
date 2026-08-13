#include "Primitive/Core/Application.hpp"
#include "Primitive/Core/Engine.hpp"

#include <iostream>

namespace primitive
{
    Application::Application()
        : m_engine(std::make_unique<Engine>())
    {
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        m_engine->Run();
    }
}