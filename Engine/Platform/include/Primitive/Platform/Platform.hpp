#pragma once

namespace primitive
{
    class Platform
    {
    public:
        Platform();
        ~Platform();

        Platform(const Platform&) = delete;
        Platform& operator=(const Platform&) = delete;
    };
}