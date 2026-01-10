#pragma once

#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <string>

#include "../Definitions.hpp"
#include "Format.hpp"

namespace WSDC::Log::Styles {
    static const WSDC::Log::Style none      = 0b0;
    static const WSDC::Log::Style bold      = 0b1 << __COUNTER__;
    static const WSDC::Log::Style dim       = 0b1 << __COUNTER__;
    static const WSDC::Log::Style underline = 0b1 << __COUNTER__;
    static const WSDC::Log::Style inverse   = 0b1 << __COUNTER__;
    static const WSDC::Log::Style blink     = 0b1 << __COUNTER__;
    static const WSDC::Log::Style hidden    = 0b1 << __COUNTER__;
    static const WSDC::Log::Style strike    = 0b1 << __COUNTER__;
    static const WSDC::Log::Style italic    = 0b1 << __COUNTER__;

    // alts
    static const WSDC::Log::Style faint         = WSDC::Log::Styles::dim;
    static const WSDC::Log::Style reverse       = WSDC::Log::Styles::inverse;
    static const WSDC::Log::Style invisible     = WSDC::Log::Styles::hidden;
    static const WSDC::Log::Style strikethrough = WSDC::Log::Styles::strike;
    static const WSDC::Log::Style under         = WSDC::Log::Styles::underline;
    static const WSDC::Log::Style italian       = WSDC::Log::Styles::italic;
    static const WSDC::Log::Style strong        = WSDC::Log::Styles::bold;
    static const WSDC::Log::Style focus         = WSDC::Log::Styles::bold | WSDC::Log::Styles::italic;
} // Styles

bool WSDC::Log::TextStyle::has(const WSDC::Log::Style& s) const {
    return ((this->style) & s);
}

std::string WSDC::Log::style_to_esc(const WSDC::Log::TextStyle& style) {
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

    if (style.has(WSDC::Log::Styles::bold))     sty = sty + "1;";
    if (style.has(WSDC::Log::Styles::dim))      sty = sty + "2;";
    if (style.has(WSDC::Log::Styles::italic))   sty = sty + "3;";
    if (style.has(WSDC::Log::Styles::underline)) sty = sty + "4;";
    if (style.has(WSDC::Log::Styles::blink))    sty = sty + "5;";
    if (style.has(WSDC::Log::Styles::inverse))  sty = sty + "7;";
    if (style.has(WSDC::Log::Styles::hidden))   sty = sty + "8;";
    if (style.has(WSDC::Log::Styles::strike))   sty = sty + "9;";

    if (sty[sty.size()-1] != '[') {
        sty[sty.size()-1] = 'm';
    } else {
        sty = "";
    }

    return sty;
}

inline std::string WSDC::Log::toLink(const std::string& url) {
    return "\x1b]8;;" + url + "\x1b\\" + url + "\x1b]8;;\x1b\\";
}

inline std::string WSDC::Log::toLink(const std::string& url, const std::string& txt) {
    return "\x1b]8;;" + url + "\x1b\\" + txt + "\x1b]8;;\x1b\\";
}

inline std::string WSDC::Log::toLink(WSDC::Log::TextStyle&& style, const std::string& url, const std::string& txt) {
    return WSDC::Log::style_to_esc(style) + "\x1b]8;;" + url + "\x1b\\" + txt + "\x1b]8;;\x1b\\\x1b[0m";
}

inline std::string WSDC::Log::toLink(WSDC::Log::TextStyle&& style, const std::string& url) {
    return WSDC::Log::style_to_esc(style) + "\x1b]8;;" + url + "\x1b\\" + url + "\x1b]8;;\x1b\\\x1b[0m";
}

void WSDC::Log::print(const std::string& fmt) {
    std::printf("%s", fmt.c_str());
}

void WSDC::Log::println(const std::string& fmt) {
    std::printf("%s\n", fmt.c_str());
}

void WSDC::Log::print(WSDC::Log::TextStyle&& style, const std::string& fmt) {
    auto sty = WSDC::Log::style_to_esc(style);

    delete style.fg;
    delete style.bg;

    std::printf("%s%s%s", sty.c_str(),
                          fmt.c_str(),
                          "\x1b[0m");
}

void WSDC::Log::println(WSDC::Log::TextStyle&& style, const std::string& fmt) {
    auto sty = WSDC::Log::style_to_esc(style);

    delete style.fg;
    delete style.bg;

    std::printf("%s%s%s\n", sty.c_str(),
                          fmt.c_str(),
                          "\x1b[0m");
}

template <typename... Args>
void WSDC::Log::print(WSDC::Log::TextStyle&& style, const std::string& fmt, Args... args) {
    auto sty = WSDC::Log::style_to_esc(style);

    delete style.fg;
    delete style.bg;

    std::printf("%s%s%s", sty.c_str(),
                          WSDC::Format::format(fmt, args...).c_str(),
                          "\x1b[0m");
}

template <typename... Args>
void WSDC::Log::println(WSDC::Log::TextStyle&& style, const std::string& fmt, Args... args) {
    auto sty = WSDC::Log::style_to_esc(style);

    delete style.fg;
    delete style.bg;

    std::printf("%s%s%s\n", sty.c_str(),
                          WSDC::Format::format(fmt, args...).c_str(),
                          "\x1b[0m");
}

template <typename... Args>
void WSDC::Log::print(const std::string& fmt, Args... args) {
    printf("%s", WSDC::Format::format(fmt, args...).c_str());
}

template <typename... Args>
void WSDC::Log::println(const std::string& fmt, Args... args) {
    printf("%s\n", WSDC::Format::format(fmt, args...).c_str());
}

void WSDC::Log::setPointerPosition(const int32_t& x, const int32_t& y) {
    printf("\x1b[%d;%dH", y, x);
}

void WSDC::Log::setPointerPosition(const WSDC::Core::Position<int32_t>& position) {
    printf("\x1b[%d;%dH", position.y, position.x);
}

void WSDC::Log::clear() {
    printf("\x1b[2J\x1b[0;0H");
}
