#include "Primitive/Platform/Window.hpp"

#include <SDL3/SDL.h>

#include <stdexcept>

namespace primitive
{
    struct Window::WindowData
    {
        SDL_Window *handle{nullptr};
        SDL_GLContext context{nullptr};

        int width{0};
        int height{0};

        bool shouldClose{false};
    };

    Window::Window(const WindowConfiguration &config)
        : m_data(new WindowData{})
    {
        m_data->width = config.width;
        m_data->height = config.height;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        SDL_WindowFlags flags = SDL_WINDOW_OPENGL;

        if (config.fullscreen)
        {
            flags |= SDL_WINDOW_FULLSCREEN;
        }

        m_data->handle = SDL_CreateWindow(
            config.title.c_str(),
            static_cast<int>(config.width),
            static_cast<int>(config.height),
            flags);

        if (!m_data->handle)
        {
            delete m_data;
            m_data = nullptr;

            throw std::runtime_error(SDL_GetError());
        }

        m_data->context = SDL_GL_CreateContext(m_data->handle);

        if (!m_data->context)
        {
            SDL_DestroyWindow(m_data->handle);

            delete m_data;
            m_data = nullptr;

            throw std::runtime_error(SDL_GetError());
        }
    }

    Window::~Window()
    {
        if (m_data)
        {
            if (m_data->context)
            {
                SDL_GL_DestroyContext(m_data->context);
            }

            if (m_data->handle)
            {
                SDL_DestroyWindow(m_data->handle);
            }

            delete m_data;
        }
    }

    void Window::SwapBuffers()
    {
        if (m_data && m_data->handle)
        {
            SDL_GL_SwapWindow(m_data->handle);
        }
    }

    bool Window::ShouldClose() const
    {
        return m_data->shouldClose;
    }

    int Window::GetWidth() const
    {
        return m_data->width;
    }

    int Window::GetHeight() const
    {
        return m_data->height;
    }
}