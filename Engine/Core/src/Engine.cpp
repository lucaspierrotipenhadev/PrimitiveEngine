#include "Primitive/Core/Engine.hpp"

#include "Primitive/Core/Events/WindowEvents.hpp"
#include "Primitive/Renderer/OpenGL/OpenGLShader.hpp"

#include <SDL3/SDL.h>

namespace primitive
{
    Engine::Engine()
        : m_configuration(),
          m_platform(),
          m_input(),
          m_sdlInput(m_input, m_eventBus),
          m_window(m_configuration.window),
          m_renderer(),
          m_resourceManager()
    {
        m_logger.Info("Engine constructed.");
    }

    Engine::~Engine()
    {
        m_logger.Info("[Engine] Destroying engine...\n");
    }

    void Engine::Run()
    {
        Initialize();

        m_running = true;

        m_logger.Info("[Engine] Starting main loop...");

        while (m_running)
        {
            m_time.BeginFrame();

            m_input.BeginFrame();

            ProcessEvents();

            Update(m_time.GetDeltaTime());

            Render();
        }

        Shutdown();
    }

    void Engine::Stop()
    {
        m_running = false;
    }

    void Engine::Initialize()
    {
        m_eventBus.Subscribe<WindowClosedEvent>(
            [this](const WindowClosedEvent &)
            {
                Stop();
            });

        m_renderer.Initialize();

        auto shader = std::make_shared<OpenGLShader>(
            "assets/shaders/basic.glsl");

        shader->Bind();
        shader->Unbind();

        m_logger.Info("[Engine] Shader test passed.");

        m_logger.Info("[Engine] Initialized.");
    }

    void Engine::Shutdown()
    {
        m_renderer.Shutdown();
        m_logger.Info("[Engine] Shutting down...\n");
    }

    void Engine::ProcessEvents()
    {
        m_sdlInput.PollEvents();
    }

    void Engine::Update(float deltaTime)
    {
        (void)deltaTime;
    }

    void Engine::Render()
    {
        m_renderer.BeginFrame();
        m_renderer.Clear(1.0f, 0.0f, 0.0f, 1.0f);
        m_renderer.EndFrame();

        m_window.SwapBuffers();
    }

    Input &Engine::GetInput()
    {
        return m_input;
    }
}