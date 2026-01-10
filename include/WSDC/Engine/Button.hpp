#pragma once

#include <cmath>
#include <string>
#include <functional>

#include "../Definitions.hpp"
#include "../Core/Color.hpp"

WSDC::Entity::Button::Button() :
    _use_text(false),
    _use_bg_image(false),
    _is_in_area(false),
    _last_check(false),
    _last_click_state(false),
    _bg(WSDC::Colors::FUCHSIA),
    _fg(WSDC::Colors::EIGENGRAU),
    _font(nullptr),
    _img(nullptr),
    _prect({0, 0, 0, 0}),
    onClick([](){ return; }),
    onRelease([](){ return; }),
    onHover([](){ return; }),
    onLeave([](){ return; }) {}

WSDC::Entity::Button::~Button() {
    if (_img != nullptr) delete _img;
}

WSDC::Entity::Button& WSDC::Entity::Button::set(const WSDC::Geo::Rect<float>& rect) {
    this->x = rect.x;
    this->y = rect.y;
    this->w = rect.w;
    this->h = rect.h;
    return *this;
}

WSDC::Entity::Button& WSDC::Entity::Button::useText(const bool& b) noexcept {
    _use_text = b;
    return *this;
}

WSDC::Entity::Button& WSDC::Entity::Button::useImg(const bool& b) noexcept {
    if (!b && _img != nullptr) {
        delete _img;
    }
    _use_bg_image = b;
    return *this;
}

WSDC::Entity::Button& WSDC::Entity::Button::font(WSDC::Text::Font& fo) noexcept {
    _font = fo;
    return *this;
}

WSDC::Entity::Button& WSDC::Entity::Button::font(WSDC::Text::Font*& fo) noexcept {
    _font = *fo;
    return *this;
}

WSDC::Draw::Image& WSDC::Entity::Button::img(const std::string& filepath) noexcept {
    if (_img == nullptr) {
        _img = new WSDC::Draw::Image;
    }

    _img->load(filepath);

    return *_img;
}

WSDC::Draw::Image& WSDC::Entity::Button::img() {
    if (_img == nullptr) {
        throw std::runtime_error("[Button::img] image not initialized.");
    }
    return *_img;
}

WSDC::Core::Color& WSDC::Entity::Button::bg() noexcept {
    return _bg;
}

WSDC::Entity::Button& WSDC::Entity::Button::bg(const WSDC::Core::Color& col) noexcept {
    _bg = col;
    return *this;
}

WSDC::Core::Color& WSDC::Entity::Button::fg() noexcept {
    return _fg;
}

WSDC::Entity::Button& WSDC::Entity::Button::fg(const WSDC::Core::Color& col) noexcept {
    _fg = col;
    return *this;
}

bool WSDC::Entity::Button::isAlignedHorizontal(const SDL_FRect& sq) noexcept {
    return _prect.x < sq.x + sq.w   &&
           _prect.x + _prect.w > sq.x ;
}

bool WSDC::Entity::Button::isAlignedVertical(const SDL_FRect& sq) noexcept {
    return _prect.y < sq.y + sq.h   &&
           _prect.y + _prect.h > sq.y ;
}

bool WSDC::Entity::Button::isInArea(const SDL_FRect& sq) noexcept {
    return this->isAlignedHorizontal(sq) && this->isAlignedVertical(sq);
}

void WSDC::Entity::Button::check(const WSDC::Core::Position<float> pointer, const bool& state) {
    SDL_FRect pt;
        pt.x = pointer.x;
        pt.y = pointer.y;
        pt.w = 3.f;
        pt.h = 3.f;
    _is_in_area = this->isInArea(pt);

    if ((_is_in_area == true) &&
        (state == true)) {
        this->onClick();
    }
    
    if ((_is_in_area == true) &&
        (_last_check == false) &&
        (state == false)) {
        this->onHover();
    }
    
    if ((_last_check == true) &&
        (_is_in_area == false)) {
        this->onLeave();
    }
    
    if ((_last_click_state == true) &&
        (state == false) &&
       ((_last_check == true) ||
        (_is_in_area == true))) {
        this->onRelease();
    }

    _last_check = _is_in_area;
    _last_click_state = state;
}

void WSDC::Entity::Button::render(SDL_Renderer*& ren, const std::string& text) {
    SDL_FRect btn_pos = *this;

    if (!_use_bg_image) {
        SDL_SetRenderDrawColor(ren, _bg.r, _bg.g, _bg.b, _bg.a);
    }

    SDL_Surface* surf = nullptr;
    SDL_Texture* texr = nullptr;
    int actual_width = 0;
    int actual_height = 0;

    _font.prepareContext(ren, surf, texr, text, actual_width, actual_height);

    if (_font._style.align == WSDC::Text::Align::CENTER) {
        _prect.x = btn_pos.x - (static_cast<float>(actual_width) / 2);
    } else {
        _prect.x = btn_pos.x;
    }

    _prect.y = btn_pos.y;
    _prect.w = static_cast<float>(actual_width);
    _prect.h = static_cast<float>(actual_height);

    if (SDL_RenderFillRect(ren, &_prect) == false) {
        throw std::runtime_error("[Button::render] Background rendering failed: " + std::string(SDL_GetError()));
    } if (SDL_RenderTexture(ren, texr, nullptr, &_prect) == false) {
        throw std::runtime_error("[Button::render] Text rendering failed: " + std::string(SDL_GetError()));
    }
}
