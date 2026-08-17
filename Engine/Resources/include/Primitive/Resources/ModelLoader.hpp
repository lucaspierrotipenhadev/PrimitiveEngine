#pragma once

#include "Primitive/Resources/IResourceLoader.hpp"

namespace primitive
{
    class Renderer;

    class ModelLoader final
        : public IResourceLoader
    {
    public:
        explicit ModelLoader(
            Renderer& renderer
        );

        std::shared_ptr<Resource> Load(
            const std::filesystem::path& path
        ) override;

    private:
        Renderer& m_renderer;
    };
}