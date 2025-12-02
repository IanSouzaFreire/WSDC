#pragma once

template <typename T=int>
struct Position {
    T x, y, &horizontal=this->x, &vertical=this->y;

    Position<T> operator=(const Position<T>&) noexcept;
};

template <typename T>
Position<T> Position<T>::operator=(const Position<T>& p) noexcept {
    horizontal = p.x;
    vertical = p.y;
    return *this;
}
