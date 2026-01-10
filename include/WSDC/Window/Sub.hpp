#pragma once

#include "../Definitions.hpp"

WSDC::Display::SubWindows::SubWindows(WSDC::Diplay::Window& win) noexcept {
    _root_window = &win;
}

WSDC::Display::SubWindows::SubWindows(WSDC::Diplay::Window*& win) noexcept {
    _root_window = win;
}

WSDC::Display::SubWindows& WSDC::Display::SubWindows::root(WSDC::Diplay::Window& win) noexcept {
    _root_window = &win;
}

WSDC::Display::SubWindows& WSDC::Display::SubWindows::root(WSDC::Diplay::Window*& win) noexcept {
    _root_window = win;
}