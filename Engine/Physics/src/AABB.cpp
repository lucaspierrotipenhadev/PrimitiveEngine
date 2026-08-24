#include "Primitive/Physics/AABB.hpp"

namespace primitive
{
    glm::vec3 AABB::GetCenter() const
    {
        return (max + min)*0.5f;
    }

    glm::vec3 AABB::GetHalfExtends() const
    {
        return (max - min)*0.5f;
    }

    bool AABB::Intercects(const AABB& other) const
    {
        return 
            min.x <= other.max.x &&
            max.x >= other.min.x &&
            
            min.y <= other.max.y &&
            max.y >= other.min.y && 
            
            min.z <= other.max.z &&
            max.z >= other.min.z;
    }
};