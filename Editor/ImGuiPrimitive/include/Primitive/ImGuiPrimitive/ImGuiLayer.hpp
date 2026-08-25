#pragma once

#include "Primitive/Core/Layer.hpp"

namespace primitive
{
    class Engine;
    class Window;

    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer() = default;
        ~ImGuiLayer() override = default;

        ImGuiLayer(const ImGuiLayer &) = delete;
        ImGuiLayer &operator=(const ImGuiLayer &) = delete;

        void OnAttach(Engine &engine) override;
        void OnDetach() override;
        void OnNativeEvent(const void *event) override;
        void OnUpdate(float deltaTime) override;
        void OnBeginFrame() override;
        void OnRender() override;
        void OnEndFrame() override;

    private:
        void BeginFrame();
        void EndFrame();
        Window *m_window{nullptr};
        bool m_initialized{false};
    };
}