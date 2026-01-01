#pragma once

#include <SDL3_ttf/SDL_ttf.h>

#include "../../Core/Types.hpp"

namespace WSDC {

namespace Text {


struct FontStyle {
    float size = 12.f;
    int weight = TTF_STYLE_NORMAL;
    int style = TTF_STYLE_NORMAL;
    WSDC::Core::Color color = { 0, 0, 0, 255 };
};


} // Text

} // WSDC
