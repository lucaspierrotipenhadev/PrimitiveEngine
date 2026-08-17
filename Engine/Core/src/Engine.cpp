#include "Primitive/Core/Engine.hpp"

#include "Primitive/Core/Events/WindowEvents.hpp"

#include "Primitive/Renderer/Shader.hpp"
#include "Primitive/Renderer/Texture.hpp"
#include "Primitive/Renderer/VertexBuffer.hpp"
#include "Primitive/Renderer/VertexArray.hpp"
#include "Primitive/Renderer/VertexBufferLayout.hpp"
#include "Primitive/Renderer/IndexBuffer.hpp"

#include "Primitive/Renderer/Model.hpp"
#include "Primitive/Resources/ModelLoader.hpp"
#include "Primitive/Renderer/Material.hpp"

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

        m_testTexture =
            m_resourceManager.Load<Texture>(
                "Assets/Textures/checker.png");

        if (!m_testTexture)
        {
            throw std::runtime_error(
                "Failed to load texture.");
        }

        m_resourceManager.RegisterLoader<Model>(
            std::make_shared<ModelLoader>(
                m_renderer));

        m_testModel =
            m_resourceManager.Load<Model>(
                "Assets/Models/cube.obj");

        m_testMaterial =
            std::make_unique<Material>(
                m_testShader);

        m_testMaterial->SetBaseColor(
            glm::vec4{
                1.0f,
                1.0f,
                1.0f,
                1.0f});

        m_testMaterial->SetAlbedoTexture(
            m_testTexture);

        if (!m_testShader)
        {
            throw std::runtime_error(
                "Failed to load shader.");
        }

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
        m_testModel.reset();
        m_testMaterial.reset();

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

            m_testShader->SetFloat3("u_LightDirection", -1.0f, -1.0f, -1.0f);
            m_testShader->SetFloat3("u_LightColor", 1.0f, 1.0f, 1.0f);

            m_renderer.DrawModel(*m_testModel, *m_testMaterial);

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