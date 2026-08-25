#pragma once

#include <cstdint>
#include <memory>
#include <functional>

#include "Primitive/Core/Time.hpp"
#include "Primitive/Core/Logger.hpp"
#include "Primitive/Core/EventBus.hpp"
#include "Primitive/Core/Configuration.hpp"
#include "Primitive/Core/Layer.hpp"
#include "Primitive/Core/LayerStack.hpp"

#include "Primitive/Platform/Window.hpp"
#include "Primitive/Platform/Platform.hpp"
#include "Primitive/Platform/Input.hpp"
#include "Primitive/Platform/SDLInput.hpp"

#include "Primitive/Resources/ResourceManager.hpp"

#include "Primitive/Renderer/Renderer.hpp"
#include "Primitive/Scene/Scene.hpp"

namespace primitive
{
    class Engine
    {
    public:
        using NativeEventCallback = std::function<void(const void *)>;
        using FrameCallback = std::function<void()>;

        Engine();
        ~Engine();

        void Run();
        void Stop();

        Input &GetInput();

        [[nodiscard]]
        Window &GetWindow();

        [[nodiscard]]
        const Window &GetWindow() const;

        [[nodiscard]]
        Scene *GetActiveScene();

        [[nodiscard]]
        const Scene *GetActiveScene() const;

        void SetNativeEventCallback(NativeEventCallback callback);
        void SetGuiBeginCallback(FrameCallback callback);
        void SetGuiRenderCallback(FrameCallback callback);
        void PushLayer(std::unique_ptr<Layer> layer);

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
        LayerStack m_layerStack;

        std::unique_ptr<Scene> m_activeScene;
    };
}