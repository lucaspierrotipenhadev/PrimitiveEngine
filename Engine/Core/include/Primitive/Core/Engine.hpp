#pragma once

#include <cstdint>
#include <memory>

#include "Primitive/Core/Time.hpp"
#include "Primitive/Core/Logger.hpp"
#include "Primitive/Core/EventBus.hpp"
#include "Primitive/Core/Configuration.hpp"

#include "Primitive/Platform/Window.hpp"
#include "Primitive/Platform/Platform.hpp"
#include "Primitive/Platform/Input.hpp"
#include "Primitive/Platform/SDLInput.hpp"

#include "Primitive/Resources/ResourceManager.hpp"

#include "Primitive/Renderer/Renderer.hpp"
#include "Primitive/Renderer/Texture.hpp"
#include "Primitive/Renderer/Shader.hpp"
#include "Primitive/Renderer/Camera.hpp"
#include "Primitive/Renderer/Mesh.hpp"
#include "Primitive/Renderer/Model.hpp"
#include "Primitive/Renderer/Material.hpp"
#include "Primitive/Renderer/VertexBuffer.hpp"
#include "Primitive/Renderer/VertexArray.hpp"
#include "Primitive/Renderer/IndexBuffer.hpp"

#include "Primitive/Scene/Transform.hpp"

namespace primitive
{
    class Engine
    {
    public:
        Engine();
        ~Engine();

        void Run();
        void Stop();

        Input &GetInput();

    private:
        void Initialize();
        void Shutdown();

        void ProcessEvents();
        void Update(float deltaTime);
        void Render();

    private:
        bool m_running{false};

        Configuration m_configuration;
        Platform m_platform;
        Logger m_logger;
        Time m_time;
        EventBus m_eventBus;
        Input m_input;
        SDLInput m_sdlInput;
        Window m_window;
        Renderer m_renderer;
        Camera m_testCamera;

        Transform m_testTransform;

        std::shared_ptr<Shader>
            m_testShader;

        std::shared_ptr<Texture>
            m_testTexture;

        std::unique_ptr<Material>
            m_testMaterial;

        std::shared_ptr<Model>
            m_testModel;

        ResourceManager m_resourceManager;
    };
}