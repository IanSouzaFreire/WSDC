#pragma once

#include "Size.hpp"
#include <SDL3/SDL_video.h>

template <typename T>
Size<T> applyNativeMonitorTo(const float& ratio, const float& percentage, SDL_DisplayID id = 0) {
    const float p = percentage / 100.0f;

    // Get the primary display if id is 0
    if (id == 0) {
        int count = 0;
        SDL_DisplayID* displays = SDL_GetDisplays(&count);
        if (displays && count > 0) {
            id = displays[0];
            SDL_free(displays);
        } else {
            // Fallback to default values if no displays found
            return { .w = static_cast<T>(800 * p * ratio), 
                     .h = static_cast<T>(600 * p) };
        }
    }

    const SDL_DisplayMode* DM = SDL_GetCurrentDisplayMode(id);
    
    if (!DM) {
        // Fallback to default values if display mode is unavailable
        return { .w = static_cast<T>(800 * p * ratio), 
                 .h = static_cast<T>(600 * p) };
    }

    // adjust if monitor is vertical
    if (DM->h > DM->w) {
        return { .w = static_cast<T>(DM->w * p), 
                 .h = static_cast<T>(DM->h * p * ratio) };
    } else {
        return { .w = static_cast<T>(DM->w * p * ratio),
                 .h = static_cast<T>(DM->h * p) };
    }
}