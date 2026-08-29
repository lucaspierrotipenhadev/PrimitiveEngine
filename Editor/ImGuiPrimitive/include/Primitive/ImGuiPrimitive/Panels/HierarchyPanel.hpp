#pragma once

#include "Primitive/Scene/Entity.hpp"

namespace primitive
{
    class Scene;
    class Entity;

    class HierarchyPanel
    {
    public:
        HierarchyPanel()=default;

        explicit HierarchyPanel(Scene* scene);

        void SetScene(Scene* scene);
        void OnRender();
        void SetSelectionContext(Entity* selectedEntity);
        void SetReadOnly(bool readOnly);

    private:
        void DrawEntityNode(Entity entity);
        void CreateEntity();
        void DestroyEntity(Entity entity);

    private:
        Scene* m_scene{nullptr};
        Entity* m_selectionContext{nullptr};
        bool m_readOnly{false};
    };
}