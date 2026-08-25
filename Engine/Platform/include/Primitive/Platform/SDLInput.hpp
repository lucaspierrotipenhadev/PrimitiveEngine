#pragma once

#include "Primitive/Platform/Input.hpp"

#include <functional>

#include "Primitive/Core/EventBus.hpp"

namespace primitive
{
    class SDLInput
    {
    public:
        using NativeEventCallback = std::function<void(const void*)>;
        explicit SDLInput(Input& input, EventBus& eventBus);
        ~SDLInput() = default;

        SDLInput(const SDLInput&) = delete;
        SDLInput& operator=(const SDLInput&) = delete;

        void PollEvents();

        void SetNativeEventCallback(NativeEventCallback callback);

    private:
        Input& m_input;
        EventBus& m_eventBus;
        NativeEventCallback m_nativeEventCallback;
    };
}