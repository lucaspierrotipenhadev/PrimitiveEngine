#include "Primitive/Core/Engine.hpp"

#include "Primitive/Core/Events/WindowEvents.hpp"

#include "Primitive/Renderer/Shader.hpp"
#include "Primitive/Renderer/VertexBuffer.hpp"
#include "Primitive/Renderer/VertexArray.hpp"
#include "Primitive/Renderer/VertexBufferLayout.hpp"

#include <stdexcept>

namespace primitive
{
    Engine::Engine()
        : m_configuration(),
          m_platform(),
          m_input(),
          m_sdlInput(
              m_input,
              m_eventBus
          ),
          m_window(
              m_configuration.window
          ),
          m_renderer(),
          m_resourceManager()
    {
        m_logger.Info(
            "Engine constructed."
        );
    }

    Engine::~Engine()
    {
        m_logger.Info(
            "[Engine] Destroying engine..."
        );
    }

    void Engine::Run()
    {
        Initialize();

        m_running = true;

        m_logger.Info(
            "[Engine] Starting main loop..."
        );

        while (m_running)
        {
            m_time.BeginFrame();

            m_input.BeginFrame();

            ProcessEvents();

            Update(
                m_time.GetDeltaTime()
            );

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
        m_eventBus.Subscribe<
            WindowClosedEvent
        >(
            [this](
                const WindowClosedEvent&)
            {
                Stop();
            }
        );

        // Renderer escolhe e inicializa
        // o backend através da factory.
        m_renderer.Initialize(
            m_configuration.renderer.backend,
            m_resourceManager
        );

        // Engine conhece somente Shader.
        m_testShader =
            m_resourceManager.Load<Shader>(
                "Assets/Shaders/basic.glsl"
            );

        if (!m_testShader)
        {
            throw std::runtime_error(
                "Failed to load shader."
            );
        }

        const float vertices[] =
        {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        // Engine conhece somente VertexBuffer.
        m_testVertexBuffer =
            m_renderer.CreateVertexBuffer(
                vertices,
                sizeof(vertices)
            );

        VertexBufferLayout layout;

        layout.Push(
            ShaderDataType::Float3
        );

        // Engine conhece somente VertexArray.
        m_testVertexArray =
            m_renderer.CreateVertexArray();

        m_testVertexArray->AddVertexBuffer(
            *m_testVertexBuffer,
            layout
        );

        m_logger.Info(
            "[Engine] Triangle pipeline initialized."
        );

        m_logger.Info(
            "[Engine] Initialized."
        );
    }

    void Engine::Shutdown()
    {
        m_testVertexArray.reset();
        m_testVertexBuffer.reset();
        m_testShader.reset();

        // Libera recursos gráficos
        // enquanto o backend/contexto
        // ainda estão disponíveis.
        m_resourceManager.Clear();

        m_renderer.Shutdown();

        m_logger.Info(
            "[Engine] Shutting down..."
        );
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

        m_renderer.Clear(
            0.10f,
            0.15f,
            0.15f,
            1.0f
        );

        if (m_testShader &&
            m_testVertexArray)
        {
            m_testShader->Bind();

            m_testVertexArray->Bind();

            m_renderer.Draw(3);

            m_testVertexArray->Unbind();

            m_testShader->Unbind();
        }

        m_renderer.EndFrame();

        m_window.SwapBuffers();
    }

    Input& Engine::GetInput()
    {
        return m_input;
    }
}