#include "Primitive/Core/Engine.hpp"

#include <iostream>

namespace primitive
{
    Engine::Engine()
    {
        std::cout << "[Engine] Constructing engine...\n";
    }

    Engine::~Engine()
    {
        std::cout << "[Engine] Destroying engine...\n";
    }

    void Engine::Run()
    {
        Initialize();

        m_running = true;

        std::cout << "[Engine] Starting main loop...\n";

        while (m_running)
        {
            m_time.BeginFrame();

            ProcessEvents();
            Update(m_time.GetDeltaTime());
            Render();

            if(m_time.GetFrameCount() >= 300000)
            {
                Stop();
            }
        }

        Shutdown();
    }

    void Engine::Stop()
    {
        m_running = false;
    }

    void Engine::Initialize()
    {
        std::cout << "[Engine] Initializing...\n";
    }

    void Engine::Shutdown()
    {
        std::cout << "[Engine] Shutting down...\n";
    }

    void Engine::ProcessEvents()
    {
        // Eventos serão implementados posteriormente através do SDL3.
    }

    void Engine::Update(float deltaTime)
    {
        (void)deltaTime;

        if (m_time.GetFrameCount() % 60 == 0)
        {
            std::cout
                << "[Engine] Frame: "
                << m_time.GetFrameCount()
                << "Delta :"
                << m_time.GetDeltaTime()
                << "FPS: "
                << m_time.GetFPS()
                << '\n';
        }
    }

    void Engine::Render()
    {
        // Renderização será implementada posteriormente.
    }
}