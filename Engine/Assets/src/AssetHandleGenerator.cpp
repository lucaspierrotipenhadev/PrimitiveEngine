#include "Primitive/Assets/AssetHandleGenerator.hpp"

#include <random>

namespace primitive
{
    AssetHandle AssetHandleGenerator::Generate()
    {
        static std::random_device randomDevice;
        static std::mt19937_64 generator{randomDevice()};
        static std::uniform_int_distribution<AssetHandle> distribution{1, UINT64_MAX};

        return distribution(generator);
    }
}