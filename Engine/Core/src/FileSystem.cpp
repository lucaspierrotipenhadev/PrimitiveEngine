#include "Primitive/Core/FileSystem.hpp"

#include <fstream>
#include <stdexcept>

namespace primitive
{
    bool FileSystem::Exists(
        const std::filesystem::path& path)
    {
        return std::filesystem::exists(path);
    }

    std::string FileSystem::ReadText(
        const std::filesystem::path& path)
    {
        std::ifstream file(path);

        if (!file.is_open())
        {
            throw std::runtime_error(
                "Failed to open file: " + path.string()
            );
        }

        return std::string(
            std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>()
        );
    }

    std::vector<std::uint8_t> FileSystem::ReadBinary(
        const std::filesystem::path& path)
    {
        std::ifstream file(
            path,
            std::ios::binary
        );

        if (!file.is_open())
        {
            throw std::runtime_error(
                "Failed to open file: " + path.string()
            );
        }

        file.seekg(0, std::ios::end);

        const auto size =
            static_cast<std::size_t>(file.tellg());

        file.seekg(0, std::ios::beg);

        std::vector<std::uint8_t> data(size);

        if (size > 0)
        {
            file.read(
                reinterpret_cast<char*>(data.data()),
                static_cast<std::streamsize>(size)
            );
        }

        return data;
    }

    std::uintmax_t FileSystem::GetFileSize(
        const std::filesystem::path& path)
    {
        if (!Exists(path))
        {
            throw std::runtime_error(
                "File does not exist: " + path.string()
            );
        }

        return std::filesystem::file_size(path);
    }

    std::string FileSystem::GetFileExtension(
        const std::filesystem::path& path)
    {
        return path.extension().string();
    }

    std::string FileSystem::GetFileName(
        const std::filesystem::path& path)
    {
        return path.filename().string();
    }
}