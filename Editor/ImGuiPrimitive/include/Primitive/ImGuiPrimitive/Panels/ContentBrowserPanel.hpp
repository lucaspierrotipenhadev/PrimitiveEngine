#pragma once

#include <filesystem>

namespace primitive
{
    class Project;
    class AssetManager;

    class ContentBrowserPanel
    {
    public:
        ContentBrowserPanel() = default;

        explicit ContentBrowserPanel(const Project& project);

        void SetProject(const Project* project);
        void SetAssetManager(const AssetManager* assetManager);
        void OnRender();

    private:
        [[nodiscard]]
        bool IsInsideAssetsDirectory(const std::filesystem::path& path) const;

        void NavigateTo(const std::filesystem::path& directory);
        void ResetToAssetsDirectory();
        void DrawNavigationBar();
        void DrawDirectoryContents();

    private:
        const Project* m_project{nullptr};
        const AssetManager* m_assetManager{nullptr};

        std::filesystem::path m_currentDirectory;
    };
}