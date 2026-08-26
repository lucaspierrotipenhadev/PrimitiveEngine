#include "Primitive/Renderer/FrameBuffer.hpp"
#include "Primitive/ImGuiPrimitive/EditorLayer.hpp"

#include "Primitive/Core/Engine.hpp"

#include "Primitive/Renderer/OpenGL/OpenGLFrameBuffer.hpp"

#include "Primitive/Scene/Components/CameraComponent.hpp"

#include <cstdint>

#include <imgui.h>

namespace primitive
{
    void EditorLayer::OnAttach(
        Engine &engine)
    {
        m_engine = &engine;
        m_engine->SetRenderActiveScene(false);
        m_hierarchyPanel.SetScene(engine.GetActiveScene());
        m_hierarchyPanel.SetSelectionContext(&m_selectedEntity);
        m_inspectorPanel.SetSelectionContext(&m_selectedEntity);

        FramebufferSpecification specification;

        specification.width = 1280;
        specification.height = 720;

        m_sceneFramebuffer = m_engine->GetRenderer().CreateFramebuffer(specification);
    }

    void EditorLayer::OnDetach()
    {
        if (m_engine)
        {
            m_engine->SetRenderActiveScene(true);
        }

        m_inspectorPanel.SetSelectionContext(nullptr);
        m_hierarchyPanel.SetSelectionContext(nullptr);
        m_hierarchyPanel.SetScene(nullptr);
        m_engine = nullptr;
    }

    void EditorLayer::OnUpdate(
        float deltaTime)
    {
        (void)deltaTime;

        if (!m_engine ||
            !m_sceneFramebuffer)
        {
            return;
        }

        const glm::vec2 viewportSize =
            m_viewportPanel.GetSize();

        if (viewportSize.x > 0.0f &&
            viewportSize.y > 0.0f)
        {
            const auto width =
                static_cast<std::uint32_t>(
                    viewportSize.x);

            const auto height =
                static_cast<std::uint32_t>(
                    viewportSize.y);

            const auto &specification =
                m_sceneFramebuffer
                    ->GetSpecification();

            if (specification.width != width ||
                specification.height != height)
            {
                m_sceneFramebuffer->Resize(
                    width,
                    height);

                const float aspectRatio =
                    static_cast<float>(width) /
                    static_cast<float>(height);

                if (auto *scene =
                        m_engine->GetActiveScene())
                {
                    scene->ForEach<
                        CameraComponent>(
                        [aspectRatio](
                            EntityID,
                            CameraComponent &camera)
                        {
                            camera.UppdateProjection(
                                aspectRatio);
                        });
                }

                m_inspectorPanel
                    .SetAspectRatio(
                        aspectRatio);
            }
        }

        m_sceneFramebuffer->Bind();

        m_engine
            ->GetRenderer()
            .SetViewport(
                0,
                0,
                static_cast<std::uint32_t>(
                    m_engine
                        ->GetWindow()
                        .GetWidth()),
                static_cast<std::uint32_t>(
                    m_engine
                        ->GetWindow()
                        .GetHeight()));

        auto &renderer =
            m_engine->GetRenderer();

        renderer.Clear(
            0.1f,
            0.1f,
            0.1f,
            1.0f);

        if (auto *scene =
                m_engine->GetActiveScene())
        {
            scene->Render(
                renderer);
        }

        m_sceneFramebuffer->Unbind();
    }

    void EditorLayer::OnRender()
    {
        constexpr ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
        ImGuiViewport *viewport = ImGui::GetMainViewport();
        const ImGuiID dockspaceID = ImGui::GetID("PrimitiveEditorDockspace");

        ImGui::DockSpaceOverViewport(dockspaceID, viewport, dockspaceFlags);

        m_hierarchyPanel.OnRender();
        m_inspectorPanel.OnRender();

        if (m_selectedEntity)
        {
            ImGui::Begin("Selection Debug");

            ImGui::Text(
                "Selected Entity ID: %u",
                static_cast<unsigned int>(
                    m_selectedEntity.GetID()));

            ImGui::End();
        }

        if (m_sceneFramebuffer)
        {
            m_viewportPanel.SetTextureID(m_sceneFramebuffer->GetColorAttachmentID());
        }

        m_viewportPanel.OnRender();

        if (m_engine)
        {
            const Window &window = m_engine->GetWindow();

            if (window.GetHeight() > 0)
            {
                const float aspectRatio = static_cast<float>(window.GetWidth()) / static_cast<float>(window.GetHeight());

                m_inspectorPanel.SetAspectRatio(aspectRatio);
            }
        }
    }
}