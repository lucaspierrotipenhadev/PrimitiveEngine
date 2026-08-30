#pragma once

#include <cstddef>
#include <memory>
#include <string_view>
#include <vector>

#include "Primitive/Resources/Resource.hpp"

namespace primitive
{
    class Mesh;

    class Model final : public Resource
    {
    public:
        explicit Model(std::string_view filepath);

        ~Model() override;

        Model(const Model &) = delete;
        Model &operator=(const Model &) = delete;

        Model(Model &&) noexcept;
        Model &operator=(Model &&) noexcept;

        void AddMesh(
            std::unique_ptr<Mesh> mesh);

        [[nodiscard]]
        std::size_t GetMeshCount() const;

        [[nodiscard]]
        const Mesh &GetMesh(
            std::size_t index) const;

        [[nodiscard]]
        Mesh &GetMesh(
            std::size_t index);

        [[nodiscard]]
        const std::vector<std::unique_ptr<Mesh>> &
        GetMeshes() const;

    private:
        std::vector<
            std::unique_ptr<Mesh>>
            m_meshes;
    };
}