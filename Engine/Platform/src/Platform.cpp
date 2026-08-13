#include "Primitive/Platform/Platform.hpp"

#include <SDL3/SDL.h>

#include <stdexcept>

namespace primitive
{
    Platform::Platform()
    {
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
        {
            throw std::runtime_error(
                SDL_GetError()
            );
        }
    }

    Platform::~Platform()
    {
        SDL_Quit();
    }
}