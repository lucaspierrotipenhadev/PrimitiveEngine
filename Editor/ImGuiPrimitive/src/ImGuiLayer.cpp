#include "Primitive/ImGuiPrimitive/ImGuiLayer.hpp"

#include "Primitive/Platform/Window.hpp"

#include "Primitive/Core/Engine.hpp"

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>
#include <ImGuizmo.h>

#include <SDL3/SDL.h>

#include <stdexcept>

namespace primitive
{
    void ImGuiLayer::OnAttach(Engine &engine)
    {
        if (m_initialized)
        {
            return;
        }
        m_window = &engine.GetWindow();

        IMGUI_CHECKVERSION();

        ImGui::CreateContext();

        ImGuiIO &io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui::StyleColorsDark();

        auto *nativeWindow = static_cast<SDL_Window *>(m_window->GetNativeHandle());
        auto graphicsContext = static_cast<SDL_GLContext>(m_window->GetGraphicsContext());

        if (!nativeWindow || !graphicsContext)
        {
            throw std::runtime_error(
                "Invalid native window or OpenGL context.");
        }

        if (!ImGui_ImplSDL3_InitForOpenGL(nativeWindow, graphicsContext))
        {
            throw std::runtime_error(
                "Failed to initialize ImGui SDL3 backend.");
        }

        if (!ImGui_ImplOpenGL3_Init("#version 460 core"))
        {
            throw std::runtime_error("Failed to initialize ImGui OpenGL backend.");
        }

        m_initialized = true;
    }

    void ImGuiLayer::OnDetach()
    {
        if (!m_initialized)
        {
            return;
        }

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL3_Shutdown();

        ImGui::DestroyContext();

        m_window = nullptr;
        m_initialized = false;
    }

    void ImGuiLayer::OnNativeEvent(const void *event)
    {
        if (!m_initialized || event == nullptr)
        {
            return;
        }

        const auto *sdlEvent = static_cast<const SDL_Event *>(event);
        ImGui_ImplSDL3_ProcessEvent(sdlEvent);
    }

    void ImGuiLayer::OnUpdate(float deltaTime)
    {
        (void)deltaTime;
    }

    void ImGuiLayer::OnBeginFrame()
    {
        if(!m_initialized){ return;}

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();

        ImGui::NewFrame();
        ImGuizmo::BeginFrame();
    }

    void ImGuiLayer::OnRender()
    {
    }

    void ImGuiLayer::OnEndFrame()
    {

        if (!m_initialized)
        {
            return;
        }

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}