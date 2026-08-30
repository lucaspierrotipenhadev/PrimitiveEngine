#pragma once

#include <filesystem>

namespace primitive
{
    class Scene;
    class ResourceManager;
    class SceneSerializer
    {
    public:
        explicit SceneSerializer(Scene& scene, ResourceManager& resourceManager);

        bool Serialize(const std::filesystem::path& filepth);
        bool Deserialize(const std::filesystem::path& filepath);

    private:
        Scene& m_scene;
        ResourceManager& m_resourceManager;
    };
}