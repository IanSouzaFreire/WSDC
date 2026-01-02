#pragma once

#include <optional>

#include "../Core/Types.hpp"
#include "Image.hpp"

namespace WSDC {

namespace Draw {


class SpriteSheet {
    Image _sprite_sheet;
    WSDC::Core::Size<int> _offset;
    WSDC::Core::Size<int> _separation;
    WSDC::Core::Size<int> _sprite_size;

public:
    // configuration
    SpriteSheet& offset(const int&, const int&) noexcept;
    SpriteSheet& separator(const int&, const int&) noexcept;
    SpriteSheet& size(const int&, const int&) noexcept;

    // handle sheet
    SpriteSheet& load(const char* filepath);

    std::optional<WSDC::Draw::Image> operator()(const int& index_x, const int& index_y) const;
};

WSDC::Draw::SpriteSheet& WSDC::Draw::SpriteSheet::offset(const int& px_w, const int& px_h) noexcept {
    _offset.w = px_w;
    _offset.h = px_h;
    return *this;
}

WSDC::Draw::SpriteSheet& WSDC::Draw::SpriteSheet::separator(const int& px_w, const int& px_h) noexcept {
    _separation.w = px_w;
    _separation.h = px_h;
    return *this;
}

WSDC::Draw::SpriteSheet& WSDC::Draw::SpriteSheet::size(const int& px_w, const int& px_h) noexcept {
    _sprite_size.w = px_w;
    _sprite_size.h = px_h;
    return *this;
}

WSDC::Draw::SpriteSheet& WSDC::Draw::SpriteSheet::load(const char* filepath) {
    _sprite_sheet.load(filepath);
    return *this;
}

std::optional<WSDC::Draw::Image> WSDC::Draw::SpriteSheet::operator()(const int& index_x, const int& index_y) const {
    WSDC::Geo::Rect<int> rect;
    rect.x = index_x * _separation.w + index_x * _sprite_size.w + _offset.w;
    rect.y = index_y * _separation.h + index_y * _sprite_size.h + _offset.h;
    rect.w = _sprite_size.w;
    rect.h = _sprite_size.h;
    
    return std::make_optional(_sprite_sheet.crop(rect));
}


} // Draw

} // WSDC
