#include "Primitive/Renderer/Material.hpp"

#include <stdexcept>
#include <utility>

#include "Primitive/Renderer/Shader.hpp"

namespace primitive
{
    Material::Material(
        std::shared_ptr<Shader> shader)
        : m_shader(std::move(shader))
    {
        if (!m_shader)
        {
            throw std::invalid_argument(
                "Material requires a valid Shader."
            );
        }
    }

    void Material::SetBaseColor(
        const glm::vec4& color)
    {
        m_baseColor = color;
    }

    void Material::SetAlbedoTexture(std::shared_ptr<Texture> texture)
    {
        m_albedoTexture = std::move(texture);
    }

    const glm::vec4&
    Material::GetBaseColor() const
    {
        return m_baseColor;
    }

    const std::shared_ptr<Texture>&
    Material::GetAlbedoTexture() const
    {
        return m_albedoTexture;
    }

    const std::shared_ptr<Shader>&
    Material::GetShader() const
    {
        return m_shader;
    }
}