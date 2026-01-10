#pragma once

#include "../Definitions.hpp"

template <typename T, typename I=const T&>
constexpr T WSDC::Math::findD(I A, I B, I C) noexcept {
    return static_cast<T>((B * C) / A);
}
