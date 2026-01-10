#pragma once

#include "../Definitions.hpp"

[[nodiscard]] auto WSDC::rgb(const WSDC::Core::rgb_t& r, const WSDC::Core::rgb_t& g, const WSDC::Core::rgb_t& b) {
    return new WSDC::Core::Color(r, g, b, 255);
}

[[nodiscard]] auto WSDC::rgb(const WSDC::Core::rgb_t& r, const WSDC::Core::rgb_t& g) {
    return new WSDC::Core::Color(r, g, g, 255);
}

[[nodiscard]] auto WSDC::rgb(const WSDC::Core::rgb_t& r) {
    return new WSDC::Core::Color(r, r, r, 255);
}

[[nodiscard]] auto WSDC::rgb(const WSDC::Core::Color& c) {
    return new WSDC::Core::Color(c.r, c.g, c.b, 255);
}

