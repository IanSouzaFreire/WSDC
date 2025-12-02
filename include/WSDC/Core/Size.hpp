#pragma once

template <typename T=int>
struct Size {
    T w, h, &width=this->w, &height=this->h;

    Size<T> operator=(const Size<T>&) noexcept;
};

template <typename T>
Size<T> Size<T>::operator=(const Size<T>& p) noexcept {
    width = p.w;
    height = p.h;
    return *this;
}
