#pragma once

#include <SDL3/SDL_rect.h>

namespace WSDC {

namespace Geo {


template <typename RR>
struct SDL_RectWrapper {
    RR* ref;

    SDL_RectWrapper(const RR& in) {
        ref = new RR(in);
    }

    void destroy() {
        delete ref;
    }

    ~SDL_RectWrapper() {
        destroy();
    }

    RR* operator&(void) noexcept {
        return ref;
    }
};

template <typename T>
struct Rect {
    T x, y, w, h, &width=w, &height=h;

    template<typename S>
    SDL_RectWrapper<S> get(void) {
        if constexpr (std::is_same_v<S, SDL_Rect>) {
            return { S{ static_cast<int>(x),
                        static_cast<int>(y),
                        static_cast<int>(w),
                        static_cast<int>(h) } };
        } else if (std::is_same_v<S, SDL_FRect>) {
            return { S{ static_cast<float>(x),
                        static_cast<float>(y),
                        static_cast<float>(w),
                        static_cast<float>(h) } };
        } else {
            throw std::runtime_error("rect type not recognized");
        }
        return S{ 0, 0, 0, 0 };
    }
};


} // Geo

} // WSDC
