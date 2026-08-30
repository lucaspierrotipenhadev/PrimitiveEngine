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
#include "Primitive/Scene/Components/RigidBodyComponent.hpp"
#include "Primitive/Scene/Components/BoxColliderComponent.hpp"

#include "Primitive/Resources/ModelLoader.hpp"

#include "Primitive/Physics/PhysicsEvents.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdexcept>
#include <utility>

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
        m_logger.Info("[Engine] Destroying engine...");
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

        m_renderer.Initialize(m_configuration.renderer.backend, m_resourceManager);
        m_renderer.DepthTest(true);

        m_resourceManager.RegisterLoader<Model>(std::make_shared<ModelLoader>(m_renderer));

        // Scene
        m_activeScene = std::make_unique<Scene>();
        m_activeScene->SetFixedTimeStep(m_configuration.physics.fixedTimeStep);

        m_logger.Info("[Engine] Scene initialized.");
        m_logger.Info("[Engine] Initialized.");

        m_eventBus.Subscribe<CollisionEnterEvent>(
            [this](const CollisionEnterEvent &)
            {
                m_logger.Info("[Physics] Collision Enter.");
            });

        m_layerStack.OnAttach(*this);
        m_sdlInput.SetNativeEventCallback(
            [this](const void *event)
            {
                m_layerStack.OnNativeEvent(
                    event);
            });
    }

    void Engine::Shutdown()
    {
        m_sdlInput.SetNativeEventCallback({});
        m_layerStack.Clear();

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
        if (m_activeScene && m_updateActiveScene)
        {
            m_activeScene->Update(deltaTime, m_eventBus);
        }

        m_layerStack.OnUpdate(deltaTime);
    }

    void Engine::Render()
    {
        m_renderer.BeginFrame();

        m_renderer.Clear(0.10f, 0.15f, 0.15f, 1.0f);

        if (m_activeScene && m_renderActiveScene && m_updateActiveScene)
        {
            m_activeScene->Render(m_renderer);
        }

        m_layerStack.OnBeginFrame();
        m_layerStack.OnRender();
        m_layerStack.OnEndFrame();

        m_renderer.EndFrame();

        m_window.SwapBuffers();
    }

    Input &Engine::GetInput()
    {
        return m_input;
    }

    Window &Engine::GetWindow()
    {
        return m_window;
    }

    const Window &Engine::GetWindow() const
    {
        return m_window;
    }

    void Engine::PushLayer(std::unique_ptr<Layer> layer)
    {
        m_layerStack.PushLayer(std::move(layer));
    }

    Scene *Engine::GetActiveScene()
    {
        return m_activeScene.get();
    }

    const Scene * Engine::GetActiveScene() const
    {
        return m_activeScene.get();
    }

    ResourceManager& Engine::GetResourceManager()
    {
        return m_resourceManager;
    }

    const ResourceManager& Engine::GetResourceManager() const
    {
        return m_resourceManager;
    }

    Renderer &Engine::GetRenderer()
    {
        return m_renderer;
    }

    const Renderer &Engine::GetRenderer() const
    {
        return m_renderer;
    }

    void Engine::SetRenderActiveScene(bool enabled)
    {
        m_renderActiveScene = enabled;
    }

    bool Engine::GetRenderActiveScene() const
    {
        return m_renderActiveScene;
    }

    void Engine::SetUpdateActiveScene(bool enabled)
    {
        m_updateActiveScene = enabled;
    }

    bool Engine::GetUpdateActiveScene() const
    {
        return m_updateActiveScene;
    }

    EventBus &Engine::GetEventBus()
    {
        return m_eventBus;
    }

    const EventBus& Engine::GetEventBus() const
    {
        return m_eventBus;
    }
}