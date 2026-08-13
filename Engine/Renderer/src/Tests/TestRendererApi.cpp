#include "Primitive/Renderer/Tests/TestRendererApi.hpp"

#include <iostream>

namespace primitive
{
    void TestRendererAPI::Initialize()
    {
        std::cout << "[TestRendererAPI] Initialize\n";
    }

    void TestRendererAPI::Shutdown()
    {
        std::cout << "[TestRendererAPI] Shutdown\n";
    }

    void TestRendererAPI::BeginFrame()
    {
        std::cout << "[TestRendererAPI] BeginFrame\n";
    }

    void TestRendererAPI::EndFrame()
    {
        std::cout << "[TestRendererAPI] EndFrame\n";
    }
}