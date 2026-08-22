#include "Primitive/Core/Engine.hpp"

#include "Primitive/Core/Events/WindowEvents.hpp"

#include "Primitive/Renderer/Shader.hpp"
#include "Primitive/Renderer/Texture.hpp"
#include "Primitive/Renderer/Camera.hpp"
#include "Primitive/Renderer/Material.hpp"
#include "Primitive/Renderer/Model.hpp"

#include "Primitive/Scene/Scene.hpp"
#include "Primitive/Scene/Components/TransformComponent.hpp"
#include "Primitive/Scene/Components/ModelRendererComponent.hpp"
#include "Primitive/Scene/Components/CameraComponent.hpp"

#include "Primitive/Resources/ModelLoader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

        m_logger.Info("[Engine] Starting main loop...");

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

        m_renderer.Initialize(
            m_configuration.renderer.backend,
            m_resourceManager);

        m_renderer.DepthTest(true);

        m_resourceManager.RegisterLoader<Model>(
            std::make_shared<ModelLoader>(
                m_renderer));

        // -----------------------------------------
        // Scene
        // -----------------------------------------

        m_activeScene = std::make_unique<Scene>();

        //------------------------------------------
        // Assets
        //------------------------------------------

        auto shader = m_resourceManager.Load<Shader>("Assets/Shaders/basic.glsl");

        if (!shader)
        {
            throw std::runtime_error(
                "Failed to load shader.");
        }

        auto texture = m_resourceManager.Load<Texture>("Assets/Textures/checker.png");

        if (!texture)
        {
            throw std::runtime_error(
                "Failed to load texture.");
        }

        auto model =m_resourceManager.Load<Model>("Assets/Models/cube.obj");

        if (!model)
        {
            throw std::runtime_error(
                "Failed to load model.");
        }

        auto material =
            std::make_shared<Material>(
                shader);

        material->SetBaseColor(
            glm::vec4{
                1.0f,
                1.0f,
                1.0f,
                1.0f});
        material->SetAlbedoTexture(texture);

        // -----------------------------------------
        // Camera Entity
        // -----------------------------------------

        auto cameraEntity = m_activeScene->CreateEntity();
        auto &cameraTransform = cameraEntity.AddComponent<TransformComponent>();

        cameraTransform.transform.SetPosition(
            glm::vec3{
                0.0f,
                0.0f,
                0.0f});

        const float aspectRatio =
            static_cast<float>(m_window.GetWidth()) /
            static_cast<float>(m_window.GetHeight());

        Camera camera;

        camera.SetProjection(
            glm::perspective(
                glm::radians(45.0f),
                aspectRatio,
                0.1f,
                100.0f));

        cameraEntity.AddComponent<CameraComponent>(std::move(camera), true);

        // -----------------------------------------
        // Cube Entity
        // -----------------------------------------
        auto cubeEntity = m_activeScene->CreateEntity();
        auto &transform = cubeEntity.AddComponent<TransformComponent>();

        transform.transform.SetPosition(glm::vec3{0.25f, 0.0f, -10.0f});
        cubeEntity.AddComponent<ModelRendererComponent>(model, material);

        m_logger.Info("[Engine] Scene initialized.");
        m_logger.Info("[Engine] Initialized.");
    }

    void Engine::Shutdown()
    {
        m_activeScene.reset();
        m_resourceManager.Clear();
        m_renderer.Shutdown();

        m_logger.Info("[Engine] Shutting down...");
    }

    void Engine::ProcessEvents()
    {
        m_sdlInput.PollEvents();
    }

    void Engine::Update(float deltaTime)
    {
        if (m_activeScene)
        {
            m_activeScene->Update(deltaTime);
        }
    }

    void Engine::Render()
    {
        m_renderer.BeginFrame();

        m_renderer.Clear(
            0.10f,
            0.15f,
            0.15f,
            1.0f);

        if (m_activeScene)
        {
            m_activeScene->Render(m_renderer);
        }

        m_renderer.EndFrame();

        m_window.SwapBuffers();
    }

    Input &Engine::GetInput()
    {
        return m_input;
    }
}