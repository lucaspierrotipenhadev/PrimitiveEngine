#pragma once

#include <memory>

#include <glm/glm.hpp>

namespace primitive
{
    class Shader;
    class Texture;

    class Material
    {
    public:
        explicit Material(
            std::shared_ptr<Shader> shader
        );

        ~Material() = default;

        Material(const Material&) = delete;
        Material& operator=(const Material&) = delete;

        Material(Material&&) noexcept = default;
        Material& operator=(Material&&) noexcept = default;

        void SetBaseColor(
            const glm::vec4& color
        );

        void SetAlbedoTexture(
            std::shared_ptr<Texture> texture
        );

        [[nodiscard]]
        const glm::vec4& GetBaseColor() const;

        [[nodiscard]]
        const std::shared_ptr<Shader>&
        GetShader() const;

        [[nodiscard]]
        const std::shared_ptr<Texture>&
        GetAlbedoTexture() const;

    private:
        std::shared_ptr<Shader> m_shader;
        std::shared_ptr<Texture> m_albedoTexture;

        glm::vec4 m_baseColor{
            1.0f,
            1.0f,
            1.0f,
            1.0f
        };
    };
}