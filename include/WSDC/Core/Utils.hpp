#pragma once

#include <SDL3/SDL_video.h>

#include "Size.hpp"
#include "Math.hpp"

namespace WSDC {

namespace Core {

namespace Ratio {
    #define NR(v1, v2) static const float r##v1##_##v2 { (static_cast<float>(v1) / static_cast<float>(v2)) }
    NR(1, 1);
    static const float r185_1 { (static_cast<float>(1.85) / static_cast<float>(1)) };
    static const float r235_1 { (static_cast<float>(2.35) / static_cast<float>(1)) };
    NR(3, 2);
    NR(4, 3);
    NR(5, 4);
    NR(9, 16);
    NR(16, 9);
    NR(16, 10);
    NR(21, 9);
    #undef NR
} // Ratio

namespace Util {

template <typename T>
WSDC::Core::Size<T> applyNativeMonitorTo(const float& ratio, const float& percentage, SDL_DisplayID id = 0) {
    const float p = percentage / 100.f;
    WSDC::Core::Size<T> ret;

    // Get the primary display if id is 0
    if (id == 0) {
        int count = 0;
        SDL_DisplayID* displays = SDL_GetDisplays(&count);
        if (displays && count > 0) {
            id = displays[0];
            SDL_free(displays);
        } else {
            throw std::runtime_error("error searching displays");
        }
    }

    const SDL_DisplayMode* DM = SDL_GetCurrentDisplayMode(id);
    if (!DM) throw std::runtime_error("display dimensions not accesible");

    const float monitor_ratio = static_cast<float>(DM->w) / static_cast<float>(DM->h);
    
    if (monitor_ratio > ratio) {
        ret.height = static_cast<T>(DM->h);
        ret.width = static_cast<T>(DM->h * ratio);
    } else {
        ret.width = static_cast<T>(DM->w);
        ret.height = static_cast<T>(DM->w / ratio);
    }
    
    ret.width = static_cast<T>(ret.width * p);
    ret.height = static_cast<T>(ret.height * p);
    
    return ret;
}

} // Utils

} // Core

} // WSDC
