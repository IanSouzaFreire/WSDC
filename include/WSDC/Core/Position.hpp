#pragma once

#include "../Definitions.hpp"

template <typename T>
constexpr WSDC::Core::Position<T>::Position() noexcept {
    this->x = 0;
    this->y = 0;
}

template <typename T>
constexpr WSDC::Core::Position<T>::Position(const WSDC::Core::Position<T>& p) noexcept {
    this->x = p.x;
    this->y = p.y;
}

template <typename T>
constexpr WSDC::Core::Position<T>::Position(const T& _x, const T& _y) noexcept {
    this->x = _x;
    this->y = _y;
}

template <typename T>
WSDC::Core::Position<T>& WSDC::Core::Position<T>::operator=(const WSDC::Core::Position<T>& p) noexcept {
    horizontal = p.x;
    vertical = p.y;
    return *this;
}
