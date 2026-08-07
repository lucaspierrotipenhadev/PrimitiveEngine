#include "Primitive/Core/Time.hpp"

namespace primitive
{
    Time::Time()
        : m_startTime(Clock::now()),
          m_lastFrameTime(m_startTime)
    {
    }

    void Time::BeginFrame()
    {
        const auto currentTime = Clock::now();

        const std::chrono::duration<float> delta =
            currentTime - m_lastFrameTime;

        const std::chrono::duration<float> elapsed =
            currentTime - m_startTime;

        m_deltaTime = delta.count();
        m_elapsedTime = elapsed.count();

        m_lastFrameTime = currentTime;

        ++m_frameCount;

        if (m_deltaTime > 0.0f)
        {
            m_fps = 1.0f / m_deltaTime;
        }
    }

    float Time::GetDeltaTime() const
    {
        return m_deltaTime;
    }

    float Time::GetElapsedTime() const
    {
        return m_elapsedTime;
    }

    float Time::GetFPS() const
    {
        return m_fps;
    }

    std::uint64_t Time::GetFrameCount() const
    {
        return m_frameCount;
    }
}