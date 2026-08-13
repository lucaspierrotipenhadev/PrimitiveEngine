/*#include "Primitive/Core/FileSystem.hpp"

#include <cassert>
#include <iostream>

int main()
{
    using namespace primitive;

    const std::filesystem::path path =
        "test_files/test.txt";

    std::cout << "=== FileSystem Test ===\n\n";

    // Exists
    assert(FileSystem::Exists(path));

    std::cout << "[OK] File exists.\n";

    // GetFileName
    assert(
        FileSystem::GetFileName(path) ==
        "test.txt"
    );

    std::cout << "[OK] File name.\n";

    // GetFileExtension
    assert(
        FileSystem::GetFileExtension(path) ==
        ".txt"
    );

    std::cout << "[OK] File extension.\n";

    // GetFileSize
    const auto size =
        FileSystem::GetFileSize(path);

    assert(size > 0);

    std::cout << "[OK] File size.\n";

    // ReadText
    const auto content =
        FileSystem::ReadText(path);

    assert(
        content.find("Primitive Engine") !=
        std::string::npos
    );

    std::cout << "[OK] ReadText.\n";

    // ReadBinary
    const auto binary =
        FileSystem::ReadBinary(path);

    assert(!binary.empty());

    std::cout << "[OK] ReadBinary.\n";

    // Missing file
    assert(
        !FileSystem::Exists(
            "test_files/missing.txt"
        )
    );

    std::cout << "[OK] Missing file detection.\n";

    std::cout << "\n=== All tests passed! ===\n";
    std::cin.get();
    return 0;
}*/