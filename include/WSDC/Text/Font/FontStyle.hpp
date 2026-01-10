#pragma once

#include "../../Definitions.hpp"

WSDC::Text::FontStyle::FontStyle() :
    size(12.0f),
    weight(WSDC::Text::Weights::NORMAL),
    style(WSDC::Text::Styles::NORMAL),
    align(WSDC::Text::Align::LEFT),
    color({127, 127, 127, 255}) {}

    bool WSDC::Text::FontStyle::operator==(const WSDC::Text::FontStyle& other) const {
        return color.r == other.color.r &&
               color.g == other.color.g &&
               color.b == other.color.b &&
               color.a == other.color.a &&
               size == other.size &&
               weight == other.weight &&
               style == other.style &&
               align == other.align;
    }
    
    bool WSDC::Text::FontStyle::operator!=(const WSDC::Text::FontStyle& other) const {
        return !(*this == other);
    }
    
    WSDC::Text::FontStyle WSDC::Text::FontStyle::withSize(float s) {
        WSDC::Text::FontStyle fs;
        fs.size = s;
        return fs;
    }
    
    WSDC::Text::FontStyle WSDC::Text::FontStyle::withColor(const WSDC::Core::Color& c) {
        WSDC::Text::FontStyle fs;
        fs.color = c;
        return fs;
    }
    
    WSDC::Text::FontStyle WSDC::Text::FontStyle::withWeight(const WSDC::Text::Weights& w) {
        WSDC::Text::FontStyle fs;
        fs.weight = w;
        return fs;
    }
    
    WSDC::Text::FontStyle WSDC::Text::FontStyle::heading() {
        FontStyle fs;
        fs.size = 32.0f;
        fs.weight = WSDC::Text::Weights::BOLD;
        return fs;
    }
    
    WSDC::Text::FontStyle WSDC::Text::FontStyle::subheading() {
        WSDC::Text::FontStyle fs;
        fs.size = 24.0f;
        fs.weight = WSDC::Text::Weights::SEMI_BOLD;
        return fs;
    }
    
    WSDC::Text::FontStyle WSDC::Text::FontStyle::body() {
        WSDC::Text::FontStyle fs;
        fs.size = 16.0f;
        fs.weight = WSDC::Text::Weights::NORMAL;
        return fs;
    }
    
    WSDC::Text::FontStyle WSDC::Text::FontStyle::small() {
        WSDC::Text::FontStyle fs;
        fs.size = 12.0f;
        fs.weight = WSDC::Text::Weights::LIGHT;
        return fs;
    }
    
    // Fluent API for chaining
    WSDC::Text::FontStyle& WSDC::Text::FontStyle::setSize(float s) {
        size = s;
        return *this;
    }
    
    WSDC::Text::FontStyle& WSDC::Text::FontStyle::setColor(const WSDC::Core::Color& c) {
        color = c;
        return *this;
    }
    
    WSDC::Text::FontStyle& WSDC::Text::FontStyle::setWeight(const WSDC::Text::Weights& w) {
        weight = w;
        return *this;
    }
    
    WSDC::Text::FontStyle& WSDC::Text::FontStyle::setStyle(const WSDC::Text::Styles& s) {
        style = s;
        return *this;
    }
    
    WSDC::Text::FontStyle& WSDC::Text::FontStyle::setAlign(const WSDC::Text::Alignment& a) {
        align = a;
        return *this;
    }
