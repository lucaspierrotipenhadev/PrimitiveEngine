#include "Primitive/Project/Project.hpp"

#include <utility>

namespace primitive
{
    Project::Project(std::filesystem::path projectDirectory) : m_projectDirectory(std::move(projectDirectory))
    {
    }

    void Project::SetProjectDirectory(std::filesystem::path projectDirectory)
    {
        m_projectDirectory = std::move(projectDirectory);
    }

    const std::filesystem::path &Project::GetProjectDirectory() const
    {
        return m_projectDirectory;
    }

    std::filesystem::path
    Project::GetAssetsDirectory() const
    {
        return m_projectDirectory / "Assets";
    }

    std::filesystem::path Project::GetAssetPath(const std::filesystem::path &relativePath) const
    {
        return GetAssetsDirectory() / relativePath;
    }

    bool Project::IsValid() const
    {
        return !m_projectDirectory.empty();
    }
}