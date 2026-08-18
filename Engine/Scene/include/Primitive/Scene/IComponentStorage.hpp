#pragma once

#include "Primitive/Scene/EntityID.hpp"

namespace primitive
{
    class IComponentStorage
    {
    public:
        virtual ~IComponentStorage() = default;

        IComponentStorage() = default;

        IComponentStorage(
            const IComponentStorage&) = delete;

        IComponentStorage& operator=(
            const IComponentStorage&) = delete;

        virtual void Remove(EntityID entity) = 0;

        [[nodiscard]]
        virtual bool Has(EntityID entity) const = 0;

        virtual void Clear() = 0;
    };
}