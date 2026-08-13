#include "Primitive/Tests/TestIResourceLoader.hpp"

#include "Primitive/Core/FileSystem.hpp"

namespace primitive
{
    std::shared_ptr<Resource>
    TestResourceLoader::Load(
        const std::filesystem::path& path)
    {
        const std::string content =
            FileSystem::ReadText(path);

        return std::make_shared<TestResource>(
            path,
            content
        );
    }
}

/*#include "Primitive/Tests/TestIResourceLoader.hpp"

#include <cassert>
#include <iostream>

int main()
{
    using namespace primitive;

    const std::filesystem::path path =
        "test_files/test.txt";

    TestResourceLoader loader;

    auto resource = loader.Load(path);

    assert(resource != nullptr);

    auto testResource =
        std::dynamic_pointer_cast<TestResource>(resource);

    assert(testResource != nullptr);

    assert(
        testResource->GetContent().find(
            "Primitive Engine"
        ) != std::string::npos
    );

    std::cout << "[OK] Resource loaded.\n";
    std::cout << "[OK] Correct resource type.\n";
    std::cout << "[OK] File content loaded.\n";
    std::cin.get();
    
    return 0;
}*/