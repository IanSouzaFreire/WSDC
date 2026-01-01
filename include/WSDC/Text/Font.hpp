#pragma once

#include <string>
#include <unordered_map>
#include <fstream>

#include "Font/FontStyle.hpp"
#include "Format.hpp"

namespace WSDC {

namespace Text {


struct TTF_Quitter {
    ~TTF_Quitter() {
        TTF_Quit();
    }
};

volatile TTF_Quitter ttf_quitter = TTF_Quitter();

class Font {
    TTF_Font* raw = nullptr;
    std::string _filepath;
    FontStyle _style;

    void prepareContext(SDL_Renderer*& ren, SDL_Surface*& surf, SDL_Texture*& texr, const std::string& txt) {
        if (raw == nullptr) {
            throw std::runtime_error("[Font::prepareContext] Font is not loaded.");
        } else if (ren == nullptr) {
            throw std::runtime_error("[Font::prepareContext] Renderer is not set.");
        }

        SDL_Color col;
            col.r = _style.color.r;
            col.g = _style.color.g;
            col.b = _style.color.b;
            col.a = _style.color.a;
        surf = TTF_RenderText_Solid(raw, txt.c_str(), txt.size(), col);
        if (surf == nullptr) {
            throw std::runtime_error("[Font::prepareContext] Failed to render text: " + std::string(SDL_GetError()));
        }

        texr = SDL_CreateTextureFromSurface(ren, surf);
        if (texr == nullptr) {
            throw std::runtime_error("[Font::prepareContext] Failed to create texture: " + std::string(SDL_GetError()));
        }
    }

public:
    Font(void) {
        if (!TTF_Init()) {
            throw std::runtime_error("[Font::Font] TTF_Init failed: " + std::string(SDL_GetError()));
        }
    }

    ~Font(void) {
        unload();
    }

    Font& close(void) {
        if (raw != nullptr) {
            TTF_CloseFont(raw);
            raw = nullptr;
        }

        return *this;
    }

    Font& build(void) {
        close();

        raw = TTF_OpenFont(_filepath.c_str(), _style.size);
        if (raw == nullptr) {
            throw std::runtime_error("[Font::build] Failed to open font: " + _filepath);
        }

        return *this;
    }

    Font& unload(void) {
        _style.color = { 0, 0, 0, 255 };
        _style.size = 12.f;
        _style.weight = TTF_STYLE_NORMAL;
        _style.style = TTF_STYLE_NORMAL;

        return close();
    }

    Font& color(const WSDC::Core::Color& color) {
        _style.color = color;
        return *this;
    }

    WSDC::Core::Color& color(void) {
        return _style.color;
    }

    Font& size(const float& size) {
        _style.size = size;
        return *this;
    }

    float& size(void) {
        return _style.size;
    }

    Font& weight(const int& weight) {
        _style.weight = weight;
        return *this;
    }

    int& weight(void) {
        return _style.weight;
    }

    Font& style(const int& style) {
        _style.style = style;
        return *this;
    }

    int& style(void) {
        return _style.style;
    }

    Font& filepath(const std::string& filepath) {
        _filepath = filepath;

        {
            std::ifstream f(_filepath.c_str());
            if (_filepath.empty()) {
                throw std::runtime_error("[Font::filepath] Font filepath is empty");
            } else if (!f.good()) {
                throw std::runtime_error("[Font::filepath] Font filepath does not exist: " + filepath);
            }
        }

        return *this;
    }

    std::string& filepath(void) {
        return _filepath;
    }

    Font& styles(const FontStyle& styles) {
        _style = styles;
        return *this;
    }

    FontStyle& styles(void) {
        return _style;
    }

    template <typename... Args>
    [[maybe_unused]] SDL_FRect write(SDL_Renderer*& renderer, const Core::Position<float>& pos, const std::string& text, Args... args) {
        SDL_Surface* surf = nullptr;
        SDL_Texture* texr = nullptr;
        const std::string fmt = WSDC::Format::format(text, args...);

        prepareContext(renderer, surf, texr, fmt);

        SDL_FRect prect;
        prect.x = pos.x;
        prect.y = pos.y;
        prect.w = _style.size * static_cast<float>(fmt.size()) * 0.60f;
        prect.h = _style.size;

        if (SDL_RenderTexture(renderer, texr, nullptr, &prect) == false) {
            throw std::runtime_error("[Font::write] Text rendering failed: " + std::string(SDL_GetError()));
        }
        
        SDL_DestroySurface(surf);
        SDL_DestroyTexture(texr);

        return prect;
    }
};


} // Text

} // WSDC
