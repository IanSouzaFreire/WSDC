#pragma once

#include "Definitions.hpp"

namespace WSDC::Display {
    volatile SDL_VIDEO_Quitter _WSDC_sdl_video_quitter = SDL_VIDEO_Quitter();
}

WSDC::Display::SDL_VIDEO_Quitter::~SDL_VIDEO_Quitter() {
    SDL_Quit();
}

WSDC::Display::Window::Window(void) {
    if (!SDL_Init(SDL_INIT_VIDEO)){
        throw std::runtime_error("SDL_Init failed: " + std::string(SDL_GetError()));
    }
}

WSDC::Display::Window::~Window(void) {
    close();
}

WSDC::Display::Window& WSDC::Display::Window::flags(const SDL_WindowFlags& f) {
    raw.flags = f;
    return self;
}

WSDC::Display::Window& WSDC::Display::Window::setFlag(const SDL_WindowFlags& flag, const bool& state) {
    if (state && !(raw.flags & flag)) {
        raw.flags |= flag;
    } else if (!state && (raw.flags & flag)) {
        raw.flags ^= flag;
    }

    return self;
}

WSDC::Display::Window& WSDC::Display::Window::highPixelDensity(const bool& b) {
    return setFlag(SDL_WINDOW_HIGH_PIXEL_DENSITY, b);
}

WSDC::Display::Window& WSDC::Display::Window::resizeable(const bool& b) {
    return setFlag(SDL_WINDOW_RESIZABLE, b);
}

template <typename T=int>
WSDC::Display::Window& WSDC::Display::Window::position(const WSDC::Core::Position<T>& pos) {
    raw.position = pos;
    return self;
}

template <typename T=int>
WSDC::Display::Window& WSDC::Display::Window::size(const WSDC::Core::Size<T>& siz) {
    raw.size = siz;
    return self;
}

WSDC::Display::Window& WSDC::Display::Window::size(const float& ratio, const float& percentage, const SDL_DisplayID& id) {
    return self.size(WSDC::Core::Util::applyMonitorTo<int>(ratio, percentage, id));
}

WSDC::Display::Window& WSDC::Display::Window::size(const float& ratio, const float& percentage) {
    return self.size(WSDC::Core::Util::applyNativeMonitorTo<int>(ratio, percentage));
}

WSDC::Display::Window& WSDC::Display::Window::build(void) {
    close(); // make sure we dont spam new windows

    if (!SDL_CreateWindowAndRenderer(raw.title.c_str(), raw.size.width, raw.size.height, raw.flags, &raw.window, &raw.renderer)) {
        throw std::runtime_error("SDL_CreateWindowAndRenderer failed: " + std::string(SDL_GetError()));
    }

    raw.renderer_name = SDL_GetRendererName(raw.renderer);

    return self;
}

WSDC::Display::Window& WSDC::Display::Window::close(void) {
    if (raw.renderer) {
        SDL_DestroyRenderer(raw.renderer);
    }

    if (raw.window) {
        SDL_DestroyWindow(raw.window);
    }

    SDL_CloseAudioDevice(raw.audio_device);
    return self;
}

WSDC::Display::Window& WSDC::Display::Window::update(void) {
    SDL_RenderPresent(raw.renderer);

    return self;
}

WSDC::Display::Window& WSDC::Display::Window::setTitle(const char* str) {
    SDL_SetWindowTitle(raw.window, str);
    return self;
}

WSDC::Display::Window& WSDC::Display::Window::setIcon(const char* path) {
    WSDC::Draw::Image img(path);
    SDL_SetWindowIcon(raw.window, img.getSurface());
    return *this;
}

WSDC::Display::Window& WSDC::Display::Window::setVSync(const int& n) {
    if (SDL_SetRenderVSync(raw.renderer, n) == false) {
        throw std::runtime_error("Could not change vsync: " + std::string(SDL_GetError()));
    }
    
    return *this;
}

template <class F, class... Args>
inline WSDC::Display::Window& WSDC::Display::Window::drawRaw(F&& dfun, const WSDC::Core::Color& c, Args... args) const noexcept {
    SDL_SetRenderDrawColor(raw.renderer, c.r, c.g, c.b, c.a);
    dfun(raw.renderer, args...);
    return self;
}

template <class F, class... Args>
inline WSDC::Display::Window& WSDC::Display::Window::renderRaw(F&& dfun, Args... args) const noexcept {
    dfun(raw.renderer, args...);
    return self;
}

float WSDC::Display::Window::getWidth(const float& percentage = 100) const noexcept {
    return raw.size.w * (percentage / 100);
}

float WSDC::Display::Window::getHeight(const float& percentage = 100) const noexcept {
    return raw.size.h * (percentage / 100);
}
