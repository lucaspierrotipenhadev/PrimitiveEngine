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

        if (m_scene)
        {
            m_scene->ForEachEntity(
                [this](EntityID entityID)
                {
                    Entity entity(
                        entityID,
                        m_scene);

                    ImGui::PushID(
                        static_cast<int>(
                            entityID));

                    std::string name =
                        "Entity";

                    if (entity.HasComponent<
                            TagComponent>())
                    {
                        name =
                            entity
                                .GetComponent<
                                    TagComponent>()
                                .tag;
                    }

                    const bool selected =
                        m_selectedEntity &&
                        m_selectedEntity->IsValid() &&
                        m_selectedEntity->GetID() ==
                            entityID;

                    if (ImGui::Selectable(
                            name.c_str(),
                            selected))
                    {
                        if (m_selectedEntity)
                        {
                            *m_selectedEntity =
                                entity;
                        }
                    }

                    ImGui::PopID();
                });
        }

        ImGui::End();
    }

    void HierarchyPanel::SetSelectionContext(Entity *selectedEntity)
    {
        m_selectedEntity = selectedEntity;
    }
}