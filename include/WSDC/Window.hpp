#pragma once

#include <stdexcept>
#include <string>
#include <cstdlib>

#include "Core/Utils.hpp"
#include "Window/RawWindow.hpp"
#include "Core/Color.hpp"
#include "Draw/Image.hpp"

namespace WSDC {

namespace Display {


struct SDL_VIDEO_Quitter {
    ~SDL_VIDEO_Quitter() {
        SDL_Quit();
    }
};

volatile SDL_VIDEO_Quitter sdl_video_quitter = SDL_VIDEO_Quitter();

struct Window {
    Window& self = (*this);
    RawWindow raw;

    Window(void);
    ~Window(void);

    // set flags
    Window& flags(const SDL_WindowFlags&);
    Window& setFlag(const SDL_WindowFlags&, const bool&);
    Window& highPixelDensity(const bool&);
    Window& resizeable(const bool&);

    // configure without rebuilding
    template <typename T> Window& position(const WSDC::Core::Position<T>&);
    template <typename T> Window& size(const WSDC::Core::Size<T>&);
    Window& size(const float&, const float&);

    // remount window with set configurations
    Window& build(void);

    // exit facilities
    Window& close(void);

    // use while running
    Window& update(void);
    Window& setTitle(const char*);
    Window& setIcon(const char*);
    Window& setVSync(const int&);
    template <class F, class... Args> [[maybe_unused]] inline Window& drawRaw(F&&, const WSDC::Core::Color&, Args...) const noexcept;
    template <class F, class... Args> [[maybe_unused]] inline Window& renderRaw(F&&, Args...) const noexcept;

    // get data
    float getWidth(const float&) noexcept;
    float getHeight(const float&) noexcept;
};

Window::Window(void) {
    if (!SDL_Init(SDL_INIT_VIDEO)){
        throw std::runtime_error("SDL_Init failed: " + std::string(SDL_GetError()));
    }
}

Window::~Window(void) {
    close();
}

Window& Window::flags(const SDL_WindowFlags& f) {
    raw.flags = f;
    return self;
}

Window& Window::setFlag(const SDL_WindowFlags& flag, const bool& state) {
    if (state && !(raw.flags & flag)) {
        raw.flags |= flag;
    } else if (!state && (raw.flags & flag)) {
        raw.flags ^= flag;
    }

    return self;
}

Window& Window::highPixelDensity(const bool& b) {
    return setFlag(SDL_WINDOW_HIGH_PIXEL_DENSITY, b);
}

Window& Window::resizeable(const bool& b) {
    return setFlag(SDL_WINDOW_RESIZABLE, b);
}

template <typename T=int>
Window& Window::position(const WSDC::Core::Position<T>& pos) {
    raw.position = pos;
    return self;
}

template <typename T=int>
Window& Window::size(const WSDC::Core::Size<T>& siz) {
    raw.size = siz;
    return self;
}

Window& Window::size(const float& ratio, const float& percentage) {
    return self.size(WSDC::Core::Util::applyNativeMonitorTo<int>(ratio, percentage));
}

Window& Window::build(void) {
    close(); // make sure we dont spam new windows

    if (!SDL_CreateWindowAndRenderer(raw.title.c_str(), raw.size.width, raw.size.height, raw.flags, &raw.window, &raw.renderer)) {
        throw std::runtime_error("SDL_CreateWindowAndRenderer failed: " + std::string(SDL_GetError()));
    }

    raw.renderer_name = SDL_GetRendererName(raw.renderer);

    return self;
}

Window& Window::close(void) {
    if (raw.renderer) {
        SDL_DestroyRenderer(raw.renderer);
    }

    if (raw.window) {
        SDL_DestroyWindow(raw.window);
    }

    SDL_CloseAudioDevice(raw.audio_device);
    return self;
}

Window& Window::update(void) {
    SDL_RenderPresent(raw.renderer);

    return self;
}

Window& Window::setTitle(const char* str) {
    SDL_SetWindowTitle(raw.window, str);
    return self;
}

Window& Window::setIcon(const char* path) {
    WSDC::Draw::Image img(path);
    SDL_SetWindowIcon(raw.window, img.getSurface());
    return *this;
}

Window& Window::setVSync(const int& n) {
    if (SDL_SetRenderVSync(raw.renderer, n) == false) {
        throw std::runtime_error("Could not change vsync: " + std::string(SDL_GetError()));
    }
    
    return *this;
}

template <class F, class... Args>
inline Window& Window::drawRaw(F&& dfun, const WSDC::Core::Color& c, Args... args) const noexcept {
    SDL_SetRenderDrawColor(raw.renderer, c.r, c.g, c.b, c.a);
    dfun(raw.renderer, args...);
    return self;
}

template <class F, class... Args>
inline Window& Window::renderRaw(F&& dfun, Args... args) const noexcept {
    dfun(raw.renderer, args...);
    return self;
}

float Window::getWidth(const float& percentage = 100) noexcept {
    return raw.size.w * (percentage / 100);
}

float Window::getHeight(const float& percentage = 100) noexcept {
    return raw.size.h * (percentage / 100);
}

} // Display

} // WSDC