#pragma once

#include <SDL3/SDL_video.h>
#include <functional>

#include "../Definitions.hpp"

template <class... Others>
WSDC::Managers::Scene<Others...>::Scene(const WSDC::Managers::Scene<Others...>::scene_raw_t& scn) {
    scene = scn;
}

template <class... Others>
WSDC::Managers::Scene<Others...>::scene_raw_t& WSDC::Managers::Scene<Others...>::get() {
    return scene;
}

template <class... Others>
WSDC::Managers::Scene<Others...>::scene_raw_t& WSDC::Managers::Scene<Others...>::operator*(void) {
    return scene;
}

template <class... Others>
WSDC::Managers::Scene<Others...>& WSDC::Managers::Scene<Others...>::run(WSDC::Display::Window& w, WSDC::Managers::Events& e, Others&... a) {
    scene(w, e, a...); // WEA!!!
    return *this;
}

template <class... Others>
WSDC::Managers::Scene<Others...>& WSDC::Managers::Scene<Others...>::operator=(const WSDC::Managers::Scene<Others...>::scene_raw_t& other) {
    scene = other;
    return *this;
}