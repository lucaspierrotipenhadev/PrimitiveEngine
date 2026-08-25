#pragma once

#include "Primitive/Core/Configuration.hpp"
#include "Primitive/Platform/Input.hpp"

namespace primitive
{
    class Window
    {
    public:
        explicit Window(const WindowConfiguration& config);
        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        void SwapBuffers();

        bool ShouldClose() const;

        int GetWidth() const;
        int GetHeight() const;

        [[nodiscard]]
        void* GetNativeHandle() const;

        [[nodiscard]]
        void* GetGraphicsContext() const;

    private:
        struct WindowData;

        WindowData* m_data{nullptr};
    };
}