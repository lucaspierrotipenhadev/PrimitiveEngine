#include "Primitive/ImGuiPrimitive/Panels/ContentBrowserPanel.hpp"

#include <string>

#include <imgui.h>

#include "Primitive/ImGuiPrimitive/DragDropPayloads.hpp"

#include "Primitive/Project/Project.hpp"

#include "Primitive/Assets/AssetManager.hpp"
#include "Primitive/Assets/AssetType.hpp"

namespace
{
    const char *GetAssetTypeLabel(primitive::AssetType type)
    {
        using primitive::AssetType;

        switch (type)
        {
        case AssetType::Scene:
            return "[SCENE]";

        case AssetType::Model:
            return "[MODEL]";

        case AssetType::Texture:
            return "[TEXTURE]";

        case AssetType::Material:
            return "[MATERIAL]";

        case AssetType::Shader:
            return "[SHADER]";

        case AssetType::Script:
            return "[SCRIPT]";

        case AssetType::Animation:
            return "[ANIMATION]";

        case AssetType::None:
        default:
            return "[FILE]";
        }
    }
}

namespace primitive
{
    AssetType ResolveAssetType(const std::filesystem::path &path, const Project &project, const AssetManager &assetManager)
    {
        std::error_code error;

        const std::filesystem::path relativePath =
            std::filesystem::relative(path, project.GetAssetsDirectory(), error);

        if (error)
        {
            return AssetType::None;
        }

        const AssetHandle handle = assetManager.FindByPath(relativePath.lexically_normal());

        if (handle == InvalidAssetHandle)
        {
            return AssetType::None;
        }

        const AssetMetadata *metadata = assetManager.GetMetadata(handle);

        if (!metadata)
        {
            return AssetType::None;
        }

        return metadata->type;
    }

    ContentBrowserPanel::ContentBrowserPanel(const Project &project) : m_project(&project)
    {
        ResetToAssetsDirectory();
    }

    void ContentBrowserPanel::SetProject(const Project *project)
    {
        m_project = project;

        ResetToAssetsDirectory();
    }

    void ContentBrowserPanel::SetAssetManager(const AssetManager *assetManager)
    {
        m_assetManager = assetManager;
    }

    void ContentBrowserPanel::ResetToAssetsDirectory()
    {
        if (!m_project)
        {
            m_currentDirectory.clear();
            return;
        }

        m_currentDirectory = m_project->GetAssetsDirectory().lexically_normal();
    }

    void ContentBrowserPanel::OnRender()
    {
        ImGui::Begin("Content Browser");

        if (!m_project)
        {
            ImGui::TextDisabled("No project loaded.");
            ImGui::End();
            return;
        }

        const std::filesystem::path assetsDirectory = m_project->GetAssetsDirectory();

        std::error_code error;

        if (!std::filesystem::exists(assetsDirectory, error) || error)
        {
            ImGui::TextDisabled("Assets directory does not exist.");
            ImGui::End();
            return;
        }

        if (m_currentDirectory.empty() || !std::filesystem::exists(m_currentDirectory, error) || error)
        {
            ResetToAssetsDirectory();
        }

        DrawNavigationBar();
        ImGui::Separator();
        DrawDirectoryContents();
        ImGui::End();
    }

    bool ContentBrowserPanel::IsInsideAssetsDirectory(const std::filesystem::path &path) const
    {
        if (!m_project)
        {
            return false;
        }

        const std::filesystem::path assetsDirectory = m_project->GetAssetsDirectory().lexically_normal();
        const std::filesystem::path normalizedPath = path.lexically_normal();
        const std::filesystem::path relativePath = normalizedPath.lexically_relative(assetsDirectory);

        if (relativePath.empty())
        {
            return false;
        }

        if (relativePath == ".")
        {
            return true;
        }

        const auto iterator = relativePath.begin();

        if (iterator == relativePath.end())
        {
            return true;
        }

        return *iterator != "..";
    }

    void ContentBrowserPanel::NavigateTo(const std::filesystem::path &directory)
    {
        if (!m_project)
        {
            return;
        }

        if (!IsInsideAssetsDirectory(directory))
        {
            return;
        }

        std::error_code error;

        if (!std::filesystem::exists(directory, error) || error)
        {
            return;
        }

        if (!std::filesystem::is_directory(directory, error) || error)
        {
            return;
        }

        m_currentDirectory = directory.lexically_normal();
    }

    void ContentBrowserPanel::DrawNavigationBar()
    {
        if (!m_project)
        {
            return;
        }

        const std::filesystem::path assetsDirectory = m_project->GetAssetsDirectory().lexically_normal();

        if (m_currentDirectory != assetsDirectory)
        {
            if (ImGui::Button("<-"))
            {
                NavigateTo(m_currentDirectory.parent_path());
            }

            ImGui::SameLine();
        }

        std::filesystem::path accumulatedPath = assetsDirectory;

        if (ImGui::SmallButton("Assets"))
        {
            NavigateTo(assetsDirectory);
        }

        const std::filesystem::path relativePath = m_currentDirectory.lexically_relative(assetsDirectory);

        if (relativePath.empty() || relativePath == ".")
        {
            return;
        }

        for (const auto &part : relativePath)
        {
            accumulatedPath /= part;

            ImGui::SameLine();
            ImGui::TextUnformatted(">");
            ImGui::SameLine();

            const std::string label = part.string();

            ImGui::PushID(accumulatedPath.generic_string().c_str());

            if (ImGui::SmallButton(label.c_str()))
            {
                NavigateTo(accumulatedPath);
            }

            ImGui::PopID();
        }
    }

    void ContentBrowserPanel::DrawDirectoryContents()
    {
        std::error_code error;

        std::filesystem::directory_iterator iterator{
            m_currentDirectory,
            std::filesystem::directory_options::skip_permission_denied,
            error};

        if (error)
        {
            return;
        }

        for (const auto &entry : iterator)
        {
            const std::filesystem::path path = entry.path();
            const std::string filename = path.filename().string();

            if (entry.is_directory(error))
            {
                if (error)
                {
                    error.clear();
                    continue;
                }

                const std::string label = "[DIR] " + filename;

                ImGui::Selectable(label.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick);

                if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                {
                    NavigateTo(path);
                }
            }
            else
            {
                AssetType assetType = AssetType::None;
                AssetHandle handle = InvalidAssetHandle;

                if (m_project && m_assetManager)
                {
                    std::error_code relativeError;

                    const std::filesystem::path relativePath =
                        std::filesystem::relative(
                            path,
                            m_project->GetAssetsDirectory(),
                            relativeError);

                    if (!relativeError)
                    {
                        handle = m_assetManager->FindByPath(relativePath.lexically_normal());

                        if (handle != InvalidAssetHandle)
                        {
                            if (const AssetMetadata *metadata = m_assetManager->GetMetadata(handle))
                            {
                                assetType = metadata->type;
                            }
                        }
                    }
                }

                ImGui::PushID(path.generic_string().c_str());

                ImGui::TextDisabled("%s", GetAssetTypeLabel(assetType));

                ImGui::SameLine();

                ImGui::Selectable(filename.c_str());

                // AQUI começa o Drag & Drop
                if (handle != InvalidAssetHandle && ImGui::BeginDragDropSource())
                {
                    ImGui::SetDragDropPayload(AssetDragDropPayload, &handle, sizeof(AssetHandle));
                    ImGui::Text("%s %s", GetAssetTypeLabel(assetType), filename.c_str());
                    ImGui::EndDragDropSource();
                }

                ImGui::PopID();
            }
        }
    }
}