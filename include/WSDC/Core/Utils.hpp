#pragma once

#include "../Definitions.hpp"

template <typename T, typename T2=T>
constexpr float WSDC::Core::Ratio::r(const T& horizontal, const T2& vertical) {
    return static_cast<float>(static_cast<float>(horizontal) / static_cast<float>(vertical));
}

template <typename T>
WSDC::Core::Size<T> WSDC::Core::Util::applyMonitorTo(const float& ratio, const float& percentage, SDL_DisplayID id) {
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

template <typename T>
WSDC::Core::Size<T> WSDC::Core::Util::applyNativeMonitorTo(const float& ratio, const float& percentage) {
    return WSDC::Core::Util::applyMonitorTo<T>(ratio, percentage, 0);
}