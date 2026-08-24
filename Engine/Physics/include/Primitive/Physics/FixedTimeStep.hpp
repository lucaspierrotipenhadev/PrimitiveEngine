#pragma once

#include <cstdint>

namespace primitive
{
    class FixedTimeStep
    {
    public:
        explicit FixedTimeStep(float step = 1.0f / 60.0f);

        void AddTime(float deltaTime);
        void SetStep(float step);
        void Reset();

        [[nodiscard]]
        bool CanStep() const;

        void ConsumeStep();

        [[nodiscard]]
        float GetStep() const;

        [[nodiscard]]
        float GetAccumulator() const;


    private:
        float m_step{1.0f / 60.0f};
        float m_accumulator{0.0f};
    };
}