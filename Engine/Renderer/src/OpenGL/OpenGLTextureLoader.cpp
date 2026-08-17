#include "Primitive/Renderer/OpenGL/OpenGLTextureLoader.hpp"

#include <memory>
#include <stdexcept>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Primitive/Renderer/OpenGL/OpenGLTexture.hpp"

namespace primitive
{
    std::shared_ptr<Resource>
    OpenGLTextureLoader::Load(
        const std::filesystem::path& path)
    {
        int width = 0;
        int height = 0;
        int channels = 0;

        // OpenGL considera a origem da textura embaixo.
        // Arquivos de imagem normalmente começam em cima.
        stbi_set_flip_vertically_on_load(true);

        unsigned char* data =
            stbi_load(
                path.string().c_str(),
                &width,
                &height,
                &channels,
                0
            );

        if (!data)
        {
            throw std::runtime_error(
                "Failed to load texture: "
                + path.string()
            );
        }

        try
        {
            auto texture =
                std::make_shared<OpenGLTexture>(
                    path.string(),
                    static_cast<std::uint32_t>(width),
                    static_cast<std::uint32_t>(height),
                    static_cast<std::uint32_t>(channels),
                    data
                );

            stbi_image_free(data);

            return texture;
        }
        catch (...)
        {
            stbi_image_free(data);
            throw;
        }
    }
}