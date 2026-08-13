#pragma once

#include "Primitive/Platform/Input.hpp"
#include "Primitive/Core/EventBus.hpp"

namespace primitive
{
    class SDLInput
    {
    public:
        explicit SDLInput(Input& input, EventBus& eventBus);
        ~SDLInput() = default;

        SDLInput(const SDLInput&) = delete;
        SDLInput& operator=(const SDLInput&) = delete;

        void PollEvents();

    private:
        Input& m_input;
        EventBus& m_eventBus;
    };
}