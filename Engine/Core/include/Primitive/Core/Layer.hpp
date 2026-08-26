#pragma once

namespace primitive
{
    class Engine;

    class Layer
    {
    public:
        virtual ~Layer() = default;

        virtual void OnAttach(Engine &)
        {
        }

        virtual void OnDetach()
        {
        }

        virtual void OnNativeEvent(const void *)
        {
        }

        virtual void OnUpdate(float)
        {
        }

        virtual void OnBeginFrame()
        {
        }

        virtual void OnRender()
        {
        }

        virtual void OnEndFrame()
        {
        }

        virtual void OnPreRender()
        {
        }
    };
}