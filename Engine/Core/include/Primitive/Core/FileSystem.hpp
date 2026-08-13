#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace primitive
{
    class FileSystem
    {
    public:
        static bool Exists(
            const std::filesystem::path& path);

        static std::string ReadText(
            const std::filesystem::path& path);

        static std::vector<std::uint8_t> ReadBinary(
            const std::filesystem::path& path);

        static std::uintmax_t GetFileSize(
            const std::filesystem::path& path);

        static std::string GetFileExtension(
            const std::filesystem::path& path);

        static std::string GetFileName(
            const std::filesystem::path& path);
    };
}