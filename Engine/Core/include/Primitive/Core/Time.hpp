#pragma once

#include <chrono>
#include <cstdint>

namespace primitive
{
    class Time
    {
    public:
        using Clock = std::chrono::steady_clock;

        Time();

        void BeginFrame();

        float GetDeltaTime() const;
        float GetElapsedTime() const;
        float GetFPS() const;

        std::uint64_t GetFrameCount() const;

    private:
        Clock::time_point m_startTime;
        Clock::time_point m_lastFrameTime;

        float m_deltaTime{0.0f};
        float m_elapsedTime{0.0f};
        float m_fps{0.0f};

        std::uint64_t m_frameCount{0};
    };
}