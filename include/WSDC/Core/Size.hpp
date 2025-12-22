#pragma once

namespace WSDC {

namespace Core {

template <typename T=int>
struct Size {
    T w, h, &width=this->w, &height=this->h;

    Size(void) noexcept;
    Size(const Size<T>&) noexcept;
    Size<T>& operator=(const Size<T>&) noexcept;
};

template <typename T>
Size<T>::Size(void) noexcept {}

template <typename T>
Size<T>::Size(const Size<T>& other) noexcept {
    this->w = other.w;
    this->h = other.h;
}

template <typename T>
Size<T>& Size<T>::operator=(const Size<T>& other) noexcept {
    width = other.w;
    height = other.h;
    return *this;
}

} // Core

} // WSDC
