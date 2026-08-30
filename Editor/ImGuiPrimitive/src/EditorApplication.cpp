#include "Primitive/Renderer/FrameBuffer.hpp"
#include "Primitive/ImGuiPrimitive/EditorApplication.hpp"

#include "Primitive/Core/Engine.hpp"

#include "Primitive/ImGuiPrimitive/ImGuiLayer.hpp"
#include "Primitive/ImGuiPrimitive/EditorLayer.hpp"

#include <memory>

namespace primitive
{
    EditorApplication::EditorApplication() : m_engine(std::make_unique<Engine>())
    {
        m_engine->PushLayer(std::make_unique<ImGuiLayer>());
        m_engine->PushLayer(std::make_unique<EditorLayer>());

        if(NFD_Init() != NFD_OKAY)
        {
            throw std::runtime_error("Failed to initialize native file dialog.");
        }
    }

    EditorApplication::~EditorApplication()
    {
        NFD_Quit();
    }

    void EditorApplication::Run()
    {
        m_engine->Run();
    }
}