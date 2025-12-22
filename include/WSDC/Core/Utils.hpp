#pragma once

#include <SDL3/SDL_video.h>

#include "Size.hpp"

namespace WSDC {

namespace Core {

namespace Util {

template <typename T>
WSDC::Core::Size<T> applyNativeMonitorTo(const float& ratio, const float& percentage, SDL_DisplayID id = 0) {
    const float p = percentage / 100.0f;
    WSDC::Core::Size<T> ret;

    // Get the primary display if id is 0
    if (id == 0) {
        int count = 0;
        SDL_DisplayID* displays = SDL_GetDisplays(&count);
        if (displays && count > 0) {
            id = displays[0];
            SDL_free(displays);
        } else {
            // Fallback to default values if no displays found
            ret.w = static_cast<T>(800 * p * ratio);
            ret.h = static_cast<T>(600 * p);
            return ret;
        }
    }

    const SDL_DisplayMode* DM = SDL_GetCurrentDisplayMode(id);
    
    if (!DM) {
        // Fallback to default values if display mode is unavailable
        ret.w = static_cast<T>(800 * p * ratio);
        ret.h = static_cast<T>(600 * p);
        return ret;
    }

    // adjust if monitor is vertical
    if (DM->h > DM->w) {
        ret.w = static_cast<T>(DM->w * p);
        ret.h = static_cast<T>(DM->h * p * ratio);
        return ret;
    } else {
        ret.w = static_cast<T>(DM->w * p * ratio);
        ret.h = static_cast<T>(DM->h * p);
        return ret;
    }
}

} // Utils

} // Core

} // WSDC
