#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

#include "../Core/Position.hpp"
#include "../Core/Size.hpp"

namespace WSDC {

namespace Display {

struct RawWindow {
    WSDC::Core::Size<int> size;
    WSDC::Core::Position<int> position;
    std::string title,
                renderer_name;
    SDL_WindowFlags flags{SDL_WINDOW_HIGH_PIXEL_DENSITY};
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_AudioDeviceID audio_device;

    RawWindow() {}
};

} // Display

} // WSDC
