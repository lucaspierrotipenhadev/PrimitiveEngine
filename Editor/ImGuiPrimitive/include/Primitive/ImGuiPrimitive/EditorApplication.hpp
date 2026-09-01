#pragma once

#include <memory>
#include <nfd.h>

#include "Primitive/Project/Project.hpp"
#include "Primitive/Assets/AssetManager.hpp"
#include "Primitive/Assets/Importers/AssetImporterRegistry.hpp"

namespace primitive
{
    class Engine;

    class EditorApplication
    {
    public:
        EditorApplication();
        ~EditorApplication();

        EditorApplication(const EditorApplication&) = delete;
        EditorApplication& operator=(const EditorApplication&) = delete;

        void Run();
    
    private:
        Project m_project;
        std::unique_ptr<Engine> m_engine;
        std::unique_ptr<AssetManager> m_assetManager;
        AssetImporterRegistry m_assetImporterRegistry;
    };
}