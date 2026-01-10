#pragma once

#include "Definitions.hpp"

WSDC::Managers::TextRenderer& WSDC::Managers::TextRenderer::renderer(SDL_Renderer*& ren) {
    _renderer = ren;
    return *this;
}

WSDC::Text::Font& WSDC::Managers::TextRenderer::operator[](const std::string& font_name) {
    return fonts[font_name];
}

   SDL_FRect WSDC::Managers::TextRenderer::write(const std::string& font, const WSDC::Core::Position<float>& position, const std::string& text) {
    if (_renderer == nullptr) {
        throw std::runtime_error("[TextRenderer::write] write attempt with non-usable renderer");
    }
    
    return fonts.at(font).write(_renderer, position, text);
}

template <typename... Args>
SDL_FRect WSDC::Managers::TextRenderer::write(const std::string& f, const WSDC::Core::Position<float>& p, const std::string& t, Args... a) {
    return this->write(f, p, WSDC::Format::format(t, a...));
}
