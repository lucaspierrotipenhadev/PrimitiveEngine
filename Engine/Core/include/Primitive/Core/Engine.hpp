#pragma once

#include <cstdint>

#include "Primitive/Core/Time.hpp"

namespace primitive
{
    class Engine
    {
    public:
        Engine();
        ~Engine();

        void Run();
        void Stop();

    private:
        void Initialize();
        void Shutdown();

        void ProcessEvents();
        void Update(float deltaTime);
        void Render();

    private:
        bool m_running{false};

        Time m_time;
    };
}