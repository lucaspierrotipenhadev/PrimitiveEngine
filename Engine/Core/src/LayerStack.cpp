#include "Primitive/Core/LayerStack.hpp"

#include "Primitive/Core/Layer.hpp"

namespace primitive
{
    LayerStack::~LayerStack()
    {
        OnDetach();
    }

    void LayerStack::PushLayer(std::unique_ptr<Layer> layer)
    {
        if (!layer)
        {
            return;
        }

        m_layers.push_back(std::move(layer));
    }

    void LayerStack::OnAttach(Engine &engine)
    {
        if (m_attached)
        {
            return;
        }

        for (auto &layer : m_layers)
        {
            layer->OnAttach(engine);
        }

        m_attached = true;
    }

    void LayerStack::OnDetach()
    {
        if (!m_attached)
        {
            return;
        }

        // Ordem inversa é mais segura para teardown.
        for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it)
        {
            (*it)->OnDetach();
        }

        m_attached = false;
    }

    void LayerStack::OnNativeEvent(const void *event)
    {
        for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it)
        {
            (*it)->OnNativeEvent(event);
        }
    }

    void LayerStack::OnUpdate(float deltaTime)
    {
        for (auto &layer : m_layers)
        {
            layer->OnUpdate(deltaTime);
        }
    }

    void LayerStack::OnBeginFrame()
    {
        for(auto& layer : m_layers)
        {
            layer->OnBeginFrame();
        }
    }

    void LayerStack::OnRender()
    {
        for (auto &layer : m_layers)
        {
            layer->OnRender();
        }
    }

    void LayerStack::OnEndFrame()
    {
        for(auto it = m_layers.rbegin(); it != m_layers.rend();  it++)
        {
            (*it)->OnEndFrame();
        }
    }

    void LayerStack::Clear()
    {
        OnDetach();
        m_layers.clear();
    }
}