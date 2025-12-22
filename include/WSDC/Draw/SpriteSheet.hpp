#pragma once

#include "Image.hpp"
#include "../Core/Position.hpp"

namespace WSDC {

namespace Draw {

class SpriteSheet {
    Image sprite_sheet;
public:
    // configuration
    template <typename T> SpriteSheet& offset(const WSDC::Core::Position<T>& px);
    template <typename T> SpriteSheet& separation(const WSDC::Core::Position<T>& px);
    template <typename T> SpriteSheet& spriteSize(const WSDC::Core::Position<T>& px);
    template <typename T> SpriteSheet& numOfSprites(const WSDC::Core::Position<T>& px);

    // handle sheet
    SpriteSheet& openFile(const char* filepath);
};

} // Draw

} // WSDC
