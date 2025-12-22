#pragma once

#include <SDL3/SDL_video.h>
#include <functional>

#include "../Events.hpp"
#include "../Window.hpp"

namespace WSDC {

namespace Managers {

template <class... Others>
class Scene {
    using scene_raw_t = std::function<void(WSDC::Display::Window&, WSDC::Managers::Events&, Others&...)>;
    scene_raw_t scene;

public:
    Scene(const scene_raw_t& scn) {
        scene = scn;
    }

    Scene() {}
    ~Scene() {}

    scene_raw_t& get() {
        return scene;
    }

    scene_raw_t& operator*(void) {
        return scene;
    }

Scene& run(WSDC::Display::Window& w, WSDC::Managers::Events& e, Others&... a) {
    scene(w, e, a...); // WEA!!!
    return *this;
}

    Scene& operator=(const scene_raw_t& other) {
        scene = other;
        return *this;
    }
};

} // Managers

} // WSDC
