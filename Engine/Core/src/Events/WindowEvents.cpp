#pragma once

#include "Primitive/Platform/Input.hpp"

namespace primitive
{
    struct KeyPressedEvent
    {
        Key key;
    };

    struct KeyReleasedEvent
    {
        Key key;
    };
}