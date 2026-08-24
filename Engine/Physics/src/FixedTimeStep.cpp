#include "Primitive/Physics/FixedTimeStep.hpp"

#include <algorithm>

namespace primitive
{
    FixedTimeStep::FixedTimeStep(float step)
    {
        SetStep(step);
    }

    void FixedTimeStep::AddTime(float deltaTime)
    {
        if (deltaTime <= 0.0f)
        {
            return;
        }

        constexpr float maxFrameDelta =0.25f;
        m_accumulator += std::min(deltaTime,maxFrameDelta);
    }

    bool FixedTimeStep::CanStep() const
    {
        constexpr float epsilon = 0.000001f;
        return m_accumulator + epsilon >= m_step;
    }

    void FixedTimeStep::ConsumeStep()
    {
        if (!CanStep())
        {
            return;
        }

        m_accumulator -= m_step;

        if(m_accumulator < 0.0f)
        {
            m_accumulator = 0.0f;
        }
    }

    float FixedTimeStep::GetStep() const
    {
        return m_step;
    }

    float
    FixedTimeStep::GetAccumulator() const
    {
        return m_accumulator;
    }

    void FixedTimeStep::SetStep(
        float step)
    {
        if (step <= 0.0f)
        {
            return;
        }

        m_step = step;
        m_accumulator = 0.0f;
    }

    void FixedTimeStep::Reset()
    {
        m_accumulator = 0.0f;
    }
}