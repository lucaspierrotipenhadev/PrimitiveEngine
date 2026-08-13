#include "Primitive/Platform/Input.hpp"

namespace primitive
{
    void Input::BeginFrame()
    {
        for (int i = 0; i < 256; ++i)
        {
            m_keysPressed[i] = false;
            m_keysReleased[i] = false;
        }

        for (int i = 0; i < 5; ++i)
        {
            m_mouseButtonsPressed[i] = false;
            m_mouseButtonsReleased[i] = false;
        }

        m_mouseDeltaX = 0.0f;
        m_mouseDeltaY = 0.0f;
    }

    bool Input::IsKeyDown(Key key) const
    {
        return m_keys[
            static_cast<std::uint16_t>(key)
        ];
    }

    bool Input::IsKeyPressed(Key key) const
    {
        return m_keysPressed[
            static_cast<std::uint16_t>(key)
        ];
    }

    bool Input::IsKeyReleased(Key key) const
    {
        return m_keysReleased[
            static_cast<std::uint16_t>(key)
        ];
    }

    bool Input::IsMouseButtonDown(MouseButton button) const
    {
        return m_mouseButtons[
            static_cast<std::uint8_t>(button)
        ];
    }

    bool Input::IsMouseButtonPressed(MouseButton button) const
    {
        return m_mouseButtonsPressed[
            static_cast<std::uint8_t>(button)
        ];
    }

    bool Input::IsMouseButtonReleased(MouseButton button) const
    {
        return m_mouseButtonsReleased[
            static_cast<std::uint8_t>(button)
        ];
    }

    float Input::GetMouseX() const
    {
        return m_mouseX;
    }

    float Input::GetMouseY() const
    {
        return m_mouseY;
    }

    float Input::GetMouseDeltaX() const
    {
        return m_mouseDeltaX;
    }

    float Input::GetMouseDeltaY() const
    {
        return m_mouseDeltaY;
    }

    void Input::ProcessKeyDown(Key key)
    {
        const auto index =
            static_cast<std::uint16_t>(key);

        if (!m_keys[index])
        {
            m_keysPressed[index] = true;
        }

        m_keys[index] = true;
    }

    void Input::ProcessKeyUp(Key key)
    {
        const auto index =
            static_cast<std::uint16_t>(key);

        m_keys[index] = false;
        m_keysReleased[index] = true;
    }

    void Input::ProcessMouseButtonDown(MouseButton button)
    {
        const auto index =
            static_cast<std::uint8_t>(button);

        if (!m_mouseButtons[index])
        {
            m_mouseButtonsPressed[index] = true;
        }

        m_mouseButtons[index] = true;
    }

    void Input::ProcessMouseButtonUp(MouseButton button)
    {
        const auto index =
            static_cast<std::uint8_t>(button);

        m_mouseButtons[index] = false;
        m_mouseButtonsReleased[index] = true;
    }

    void Input::ProcessMouseMove(
        float x,
        float y,
        float deltaX,
        float deltaY)
    {
        m_mouseX = x;
        m_mouseY = y;

        m_mouseDeltaX += deltaX;
        m_mouseDeltaY += deltaY;
    }
}