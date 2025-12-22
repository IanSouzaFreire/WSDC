#pragma once

#include "Image.hpp"
#include "../Core/Position.hpp"

class SpriteSheet {
    Image sprite_sheet;
public:
    // configuration
    template <typename T> SpriteSheet& offset(const Position<T>& px);
    template <typename T> SpriteSheet& separation(const Position<T>& px);
    template <typename T> SpriteSheet& spriteSize(const Position<T>& px);
    template <typename T> SpriteSheet& numOfSprites(const Position<T>& px);

    // handle sheet
    SpriteSheet& openFile(const char* filepath);
};