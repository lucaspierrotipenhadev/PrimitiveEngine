#include "Primitive/Platform/SDLInput.hpp"

#include "Primitive/Core/Events/WindowEvents.hpp"

#include <SDL3/SDL.h>

namespace primitive
{
    namespace
    {
        Key TranslateKey(SDL_Scancode scancode)
        {
            switch (scancode)
            {
            case SDL_SCANCODE_A: return Key::A;
            case SDL_SCANCODE_B: return Key::B;
            case SDL_SCANCODE_C: return Key::C;
            case SDL_SCANCODE_D: return Key::D;
            case SDL_SCANCODE_E: return Key::E;
            case SDL_SCANCODE_F: return Key::F;
            case SDL_SCANCODE_G: return Key::G;
            case SDL_SCANCODE_H: return Key::H;
            case SDL_SCANCODE_I: return Key::I;
            case SDL_SCANCODE_J: return Key::J;
            case SDL_SCANCODE_K: return Key::K;
            case SDL_SCANCODE_L: return Key::L;
            case SDL_SCANCODE_M: return Key::M;
            case SDL_SCANCODE_N: return Key::N;
            case SDL_SCANCODE_O: return Key::O;
            case SDL_SCANCODE_P: return Key::P;
            case SDL_SCANCODE_Q: return Key::Q;
            case SDL_SCANCODE_R: return Key::R;
            case SDL_SCANCODE_S: return Key::S;
            case SDL_SCANCODE_T: return Key::T;
            case SDL_SCANCODE_U: return Key::U;
            case SDL_SCANCODE_V: return Key::V;
            case SDL_SCANCODE_W: return Key::W;
            case SDL_SCANCODE_X: return Key::X;
            case SDL_SCANCODE_Y: return Key::Y;
            case SDL_SCANCODE_Z: return Key::Z;

            case SDL_SCANCODE_0: return Key::Num0;
            case SDL_SCANCODE_1: return Key::Num1;
            case SDL_SCANCODE_2: return Key::Num2;
            case SDL_SCANCODE_3: return Key::Num3;
            case SDL_SCANCODE_4: return Key::Num4;
            case SDL_SCANCODE_5: return Key::Num5;
            case SDL_SCANCODE_6: return Key::Num6;
            case SDL_SCANCODE_7: return Key::Num7;
            case SDL_SCANCODE_8: return Key::Num8;
            case SDL_SCANCODE_9: return Key::Num9;

            case SDL_SCANCODE_ESCAPE:
                return Key::Escape;

            case SDL_SCANCODE_RETURN:
                return Key::Enter;

            case SDL_SCANCODE_TAB:
                return Key::Tab;

            case SDL_SCANCODE_BACKSPACE:
                return Key::Backspace;

            case SDL_SCANCODE_SPACE:
                return Key::Space;

            case SDL_SCANCODE_LEFT:
                return Key::Left;

            case SDL_SCANCODE_RIGHT:
                return Key::Right;

            case SDL_SCANCODE_UP:
                return Key::Up;

            case SDL_SCANCODE_DOWN:
                return Key::Down;

            case SDL_SCANCODE_LSHIFT:
                return Key::LeftShift;

            case SDL_SCANCODE_RSHIFT:
                return Key::RightShift;

            case SDL_SCANCODE_LCTRL:
                return Key::LeftCtrl;

            case SDL_SCANCODE_RCTRL:
                return Key::RightCtrl;

            case SDL_SCANCODE_LALT:
                return Key::LeftAlt;

            case SDL_SCANCODE_RALT:
                return Key::RightAlt;

            default:
                return Key::Unknown;
            }
        }

        MouseButton TranslateMouseButton(Uint8 button)
        {
            switch (button)
            {
            case SDL_BUTTON_LEFT:
                return MouseButton::Left;

            case SDL_BUTTON_MIDDLE:
                return MouseButton::Middle;

            case SDL_BUTTON_RIGHT:
                return MouseButton::Right;

            case SDL_BUTTON_X1:
                return MouseButton::X1;

            case SDL_BUTTON_X2:
                return MouseButton::X2;

            default:
                return MouseButton::Left;
            }
        }
    }

    SDLInput::SDLInput(Input& input, EventBus& eventBus)
        : m_input(input), 
          m_eventBus(eventBus)
    {
    }

    void SDLInput::PollEvents()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if(m_nativeEventCallback)
            {
                m_nativeEventCallback(&event);
            }

            switch (event.type)
            {
            case SDL_EVENT_QUIT:
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                m_eventBus.Publish(WindowClosedEvent());
                break;

            case SDL_EVENT_KEY_DOWN:
            {
                const Key key =
                    TranslateKey(event.key.scancode);

                if (key != Key::Unknown)
                {
                    m_input.ProcessKeyDown(key);
                }

                break;
            }

            case SDL_EVENT_KEY_UP:
            {
                const Key key =
                    TranslateKey(event.key.scancode);

                if (key != Key::Unknown)
                {
                    m_input.ProcessKeyUp(key);
                }

                break;
            }

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
            {
                const MouseButton button =
                    TranslateMouseButton(event.button.button);

                m_input.ProcessMouseButtonDown(button);

                break;
            }

            case SDL_EVENT_MOUSE_BUTTON_UP:
            {
                const MouseButton button =
                    TranslateMouseButton(event.button.button);

                m_input.ProcessMouseButtonUp(button);

                break;
            }

            case SDL_EVENT_MOUSE_MOTION:
            {
                m_input.ProcessMouseMove(
                    event.motion.x,
                    event.motion.y,
                    event.motion.xrel,
                    event.motion.yrel
                );

                break;
            }

            default:
                break;
            }
        }
    }

    void SDLInput::SetNativeEventCallback(NativeEventCallback callback)
    {
        m_nativeEventCallback = std::move(callback);
    }
}