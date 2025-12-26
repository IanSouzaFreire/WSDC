#pragma once

#include <stdexcept>
#include <string>

#include "Core/Utils.hpp"
#include "Window/RawWindow.hpp"
#include "Core/Color.hpp"
#include "Draw/Image.hpp"

namespace WSDC {

namespace Display {

struct Window {
    using self_t = Window&;
    self_t& self = (*this);
    RawWindow raw;

    Window(void);
    ~Window(void);

    // set flags
    self_t flags(const SDL_WindowFlags&);
    self_t setFlag(const SDL_WindowFlags&, const bool&);
    self_t highPixelDensity(const bool&);
    self_t resizeable(const bool&);

    // configure without rebuilding
    template <typename T> self_t position(const WSDC::Core::Position<T>&);
    template <typename T> self_t size(const WSDC::Core::Size<T>&);
    self_t size(const float&, const float&);

    // remount window with set configurations
    self_t build(void);

    // exit facilities
    self_t close(void);

    // use while running
    self_t update(void);
    self_t setTitle(const char*);
    self_t setIcon(const char*);
    self_t setVSync(const int&);
    template <class F, class... Args> self_t drawRaw(F&&, const WSDC::Core::Color&, Args...);
    template <class F, class... Args> self_t renderRaw(F&&, Args...);
};

Window::Window(void) {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){
        throw std::runtime_error("SDL_Init failed: " + std::string(SDL_GetError()));
    }
    
    if (!TTF_Init()) {
        throw std::runtime_error("TTF_Init failed: " + std::string(SDL_GetError()));
    }
}

Window::~Window(void) {
    close();
}

Window::self_t Window::flags(const SDL_WindowFlags& f) {
    raw.flags = f;
    return self;
}

Window::self_t Window::setFlag(const SDL_WindowFlags& flag, const bool& state) {
    if (state && !(raw.flags & flag)) {
        raw.flags |= flag;
    } else if (!state && (raw.flags & flag)) {
        raw.flags ^= flag;
    }

    return self;
}

Window::self_t Window::highPixelDensity(const bool& b) {
    return setFlag(SDL_WINDOW_HIGH_PIXEL_DENSITY, b);
}

Window::self_t Window::resizeable(const bool& b) {
    return setFlag(SDL_WINDOW_RESIZABLE, b);
}

template <typename T=int>
Window::self_t Window::position(const WSDC::Core::Position<T>& pos) {
    raw.position = pos;
    return self;
}

template <typename T=int>
Window::self_t Window::size(const WSDC::Core::Size<T>& siz) {
    raw.size = siz;
    return self;
}

Window::self_t Window::size(const float& ratio, const float& percentage) {
    return self.size(WSDC::Core::Util::applyNativeMonitorTo<int>(ratio, percentage));
}

Window::self_t Window::build(void) {
    close(); // make sure we dont spam new windows

    raw.window = SDL_CreateWindow(raw.title.c_str(), raw.size.width, raw.size.height, raw.flags);
    if (!raw.window){
        throw std::runtime_error("SDL_CreateWindow failed: " + std::string(SDL_GetError()));
    }
    
    raw.renderer = SDL_CreateRenderer(raw.window, NULL);
    if (!raw.renderer){
        throw std::runtime_error("SDL_CreateRenderer failed: " + std::string(SDL_GetError()));
    }

    return self;
}

Window::self_t Window::close(void) {
    if (raw.renderer) {
        SDL_DestroyRenderer(raw.renderer);
    }

    if (raw.window) {
        SDL_DestroyWindow(raw.window);
    }

    SDL_CloseAudioDevice(raw.audio_device);
    
    TTF_Quit();
    SDL_Quit();
    return self;
}

Window::self_t Window::update(void) {
    SDL_RenderPresent(raw.renderer);

    return self;
}

Window::self_t Window::setTitle(const char* str) {
    SDL_SetWindowTitle(raw.window, str);
    return self;
}

Window::self_t Window::setIcon(const char* path) {
    WSDC::Draw::Image img(path);
    SDL_SetWindowIcon(raw.window, img.getSurface());
    return *this;
}

Window::self_t Window::setVSync(const int& n) {
    if (SDL_SetRenderVSync(raw.renderer, n) == false) {
        throw std::runtime_error("Could not change vsync: " + std::string(SDL_GetError()));
    }
    
    return *this;
}

template <class F, class... Args>
Window::self_t Window::drawRaw(F&& dfun, const WSDC::Core::Color& c, Args... args) {
    SDL_SetRenderDrawColor(raw.renderer, c.r, c.g, c.b, c.a);
    dfun(raw.renderer, args...);
    return self;
}

template <class F, class... Args>
Window::self_t Window::renderRaw(F&& dfun, Args... args) {
    dfun(raw.renderer, args...);
    return self;
}

} // Display

} // WSDC