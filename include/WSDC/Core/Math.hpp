#pragma once

namespace WSDC {

namespace Math {

template <typename T, typename I=const T&>
constexpr T findD(I A, I B, I C) noexcept {
    return (B * C) / A;
}

} // Math

} // WSDC
