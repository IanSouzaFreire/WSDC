#pragma once

#include <string>
#include <unordered_map>

#include "Core/Geometry.hpp"
#include "Text/Font.hpp"

namespace WSDC {

namespace Managers {


class TextRenderer {
    std::unordered_map<std::string, WSDC::Text::Font> fonts;
    SDL_Renderer* _renderer;
    
public:
    TextRenderer& renderer(SDL_Renderer*& ren) {
        _renderer = ren;
        return *this;
    }

    WSDC::Text::Font& operator[](const std::string& font_name) {
        return fonts[font_name];
    }

    template <typename... Args>
    [[maybe_unused]] SDL_FRect write(const std::string& font, const Core::Position<float>& position, const std::string& text, Args... args) {
        if (_renderer == nullptr) {
            throw std::runtime_error("[TextRenderer::write] write attempt with non-usable renderer");
        }
        
        return fonts.at(font).write(_renderer, position, text, args...);;
    }
};


} // Managers

} // WSDC
