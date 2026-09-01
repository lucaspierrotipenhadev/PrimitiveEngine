#pragma once

#include <filesystem>

namespace primitive
{
    class Project
    {
    public:
        Project() = default;

        explicit Project(std::filesystem::path projectDirectory);

        void SetProjectDirectory(std::filesystem::path projectDirectory);

        [[nodiscard]]
        const std::filesystem::path &GetProjectDirectory() const;

        [[nodiscard]]
        std::filesystem::path GetAssetsDirectory() const;

        [[nodiscard]]
        std::filesystem::path GetAssetPath(const std::filesystem::path &relativePath) const;

        [[nodiscard]]
        bool IsValid() const;

    private:
        std::filesystem::path m_projectDirectory;
    };
}