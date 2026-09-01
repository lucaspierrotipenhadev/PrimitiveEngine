#include "Primitive/Renderer/FrameBuffer.hpp"
#include "Primitive/ImGuiPrimitive/EditorApplication.hpp"

#include "Primitive/Core/Engine.hpp"

#include "Primitive/ImGuiPrimitive/ImGuiLayer.hpp"
#include "Primitive/ImGuiPrimitive/EditorLayer.hpp"

#include "Primitive/Assets/AssetDiscovery.hpp"

#include "Primitive/Assets/Importers/ModelAssetImporter.hpp"
#include "Primitive/Assets/Importers/TextureAssetImporter.hpp"
#include "Primitive/Assets/Importers/ShaderAssetImporter.hpp"
#include "Primitive/Assets/Importers/SceneAssetImporter.hpp"

#include <memory>

namespace primitive
{
    EditorApplication::EditorApplication() : m_engine(std::make_unique<Engine>())
    {
        m_project.SetProjectDirectory(std::filesystem::current_path());

        m_assetManager = std::make_unique<AssetManager>(m_project, m_engine->GetResourceManager());

        m_assetImporterRegistry.Register(std::make_unique<ModelAssetImporter>());
        m_assetImporterRegistry.Register(std::make_unique<TextureAssetImporter>());
        m_assetImporterRegistry.Register(std::make_unique<SceneAssetImporter>());
        m_assetImporterRegistry.Register(std::make_unique<ShaderAssetImporter>());

        AssetDiscovery::Discover(m_project, *m_assetManager, m_assetImporterRegistry);

        m_engine->PushLayer(std::make_unique<ImGuiLayer>());
        m_engine->PushLayer(std::make_unique<EditorLayer>(m_project, *m_assetManager));

        if(NFD_Init() != NFD_OKAY)
        {
            throw std::runtime_error("Failed to initialize native file dialog.");
        }
    }

    EditorApplication::~EditorApplication()
    {
        NFD_Quit();
    }

    void EditorApplication::Run()
    {
        m_engine->Run();
    }
}