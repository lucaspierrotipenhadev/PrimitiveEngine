#pragma once

#include <cstdint>

namespace primitive
{
    class SDLInput;

    enum class Key : std::uint16_t
    {
        Unknown = 0,

        A, B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

        Num0, Num1, Num2, Num3, Num4,
        Num5, Num6, Num7, Num8, Num9,

        Escape,
        Enter,
        Tab,
        Backspace,
        Space,

        Left,
        Right,
        Up,
        Down,

        LeftShift,
        RightShift,
        LeftCtrl,
        RightCtrl,

        LeftAlt,
        RightAlt
    };

    enum class MouseButton : std::uint8_t
    {
        Left = 0,
        Middle,
        Right,
        X1,
        X2
    };

    class Input
    {
    public:
        Input() = default;
        ~Input() = default;

        Input(const Input&) = delete;
        Input& operator=(const Input&) = delete;

        void BeginFrame();

        bool IsKeyDown(Key key) const;
        bool IsKeyPressed(Key key) const;
        bool IsKeyReleased(Key key) const;

        bool IsMouseButtonDown(MouseButton button) const;
        bool IsMouseButtonPressed(MouseButton button) const;
        bool IsMouseButtonReleased(MouseButton button) const;

        float GetMouseX() const;
        float GetMouseY() const;

        float GetMouseDeltaX() const;
        float GetMouseDeltaY() const;

    private:
        friend class SDLInput;

        void ProcessKeyDown(Key key);
        void ProcessKeyUp(Key key);

        void ProcessMouseButtonDown(MouseButton button);
        void ProcessMouseButtonUp(MouseButton button);

        void ProcessMouseMove(
            float x,
            float y,
            float deltaX,
            float deltaY
        );

        bool m_keys[256]{};
        bool m_keysPressed[256]{};
        bool m_keysReleased[256]{};

        bool m_mouseButtons[5]{};
        bool m_mouseButtonsPressed[5]{};
        bool m_mouseButtonsReleased[5]{};

        float m_mouseX{0.0f};
        float m_mouseY{0.0f};

        float m_mouseDeltaX{0.0f};
        float m_mouseDeltaY{0.0f};
    };
}