#pragma once

#include "../Definitions.hpp"

template <typename T>
WSDC::Core::Size<T>::Size(void) noexcept {}

template <typename T>
WSDC::Core::Size<T>::Size(const WSDC::Core::Size<T>& other) noexcept {
    this->w = other.w;
    this->h = other.h;
}

template <typename T>
WSDC::Core::Size<T>::Size(const T& _width, const T& _height) noexcept {
    this->w = _width;
    this->h = _height;
}

template <typename T>
WSDC::Core::Size<T>& WSDC::Core::Size<T>::operator=(const WSDC::Core::Size<T>& other) noexcept {
    width = other.w;
    height = other.h;
    return *this;
}
