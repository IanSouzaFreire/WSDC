#pragma once

#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <string>

#include "../Core/Types.hpp"
#include "Format.hpp"

namespace WSDC {

namespace Log {


namespace Styles {
    static const uint8_t none      = 0b0;
    static const uint8_t bold      = 0b1 << __COUNTER__;
    static const uint8_t dim       = 0b1 << __COUNTER__;
    static const uint8_t underline = 0b1 << __COUNTER__;
    static const uint8_t inverse   = 0b1 << __COUNTER__;
    static const uint8_t blink     = 0b1 << __COUNTER__;
    static const uint8_t hidden    = 0b1 << __COUNTER__;
    static const uint8_t strike    = 0b1 << __COUNTER__;
    static const uint8_t italic    = 0b1 << __COUNTER__;
    // alts
    static const uint8_t faint         = dim;
    static const uint8_t reverse       = inverse;
    static const uint8_t invisible     = hidden;
    static const uint8_t strikethrough = strike;
    static const uint8_t under         = underline;
    static const uint8_t italian       = italic;
    static const uint8_t strong        = bold;
} // namespace Styles
    
typedef struct TextStyle {
    Core::Color *fg = nullptr,
                *bg = nullptr;
    uint8_t style = Styles::none;
    
    bool has(const uint8_t& s) const {
        return ((this->style) & s);
    }
} TextStyle;

std::string style_to_esc(const TextStyle& style) {
    std::string sty = "\x1b[";

    if (style.fg != nullptr) {
        // ESC[38;2;{r};{g};{b}m
        sty = sty + "38;2;"
                  + std::to_string(style.fg->r) + ";"
                  + std::to_string(style.fg->g) + ";"
                  + std::to_string(style.fg->b) + ";";
    }

    if (style.bg != nullptr) {
        // ESC[48;2;{r};{g};{b}m
        sty = sty + "48;2;"
                  + std::to_string(style.bg->r) + ";"
                  + std::to_string(style.bg->g) + ";"
                  + std::to_string(style.bg->b) + ";";
    }

    if (style.has(Styles::bold))     sty = sty + "1;";
    if (style.has(Styles::dim))      sty = sty + "2;";
    if (style.has(Styles::italic))   sty = sty + "3;";
    if (style.has(Styles::underline)) sty = sty + "4;";
    if (style.has(Styles::blink))    sty = sty + "5;";
    if (style.has(Styles::inverse))  sty = sty + "7;";
    if (style.has(Styles::hidden))   sty = sty + "8;";
    if (style.has(Styles::strike))   sty = sty + "9;";

    if (sty[sty.size()-1] != '[') {
        sty[sty.size()-1] = 'm';
    } else {
        sty = "";
    }

    return sty;
}

inline std::string toLink(const std::string& url) {
    return "\x1b]8;;" + url + "\x1b\\" + url + "\x1b]8;;\x1b\\";
}

inline std::string toLink(const std::string& url, const std::string& txt) {
    return "\x1b]8;;" + url + "\x1b\\" + txt + "\x1b]8;;\x1b\\";
}

inline std::string toLink(TextStyle&& style, const std::string& url, const std::string& txt) {
    return style_to_esc(style) + "\x1b]8;;" + url + "\x1b\\" + txt + "\x1b]8;;\x1b\\\x1b[0m";
}

inline std::string toLink(TextStyle&& style, const std::string& url) {
    return style_to_esc(style) + "\x1b]8;;" + url + "\x1b\\" + url + "\x1b]8;;\x1b\\\x1b[0m";
}

void print(const std::string& fmt) {
    std::printf("%s", fmt.c_str());
}

void println(const std::string& fmt) {
    std::printf("%s\n", fmt.c_str());
}

void print(TextStyle&& style, const std::string& fmt) {
    auto sty = style_to_esc(style);

    delete style.fg;
    delete style.bg;

    std::printf("%s%s%s", sty.c_str(),
                          fmt.c_str(),
                          "\x1b[0m");
}

void println(TextStyle&& style, const std::string& fmt) {
    auto sty = style_to_esc(style);

    delete style.fg;
    delete style.bg;

    std::printf("%s%s%s\n", sty.c_str(),
                          fmt.c_str(),
                          "\x1b[0m");
}

template <typename... Args>
void print(TextStyle&& style, const std::string& fmt, Args... args) {
    auto sty = style_to_esc(style);

    delete style.fg;
    delete style.bg;

    std::printf("%s%s%s", sty.c_str(),
                          Format::format(fmt, args...).c_str(),
                          "\x1b[0m");
}

template <typename... Args>
void println(TextStyle&& style, const std::string& fmt, Args... args) {
    auto sty = style_to_esc(style);

    delete style.fg;
    delete style.bg;

    std::printf("%s%s%s\n", sty.c_str(),
                          Format::format(fmt, args...).c_str(),
                          "\x1b[0m");
}

template <typename... Args>
void print(const std::string& fmt, Args... args) {
    printf("%s", Format::format(fmt, args...).c_str());
}

template <typename... Args>
void println(const std::string& fmt, Args... args) {
    printf("%s\n", Format::format(fmt, args...).c_str());
}

void setPointerPosition(const int32_t& x, const int32_t& y) {
    printf("\x1b[%d;%dH", y, x);
}

void setPointerPosition(const Core::Position<int32_t>& position) {
    printf("\x1b[%d;%dH", position.y, position.x);
}

void clear() {
    printf("\x1b[2J\x1b[0;0H");
}


} // namespace Log

} // namespace WSDC
