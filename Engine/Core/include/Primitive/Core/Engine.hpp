#pragma once

#include <cstdint>

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

namespace primitive
{
    class Engine
    {
    public:
        Engine();
        ~Engine();

        void Run();
        void Stop();

        Input& GetInput();

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
        ResourceManager m_resourceManager;
    };
}