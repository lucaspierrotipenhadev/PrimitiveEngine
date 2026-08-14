#include "Primitive/Core/Engine.hpp"

#include "Primitive/Core/Events/WindowEvents.hpp"

#include "Primitive/Renderer/Shader.hpp"
#include "Primitive/Renderer/VertexBuffer.hpp"
#include "Primitive/Renderer/VertexArray.hpp"
#include "Primitive/Renderer/VertexBufferLayout.hpp"
#include "Primitive/Renderer/IndexBuffer.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>

namespace primitive
{
    Engine::Engine()
        : m_configuration(),
          m_platform(),
          m_input(),
          m_sdlInput(
              m_input,
              m_eventBus),
          m_window(
              m_configuration.window),
          m_renderer(),
          m_resourceManager()
    {
        m_logger.Info(
            "Engine constructed.");
    }

    Engine::~Engine()
    {
        m_logger.Info(
            "[Engine] Destroying engine...");
    }

    void Engine::Run()
    {
        Initialize();

        m_running = true;

        m_logger.Info(
            "[Engine] Starting main loop...");

        while (m_running)
        {
            m_time.BeginFrame();

            m_input.BeginFrame();

            ProcessEvents();

            Update(
                m_time.GetDeltaTime());

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
            WindowClosedEvent>(
            [this](
                const WindowClosedEvent &)
            {
                Stop();
            });

        // Renderer escolhe e inicializa
        // o backend através da factory.
        m_renderer.Initialize(
            m_configuration.renderer.backend,
            m_resourceManager);

        m_renderer.DepthTest(true);

        // Engine conhece somente Shader.
        m_testShader =
            m_resourceManager.Load<Shader>(
                "Assets/Shaders/basic.glsl");

        if (!m_testShader)
        {
            throw std::runtime_error(
                "Failed to load shader.");
        }

        const float vertices[] =
            {
                // Frente
                -0.5f, -0.5f, -0.5f, // 0
                0.5f, -0.5f, -0.5f,  // 1
                0.5f, 0.5f, -0.5f,   // 2
                -0.5f, 0.5f, -0.5f,  // 3

                // Trás
                -0.5f, -0.5f, 0.5f, // 4
                0.5f, -0.5f, 0.5f,  // 5
                0.5f, 0.5f, 0.5f,   // 6
                -0.5f, 0.5f, 0.5f   // 7
            };

        const std::uint32_t indices[] =
            {
                // Frente
                0, 1, 2,
                2, 3, 0,

                // Direita
                1, 5, 6,
                6, 2, 1,

                // Trás
                5, 4, 7,
                7, 6, 5,

                // Esquerda
                4, 0, 3,
                3, 7, 4,

                // Topo
                3, 2, 6,
                6, 7, 3,

                // Fundo
                4, 5, 1,
                1, 0, 4};

        VertexBufferLayout layout;

        layout.Push(
            ShaderDataType::Float3);

        m_testMesh =
            m_renderer.CreateMesh(
                vertices,
                sizeof(vertices),
                layout,
                indices,
                36);

        const float aspectRatio =
            static_cast<float>(m_window.GetWidth()) /
            static_cast<float>(m_window.GetHeight());

        m_testCamera.SetProjection(
            glm::perspective(
                glm::radians(45.0f),
                aspectRatio,
                0.1f,
                100.0f));

        m_testCamera
            .GetTransform()
            .SetPosition(
                glm::vec3{
                    0.25f,
                    0.0f,
                    0.0f});

        m_testTransform.SetPosition(
            glm::vec3(
                0.25f,
                0.0f,
                -10.0f));

        m_testTransform.SetRotation(
            glm::vec3(
                0.0f,
                0.0f,
                30.0f));

        m_testTransform.SetScale(
            glm::vec3(
                0.75f,
                0.75f,
                1.0f));

        m_logger.Info(
            "[Engine] Triangle pipeline initialized.");

        m_logger.Info(
            "[Engine] Initialized.");
    }

    void Engine::Shutdown()
    {
        m_testShader.reset();
        m_testMesh.reset();

        // Libera recursos gráficos
        // enquanto o backend/contexto
        // ainda estão disponíveis.
        m_resourceManager.Clear();

        m_renderer.Shutdown();

        m_logger.Info(
            "[Engine] Shutting down...");
    }

    void Engine::ProcessEvents()
    {
        m_sdlInput.PollEvents();
    }

    void Engine::Update(float deltaTime)
    {
        (void)deltaTime;
        m_testTransform.Rotate(
            glm::vec3{
                25.0f * deltaTime,
                40.0f * deltaTime,
                15.0f * deltaTime});
    }

    void Engine::Render()
    {
        m_renderer.BeginFrame();

        m_renderer.Clear(
            0.10f,
            0.15f,
            0.15f,
            1.0f);

        if (m_testShader)
        {
            m_testShader->Bind();

            const glm::mat4 model =
                m_testTransform.GetMatrix();

            m_testShader->SetMat4(
                "u_View",
                glm::value_ptr(
                    m_testCamera.GetView()));

            m_testShader->SetMat4(
                "u_Projection",
                glm::value_ptr(
                    m_testCamera.GetProjection()));

            m_testShader->SetMat4(
                "u_Model",
                glm::value_ptr(model));

            m_testShader->SetFloat4("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);

            m_testMesh->Bind();

            m_renderer.DrawIndexed(
                m_testMesh->GetIndexBuffer());

            m_testMesh->Unbind();

            m_testShader->Unbind();
        }

        m_renderer.EndFrame();

        m_window.SwapBuffers();
    }

    Input &Engine::GetInput()
    {
        return m_input;
    }
}