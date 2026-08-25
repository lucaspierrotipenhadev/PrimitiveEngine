#pragma once

#include "Primitive/Scene/Entity.hpp"

namespace primitive
{
    class Scene;

    class HierarchyPanel
    {
    public:
        HierarchyPanel()=default;

        explicit HierarchyPanel(Scene* scene);

        void SetScene(Scene* scene);
        void OnRender();
        void SetSelectionContext(Entity* selectedEntity);

    private:
        Scene* m_scene{nullptr};
        Entity* m_selectedEntity{nullptr};
    };
}