#include "Primitive/Renderer/Renderer.hpp"

#include "Primitive/Renderer/OpenGL/OpenGLRenderer.hpp"

namespace primitive
{
    void Renderer::Initialize()
    {
        if(!m_api)
        {
            m_api = std::make_unique<OpenGLRenderer>();
        }
        m_api->Initialize();
    }

    void Renderer::Shutdown()
    {
        if(m_api)
        {
            m_api->Shutdown();
            m_api.reset();
        }
    }

    void Renderer::BeginFrame()
    {
        if(m_api)
        {
            m_api->BeginFrame();
        }
    }

    void Renderer::EndFrame()
    {
        if(m_api)
        {
            m_api->EndFrame();
        }
    }

    void Renderer::Clear(float r, float g, float b, float a)
    {
        if(m_api)
        {
            m_api->Clear(r, g, b, a);
        }
    }
}