#pragma once

#include <filesystem>
#include <optional>

namespace primitive
{
    class FileDialogs
    {
    public:
        [[nodiscard]]
        static std::optional<std::filesystem::path> SaveScene();

        [[nodiscard]]
        static std::optional<std::filesystem::path> OpenScene();
    };
}