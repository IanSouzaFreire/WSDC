#pragma once

#include "../Definitions.hpp"

WSDC::Display::SubWindows::SubWindows(WSDC::Display::Window& win) noexcept {
    _root_window = &win;
}

WSDC::Display::SubWindows::SubWindows(WSDC::Display::Window*& win) noexcept {
    _root_window = win;
}

WSDC::Display::SubWindows& WSDC::Display::SubWindows::root(WSDC::Display::Window& win) noexcept {
    _root_window = &win;
    return *this;
}

WSDC::Display::SubWindows& WSDC::Display::SubWindows::root(WSDC::Display::Window*& win) noexcept {
    _root_window = win;
    return *this;
}

WSDC::Display::SubWindows& WSDC::Display::SubWindows::close_all() noexcept {
    // later
    return *this;
}

WSDC::Display::SubWindows& WSDC::Display::SubWindows::update_all() noexcept {
    // later
    return *this;
}