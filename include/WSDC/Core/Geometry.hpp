#pragma once

#include "../Definitions.hpp"

template <typename RR>
WSDC::Geo::SDL_RectWrapper<RR>::SDL_RectWrapper(const RR& in) {
    ref = new RR(in);
}

template <typename RR>
void WSDC::Geo::SDL_RectWrapper<RR>::destroy() {
    delete ref;
}

template <typename RR>
WSDC::Geo::SDL_RectWrapper<RR>::~SDL_RectWrapper() {
    destroy();
}

template <typename RR>
RR* WSDC::Geo::SDL_RectWrapper<RR>::operator&(void) noexcept {
    return ref;
}

template <typename T>
template<typename S>
WSDC::Geo::SDL_RectWrapper<S> WSDC::Geo::Rect<T>::get(void) const {
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

template <typename T>
template<typename S>
WSDC::Geo::Rect<T>::operator S() const {
    if constexpr (std::is_same_v<S, SDL_Rect> || std::is_same_v<S, const SDL_Rect>) {
        return SDL_Rect{static_cast<int>(x),
                        static_cast<int>(y),
                        static_cast<int>(w),
                        static_cast<int>(h)};
    } else if constexpr (std::is_same_v<S, SDL_FRect> || std::is_same_v<S, const SDL_FRect>) {
        return SDL_FRect{static_cast<float>(x),
                         static_cast<float>(y),
                         static_cast<float>(w),
                         static_cast<float>(h)};
    } else {
        static_assert(std::is_same_v<S, SDL_Rect> || std::is_same_v<S, SDL_FRect>, 
                      "Rect can only convert to SDL_Rect or SDL_FRect");
    }
}

template <typename T>
template <typename Float_t>
WSDC::Geo::Rect<T>& WSDC::Geo::Rect<T>::scale(const Float_t& sc) noexcept {
    x = static_cast<T>(static_cast<Float_t>(x) * sc);
    y = static_cast<T>(static_cast<Float_t>(y) * sc);
    w = static_cast<T>(static_cast<Float_t>(w) * sc);
    h = static_cast<T>(static_cast<Float_t>(h) * sc);
    return *this;
}
