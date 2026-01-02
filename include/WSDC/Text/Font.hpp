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
    
    // Cache structure for rendered text
    struct CachedText {
        SDL_Surface* surface;
        SDL_Texture* texture;
        SDL_Renderer* renderer;
        std::string text;
        FontStyle style;
        int actual_width;
        int actual_height;
        
        CachedText() : surface(nullptr), texture(nullptr), renderer(nullptr),
                       actual_width(0), actual_height(0) {}
        
        ~CachedText() {
            clear();
        }
        
        void clear() {
            if (texture) {
                SDL_DestroyTexture(texture);
                texture = nullptr;
            }
            if (surface) {
                SDL_DestroySurface(surface);
                surface = nullptr;
            }
            renderer = nullptr;
            text.clear();
            actual_width = 0;
            actual_height = 0;
        }
        
        bool matches(const std::string& txt, const FontStyle& s, SDL_Renderer* ren) const {
            return text == txt && 
                   style == s && 
                   renderer == ren &&
                   surface != nullptr &&
                   texture != nullptr;
        }
    };
    
    mutable CachedText cache;

    void prepareContext(SDL_Renderer* ren, SDL_Surface*& surf, SDL_Texture*& texr, 
                       const std::string& txt, int& width, int& height) {
        if (raw == nullptr) {
            throw std::runtime_error("[Font::prepareContext] Font is not loaded.");
        } else if (ren == nullptr) {
            throw std::runtime_error("[Font::prepareContext] Renderer is not set.");
        }
        
        if (cache.matches(txt, _style, ren)) {
            surf = cache.surface;
            texr = cache.texture;
            width = cache.actual_width;
            height = cache.actual_height;
            return;
        }
        
        cache.clear();

        if (raw) {
            TTF_SetFontSize(raw, static_cast<int>(_style.size));
            TTF_SetFontStyle(raw, _style.style);
            // TTF_SetFontWeight(raw, _style.weight);
            TTF_SetFontWrapAlignment(raw, _style.align);
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
            SDL_DestroySurface(surf);
            throw std::runtime_error("[Font::prepareContext] Failed to create texture: " + std::string(SDL_GetError()));
        }
        
        // Get actual rendered dimensions
        width = surf->w;
        height = surf->h;
        
        // Cache the new render
        cache.surface = surf;
        cache.texture = texr;
        cache.renderer = ren;
        cache.text = txt;
        cache.style = _style;
        cache.actual_width = width;
        cache.actual_height = height;
    }
    
    void clearCache() {
        cache.clear();
    }
    
    void applyStyesToFont() {
        if (raw == nullptr) return;
        
        TTF_SetFontSize(raw, static_cast<int>(_style.size));
        TTF_SetFontStyle(raw, _style.style);
        // TTF_SetFontWeight(raw, _style.weight);
        TTF_SetFontWrapAlignment(raw, _style.align);
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
        clearCache();
        
        if (raw != nullptr) {
            TTF_CloseFont(raw);
            raw = nullptr;
        }

        return *this;
    }

    Font& unload(void) {
        clearCache();
        _style = FontStyle();

        return close();
    }

    Font& color(const WSDC::Core::Color& color) {
        if (_style.color.r != color.r || 
            _style.color.g != color.g || 
            _style.color.b != color.b || 
            _style.color.a != color.a) {
            clearCache();
        }
        _style.color = color;
        return *this;
    }

    WSDC::Core::Color& color(void) {
        return _style.color;
    }

    Font& size(const float& size) {
        if (_style.size != size) {
            clearCache();
            _style.size = size;
            if (raw != nullptr) {
                TTF_SetFontSize(raw, static_cast<int>(_style.size));
            }
        }
        return *this;
    }

    float& size(void) {
        return _style.size;
    }

    Font& weight(const Weight& weight) {
        if (raw == nullptr) {
            throw std::runtime_error("[Font::weight] no font to set.");
        }
        if (_style.weight != weight) {
            clearCache();
            _style.weight = weight;
            // TTF_SetFontWeight(raw, _style.weight);
        }
        return *this;
    }

    Weight& weight(void) {
        return _style.weight;
    }

    Font& style(const Style& style) {
        if (raw == nullptr) {
            throw std::runtime_error("[Font::style] no font to set.");
        }
        if (_style.style != style) {
            clearCache();
            _style.style = style;
            TTF_SetFontStyle(raw, _style.style);
        }
        return *this;
    }

    Style& style(void) {
        return _style.style;
    }

    Font& align(const Alignment& a) {
        if (raw == nullptr) {
            throw std::runtime_error("[Font::align] no font to set.");
        }
        if (_style.align != a) {
            clearCache();
            _style.align = a;
            TTF_SetFontWrapAlignment(raw, _style.align);
        }
        return *this;
    }

    Font& load(const std::string& filepath) {
        _filepath = filepath;

        {
            std::ifstream f(_filepath.c_str());
            if (_filepath.empty()) {
                throw std::runtime_error("[Font::load] Font filepath is empty");
            } else if (!f.good()) {
                throw std::runtime_error("[Font::load] Font filepath does not exist: " + filepath);
            }
        }

        close();

        raw = TTF_OpenFont(_filepath.c_str(), static_cast<int>(_style.size));
        if (raw == nullptr) {
            throw std::runtime_error("[Font::load] Failed to open font: " + _filepath + " - " + std::string(SDL_GetError()));
        }
        
        // Apply all current styles to the newly loaded font
        applyStyesToFont();

        return *this;
    }

    std::string& filepath(void) {
        return _filepath;
    }

    Font& styles(const FontStyle& styles) {
        bool changed = (_style != styles);
        if (changed) {
            clearCache();
        }
        _style = styles;
        applyStyesToFont();
        return *this;
    }

    FontStyle& styles(void) {
        return _style;
    }

    [[maybe_unused]] SDL_FRect write(SDL_Renderer* renderer, const Core::Position<float>& pos, 
                                     const std::string& text) {
        if (text.empty()) {
            return SDL_FRect{pos.x, pos.y, 0.0f, 0.0f};
        }

        SDL_Surface* surf = nullptr;
        SDL_Texture* texr = nullptr;
        int actual_width = 0;
        int actual_height = 0;

        prepareContext(renderer, surf, texr, text, actual_width, actual_height);

        SDL_FRect prect;

        if (_style.align == Align::CENTER) {
            prect.x = pos.x - (static_cast<float>(actual_width) / 2);
        } else {
            prect.x = pos.x;
        }
        prect.y = pos.y;
        prect.w = static_cast<float>(actual_width);
        prect.h = static_cast<float>(actual_height);

        if (SDL_RenderTexture(renderer, texr, nullptr, &prect) == false) {
            throw std::runtime_error("[Font::write] Text rendering failed: " + std::string(SDL_GetError()));
        }

        return prect;
    }

    template <typename... Args>
    [[maybe_unused]] SDL_FRect write(SDL_Renderer* r, const Core::Position<float>& p, 
                                     const std::string& f, Args... a) {
        return this->write(r, p, Format::format(f, a...));
    }
    
    // Get text dimensions without rendering
    SDL_FRect measureText(const std::string& text) {
        if (raw == nullptr) {
            throw std::runtime_error("[Font::measureText] Font is not loaded.");
        }
        if (text.empty()) {
            return SDL_FRect{0.0f, 0.0f, 0.0f, 0.0f};
        }
        
        int w = 0, h = 0;
        if (!TTF_GetStringSize(raw, text.c_str(), text.size(), &w, &h)) {
            throw std::runtime_error("[Font::measureText] Failed to measure text: " + std::string(SDL_GetError()));
        }
        
        return SDL_FRect{0.0f, 0.0f, static_cast<float>(w), static_cast<float>(h)};
    }
    
    // Get font height
    int getHeight() const {
        if (raw == nullptr) {
            throw std::runtime_error("[Font::getHeight] Font is not loaded.");
        }
        return TTF_GetFontHeight(raw);
    }
    
    // Get font ascent
    int getAscent() const {
        if (raw == nullptr) {
            throw std::runtime_error("[Font::getAscent] Font is not loaded.");
        }
        return TTF_GetFontAscent(raw);
    }
    
    // Get font descent
    int getDescent() const {
        if (raw == nullptr) {
            throw std::runtime_error("[Font::getDescent] Font is not loaded.");
        }
        return TTF_GetFontDescent(raw);
    }
    
    // Check if font is loaded
    bool isLoaded() const {
        return raw != nullptr;
    }
    
    // Force cache clear
    Font& invalidateCache() {
        clearCache();
        return *this;
    }
};


} // Text

} // WSDC