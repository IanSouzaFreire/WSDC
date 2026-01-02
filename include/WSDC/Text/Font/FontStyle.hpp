#pragma once

#include <SDL3_ttf/SDL_ttf.h>

#include "../../Core/Types.hpp"

namespace WSDC {

namespace Text {


using Alignment = TTF_HorizontalAlignment;
namespace Align {
    #define NAL(n, v) constexpr static Alignment n = v
    NAL(LEFT,   TTF_HORIZONTAL_ALIGN_LEFT);
    NAL(CENTER, TTF_HORIZONTAL_ALIGN_CENTER);
    NAL(RIGHT,  TTF_HORIZONTAL_ALIGN_RIGHT);
    NAL(NONE,   TTF_HORIZONTAL_ALIGN_INVALID);
    #undef NAL
}

using Weight = int;
namespace Weights {
    #define NWE(n, v) constexpr static Weight n = v
    NWE(THIN,       TTF_FONT_WEIGHT_THIN);          // 100
    NWE(LIGHTER,    TTF_FONT_WEIGHT_EXTRA_LIGHT);   // 200
    NWE(LIGHT,      TTF_FONT_WEIGHT_LIGHT);         // 300
    NWE(NORMAL,     TTF_FONT_WEIGHT_NORMAL);        // 400
    NWE(MEDIUM,     TTF_FONT_WEIGHT_MEDIUM);        // 500
    NWE(SEMI_BOLD,  TTF_FONT_WEIGHT_SEMI_BOLD);     // 600
    NWE(BOLD,       TTF_FONT_WEIGHT_BOLD);          // 700
    NWE(BOLDER,     TTF_FONT_WEIGHT_EXTRA_BOLD);    // 800
    NWE(EXTRA,      TTF_FONT_WEIGHT_BLACK);         // 900
    NWE(GIGA,       TTF_FONT_WEIGHT_EXTRA_BLACK);   // 950
    #undef NWE
}

using Style = int;
namespace Styles {
    #define NES(n, v) constexpr static Style n = v
    NES(NORMAL,     TTF_STYLE_NORMAL);
    NES(BOLD,       TTF_STYLE_BOLD);
    NES(ITALIC,     TTF_STYLE_ITALIC);
    NES(UNDERLINE,  TTF_STYLE_UNDERLINE);
    NES(STRIKE,     TTF_STYLE_STRIKETHROUGH);
    #undef NES
}

struct FontStyle {
    float size = 12.0f;
    WSDC::Text::Weight weight = WSDC::Text::Weights::NORMAL;
    WSDC::Text::Style style = WSDC::Text::Styles::NORMAL;
    WSDC::Text::Alignment align = WSDC::Text::Align::LEFT;
    WSDC::Core::Color color = {127, 127, 127, 255};

    // Equality operator for cache comparison
    bool operator==(const FontStyle& other) const {
        return color.r == other.color.r &&
               color.g == other.color.g &&
               color.b == other.color.b &&
               color.a == other.color.a &&
               size == other.size &&
               weight == other.weight &&
               style == other.style &&
               align == other.align;
    }
    
    bool operator!=(const FontStyle& other) const {
        return !(*this == other);
    }
    
    // Helper constructors
    static FontStyle withSize(float s) {
        FontStyle fs;
        fs.size = s;
        return fs;
    }
    
    static FontStyle withColor(const WSDC::Core::Color& c) {
        FontStyle fs;
        fs.color = c;
        return fs;
    }
    
    static FontStyle withWeight(WSDC::Text::Weight w) {
        FontStyle fs;
        fs.weight = w;
        return fs;
    }
    
    // Preset styles
    static FontStyle heading() {
        FontStyle fs;
        fs.size = 32.0f;
        fs.weight = WSDC::Text::Weights::BOLD;
        return fs;
    }
    
    static FontStyle subheading() {
        FontStyle fs;
        fs.size = 24.0f;
        fs.weight = WSDC::Text::Weights::SEMI_BOLD;
        return fs;
    }
    
    static FontStyle body() {
        FontStyle fs;
        fs.size = 16.0f;
        fs.weight = WSDC::Text::Weights::NORMAL;
        return fs;
    }
    
    static FontStyle small() {
        FontStyle fs;
        fs.size = 12.0f;
        fs.weight = WSDC::Text::Weights::LIGHT;
        return fs;
    }
    
    // Fluent API for chaining
    FontStyle& setSize(float s) {
        size = s;
        return *this;
    }
    
    FontStyle& setColor(const WSDC::Core::Color& c) {
        color = c;
        return *this;
    }
    
    FontStyle& setWeight(WSDC::Text::Weight w) {
        weight = w;
        return *this;
    }
    
    FontStyle& setStyle(WSDC::Text::Style s) {
        style = s;
        return *this;
    }
    
    FontStyle& setAlign(WSDC::Text::Alignment a) {
        align = a;
        return *this;
    }
};


} // Text

} // WSDC