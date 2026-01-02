#pragma once

namespace WSDC {

namespace Core {


template <typename T=int>
struct Position {
    T x, y, &horizontal=this->x, &vertical=this->y;

    Position<T>& operator=(const Position<T>&) noexcept;
};

template <typename T>
WSDC::Core::Position<T>& WSDC::Core::Position<T>::operator=(const WSDC::Core::Position<T>& p) noexcept {
    horizontal = p.x;
    vertical = p.y;
    return *this;
}


} // Core

} // WSDC
