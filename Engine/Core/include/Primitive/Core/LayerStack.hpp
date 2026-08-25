#pragma once

#include "Primitive/Core/Layer.hpp"

#include <memory>
#include <vector>

namespace primitive
{
    class Engine;
    class Layer;

    class LayerStack
    {
    public:
        LayerStack() = default;
        ~LayerStack();

        LayerStack(const LayerStack &) = delete;
        LayerStack &operator=(const LayerStack &) = delete;

        void PushLayer(std::unique_ptr<Layer> layer);
        void OnAttach(Engine &engine);
        void OnDetach();

        void OnNativeEvent(const void *event);
        void OnUpdate(float deltaTime);
        void OnBeginFrame();
        void OnRender();
        void OnEndFrame();
        void Clear();

    private:
        std::vector<std::unique_ptr<Layer>> m_layers;
        bool m_attached{false};
    };
}