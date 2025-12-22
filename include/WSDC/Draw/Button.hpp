#pragma once

#include <cmath>
#include <SDL3/SDL_rect.h>

namespace WSDC {

namespace Draw {

struct Button {
    float x, y, w, h;
    SDL_FRect _frect;
    SDL_Rect _rect;

    SDL_Rect* rect(void) {
        _rect = {static_cast<int>(std::round(x)),
                 static_cast<int>(std::round(y)),
                 static_cast<int>(std::round(w)),
                 static_cast<int>(std::round(h))};
        return &_rect;
    }

    SDL_FRect* frect(void) {
        _frect = { x, y, w, h };
        return &_frect;
    }

    bool isAlignedHorizontal(const SDL_FRect& sq) {
        return this->x < sq.x + sq.w    &&
               this->x + this->w > sq.x ;
    }

    bool isAlignedVertical(const SDL_FRect& sq) {
        return this->y < sq.y + sq.h    &&
               this->y + this->h > sq.y ;
    }

    bool isInArea(const SDL_FRect& sq) {
        return isAlignedHorizontal(sq) && isAlignedVertical(sq);
    }
};

} // Draw

} // WSDC
