#include "Primitive/Renderer/OpenGL/OpenGLRenderer.hpp"

#include <glad/gl.h>
#include <SDL3/SDL.h>

#include <stdexcept>
#include <iostream>

namespace primitive
{
    void OpenGLRenderer::Initialize()
    {
        if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress))
        {
            throw std::runtime_error(
                "Failed to initialize GLAD.");
        }

        std::cout
            << "[OpenGL] Vendor: "
            << reinterpret_cast<const char *>(glGetString(GL_VENDOR))
            << '\n';

        std::cout
            << "[OpenGL] Renderer: "
            << reinterpret_cast<const char *>(glGetString(GL_RENDERER))
            << '\n';

        std::cout
            << "[OpenGL] Version: "
            << reinterpret_cast<const char *>(glGetString(GL_VERSION))
            << '\n';
    }

    void OpenGLRenderer::Shutdown()
    {
    }

    void OpenGLRenderer::BeginFrame()
    {
    }

    void OpenGLRenderer::EndFrame()
    {
    }

    void OpenGLRenderer::Clear(
        float r,
        float g,
        float b,
        float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderer::SetDepthTest(bool enable)
    {
        if(enable)
        {
            glEnable(GL_DEPTH_TEST);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }
    }

    void OpenGLRenderer::Draw(std::uint32_t vertexCount)
    {
        glDrawArrays(
            GL_TRIANGLES,
            0,
            static_cast<GLsizei>(vertexCount)
        );
    }

    void OpenGLRenderer::DrawIndexed(std::uint32_t indexCount)
    {
        glDrawElements(
            GL_TRIANGLES,
            static_cast<GLsizei>(indexCount),
            GL_UNSIGNED_INT,
            nullptr
        );
    }
}