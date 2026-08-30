#include "Primitive/ImGuiPrimitive/Panels/HierarchyPanel.hpp"

#include "Primitive/Scene/Scene.hpp"
#include "Primitive/Scene/Components/TagComponent.hpp"

#include <imgui.h>

#include <string>

namespace primitive
{
    HierarchyPanel::HierarchyPanel(Scene *scene) : m_scene(scene)
    {
    }

    void HierarchyPanel::SetScene(Scene *scene)
    {
        m_scene = scene;
    }

    void HierarchyPanel::OnRender()
    {
        ImGui::Begin("Hierarchy");

        if (!m_scene)
        {
            ImGui::TextDisabled("No active scene.");
            ImGui::End();
            return;
        }

        if (ImGui::Button("+ Entity"))
        {
            CreateEntity();
        }

        ImGui::Separator();

        Entity entityToDestroy{};

        m_scene->ForEachEntity(
            [&](EntityID entityID)
            {
                Entity entity{
                    entityID,
                    m_scene};

                ImGui::PushID(
                    static_cast<int>(
                        entityID));

                std::string name = "Entity";

                if (entity.HasComponent<
                        TagComponent>())
                {
                    name = entity.GetComponent<TagComponent>().tag;
                }

                const bool selected =
                    m_selectionContext &&
                    *m_selectionContext &&
                    m_selectionContext->GetID() == entityID;

                if (ImGui::Selectable(name.c_str(), selected))
                {
                    if (m_selectionContext)
                    {
                        *m_selectionContext = entity;
                    }
                }

                if (ImGui::BeginPopupContextItem("EntityContext"))
                {
                    if (ImGui::MenuItem("Delete Entity"))
                    {
                        entityToDestroy = entity;
                    }

                    ImGui::EndPopup();
                }

                ImGui::PopID();
            });

        if (ImGui::BeginPopupContextWindow(
                "HierarchyContext",
                ImGuiPopupFlags_MouseButtonRight |
                    ImGuiPopupFlags_NoOpenOverItems))
        {
            if(!m_readOnly)
            {
                if (ImGui::MenuItem("Create Entity"))
                {
                CreateEntity();
                }
            }

            ImGui::EndPopup();
        }

        if (entityToDestroy)
        {
            DestroyEntity(
                entityToDestroy);
        }

        ImGui::End();
    }

    void HierarchyPanel::SetSelectionContext(Entity *selectedEntity)
    {
        m_selectionContext = selectedEntity;
    }

    void HierarchyPanel::DrawEntityNode(Entity entity)
    {
        if (!entity)
        {
            return;
        }

        std::string name = "Entity";

        if (entity.HasComponent<TagComponent>())
        {
            name = entity.GetComponent<TagComponent>().tag;
        }

        ImGui::PushID(static_cast<int>(entity.GetID()));

        const bool selected = m_selectionContext && *m_selectionContext && m_selectionContext->GetID() == entity.GetID();

        if (ImGui::Selectable(name.c_str(), selected))
        {
            if (m_selectionContext)
            {
                *m_selectionContext = entity;
            }
        }

        bool deleteEntity = false;

        if (ImGui::BeginPopupContextItem("EntityContextMenu"))
        {
            if (ImGui::MenuItem("Delete entity"))
            {
                deleteEntity = true;
            }
        }

        ImGui::PopID();
    }

    void HierarchyPanel::CreateEntity()
    {
        if (!m_scene)
        {
            return;
        }

        Entity entity = m_scene->CreateEntity("Entity");

        if (m_selectionContext)
        {
            *m_selectionContext = entity;
        }
    }

    void HierarchyPanel::DestroyEntity(Entity entity)
    {
        if (!m_scene || !entity)
        {
            return;
        }

        if (m_selectionContext && *m_selectionContext && m_selectionContext->GetID())
        {
            *m_selectionContext = {};
        }
        m_scene->DestroyEntity(entity);
    }

    void HierarchyPanel::SetReadOnly(bool readOnly)
    {
        m_readOnly = readOnly;
    }
}