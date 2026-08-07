#pragma once

#include <memory>

namespace primitive
{
    class Engine;

    class Application
    {
    public:
        Application();
        ~Application();

        void Run();

    private:
        std::unique_ptr<Engine> m_engine;
    };
}