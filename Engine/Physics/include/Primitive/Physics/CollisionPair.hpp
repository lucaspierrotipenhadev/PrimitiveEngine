#pragma once

#include <cstddef>
#include <functional>

#include "Primitive/Scene/EntityID.hpp"

namespace primitive
{
    struct CollisionPair
    {
        EntityID first{NullEntity};
        EntityID second{NullEntity};

        static CollisionPair Create(EntityID a, EntityID b)
        {
            if(a < b)
            {
                return {a, b};
            }
            return {b, a};
        }

        bool operator==(const CollisionPair&) const = default;
    };

    struct CollisionPairHash
    {
        std::size_t operator()(const CollisionPair& pair) const
        {
            const std::size_t firstHash = std::hash<EntityID>{}(pair.first);
            const std::size_t secondHash = std::hash<EntityID>{}(pair.second);

            return firstHash ^ (secondHash + 0x9e3779b9 + (firstHash << 6) + (firstHash + 2));
        }
    };
};