#pragma once

#include <cmath>
#include "../Core/Geometry.hpp"

namespace WSDC {

namespace Draw {

struct Button : public Geo::Rect<float> {

    bool isAlignedHorizontal(const SDL_FRect& sq) {
        return this->x < sq.x + sq.w   &&
               this->x + this->w > sq.x ;
    }

    bool isAlignedVertical(const SDL_FRect& sq) {
        return this->y < sq.y + sq.h   &&
               this->y + this->h > sq.y ;
    }

    bool isInArea(const SDL_FRect& sq) {
        return isAlignedHorizontal(sq) && isAlignedVertical(sq);
    }
};

} // Draw

} // WSDC
