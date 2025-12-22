#pragma once

#include <string>
#include <algorithm>
#include <SDL3/SDL.h>
#include <SDL3/SDL_filesystem.h>
#include <SDL3_image/SDL_image.h>

namespace WSDC {

namespace Draw {

class Image {
    const std::string base_path;
    SDL_Surface* surface;
    std::string filepath;
    std::string extension;
    int width;
    int height;
    bool loaded;

    // Extract file extension from path
    std::string getExtension(const std::string&);

    // Get the full file path
    std::string getFullPath(const std::string&) const;

public:
    Image();

    Image(const std::string&);

    ~Image();

    // Load image from file
    bool load(const std::string&);

    // Free the surface
    void free();

    // Get as SDL_Surface (CPU memory)
    SDL_Surface* getSurface() const;

    // Get as SDL_Texture (GPU memory) - requires renderer
    SDL_Texture* getTexture(SDL_Renderer*) const;

    // Load directly as texture (more efficient if you don't need the surface)
    SDL_Texture* loadAsTexture(SDL_Renderer*, const std::string&);

    // Get scaled surface
    SDL_Surface* getScaledSurface(int, int, SDL_ScaleMode) const;

    // Convert surface to different pixel format
    SDL_Surface* convertSurface(SDL_PixelFormat format) const;

    // Get raw pixel data
    void* getPixels() const;

    // Get pitch (bytes per row)
    int getPitch() const;

    // Get pixel format
    SDL_PixelFormat getFormat() const;

    // Blit to another surface
    bool blitTo(SDL_Surface*, const SDL_Rect*, SDL_Rect*) const;

    // Blit with scaling
    bool blitScaledTo(SDL_Surface*, const SDL_Rect*, SDL_Rect*, SDL_ScaleMode) const;

    // Save as BMP
    bool saveBMP(const std::string&) const;

    // Getters
    int getWidth() const;
    int getHeight() const;
    bool isLoaded() const;
    std::string getFilepath() const;
    std::string getExtension() const;
    std::string getBasePath() const;

    // Set color modulation
    bool setColorMod(Uint8, Uint8, Uint8);

    // Get color modulation
    bool getColorMod(Uint8*, Uint8*, Uint8*);

    // Set alpha modulation
    bool setAlphaMod(Uint8);

    // Get alpha modulation
    bool getAlphaMod(Uint8*) const;

    // Set blend mode
    bool setBlendMode(SDL_BlendMode);

    // Get blend mode
    bool getBlendMode(SDL_BlendMode*) const;

    // Lock surface for direct pixel access
    bool lock();

    // Unlock surface
    void unlock();
};

std::string Image::getExtension(const std::string& path) {
    size_t dot_pos = path.find_last_of('.');
    if (dot_pos != std::string::npos) {
        std::string ext = path.substr(dot_pos + 1);
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
        return ext;
    }
    return "";
}

std::string Image::getFullPath(const std::string& filename) const {
    if (filename.empty()) return "";
    
    // If filename is already an absolute path, use it directly
    if (filename[0] == '/' || (filename.length() > 1 && filename[1] == ':')) {
        return filename;
    }
    
    // Otherwise, prepend base path
    return base_path + filename;
}

Image::Image()
        : base_path(SDL_GetBasePath() ? SDL_GetBasePath() : ""),
          surface(nullptr),
          width(0),
          height(0),
          loaded(false) {}

Image::Image(const std::string& filename)
        : base_path(SDL_GetBasePath() ? SDL_GetBasePath() : ""),
          surface(nullptr),
          width(0),
          height(0),
          loaded(false) {
    load(filename);
}

Image::~Image() {
    free();
}

bool Image::load(const std::string& filename) {
    free(); // Clean up any existing surface
    
    filepath = getFullPath(filename);
    extension = getExtension(filepath);
    
    if (extension.empty()) {
        SDL_Log("Error: No file extension found for %s", filepath.c_str());
        return false;
    }

    
    surface = IMG_Load(filepath.c_str());

    if (!surface) {
        SDL_Log("Failed to load image %s: %s", filepath.c_str(), SDL_GetError());
        return false;
    }

    // Extract dimensions
    width = surface->w;
    height = surface->h;
    loaded = true;

    return true;
}

void Image::free() {
    if (surface) {
        SDL_DestroySurface(surface);
        surface = nullptr;
    }
    loaded = false;
    width = 0;
    height = 0;
}

SDL_Surface* Image::getSurface() const {
    return surface;
}

SDL_Texture* Image::getTexture(SDL_Renderer* renderer) const {
    if (!loaded || !surface || !renderer) {
        return nullptr;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
    }
    
    return texture;
}

SDL_Texture* Image::loadAsTexture(SDL_Renderer* renderer, const std::string& filename) {
    if (!renderer) return nullptr;
    
    std::string fullpath = getFullPath(filename);
    SDL_Texture* texture = IMG_LoadTexture(renderer, fullpath.c_str());
    
    if (!texture) {
        SDL_Log("Failed to load texture %s: %s", fullpath.c_str(), SDL_GetError());
        return nullptr;
    }

    // Get texture dimensions
    auto fw = static_cast<float>(width),
         fh = static_cast<float>(height);
    SDL_GetTextureSize(texture, &fw, &fh);
    filepath = fullpath;
    extension = getExtension(filepath);
    loaded = true;
    
    return texture;
}

SDL_Surface* Image::getScaledSurface(int new_width, int new_height, SDL_ScaleMode mode = SDL_SCALEMODE_LINEAR) const {
    if (!loaded || !surface) {
        return nullptr;
    }
    
    SDL_Surface* scaled = SDL_ScaleSurface(surface, new_width, new_height, mode);
    if (!scaled) {
        SDL_Log("Failed to scale surface: %s", SDL_GetError());
    }
    
    return scaled;
}

SDL_Surface* Image::convertSurface(SDL_PixelFormat format) const {
    if (!loaded || !surface) {
        return nullptr;
    }
    
    SDL_Surface* converted = SDL_ConvertSurface(surface, format);
    if (!converted) {
        SDL_Log("Failed to convert surface: %s", SDL_GetError());
    }
    
    return converted;
}

void* Image::getPixels() const {
    if (!loaded || !surface) {
        return nullptr;
    }
    return surface->pixels;
}

int Image::getPitch() const {
    if (!loaded || !surface) {
        return 0;
    }
    return surface->pitch;
}

SDL_PixelFormat Image::getFormat() const {
    if (!loaded || !surface) {
        return SDL_PIXELFORMAT_UNKNOWN;
    }
    return surface->format;
}

bool Image::blitTo(SDL_Surface* dest, const SDL_Rect* srcRect = nullptr, SDL_Rect* destRect = nullptr) const {
    if (!loaded || !surface || !dest) {
        return false;
    }
    
    return SDL_BlitSurface(surface, srcRect, dest, destRect);
}

bool Image::blitScaledTo(SDL_Surface* dest, const SDL_Rect* srcRect = nullptr, SDL_Rect* destRect = nullptr, SDL_ScaleMode mode = SDL_SCALEMODE_LINEAR) const {
    if (!loaded || !surface || !dest) {
        return false;
    }
    
    return SDL_BlitSurfaceScaled(surface, srcRect, dest, destRect, mode);
}

bool Image::saveBMP(const std::string& filename) const {
    if (!loaded || !surface) {
        return false;
    }
    
    std::string fullpath = getFullPath(filename);
    return SDL_SaveBMP(surface, fullpath.c_str());
}

int Image::getWidth() const { return width; }
int Image::getHeight() const { return height; }
bool Image::isLoaded() const { return loaded; }
std::string Image::getFilepath() const { return filepath; }
std::string Image::getExtension() const { return extension; }
std::string Image::getBasePath() const { return base_path; }

bool Image::setColorMod(Uint8 r, Uint8 g, Uint8 b) {
    if (!loaded || !surface) {
        return false;
    }
    return SDL_SetSurfaceColorMod(surface, r, g, b);
}

bool Image::getColorMod(Uint8* r, Uint8* g, Uint8* b) {
    if (!loaded || !surface) {
        return false;
    }
    return SDL_GetSurfaceColorMod(surface, r, g, b);
}

bool Image::setAlphaMod(Uint8 a) {
    if (!loaded || !surface) {
        return false;
    }
    return SDL_SetSurfaceAlphaMod(surface, a);
}

bool Image::getAlphaMod(Uint8* a) const {
    if (!loaded || !surface) {
        return false;
    }
    return SDL_GetSurfaceAlphaMod(surface, a);
}

bool Image::setBlendMode(SDL_BlendMode mode) {
    if (!loaded || !surface) {
        return false;
    }
    return SDL_SetSurfaceBlendMode(surface, mode);
}

bool Image::getBlendMode(SDL_BlendMode* mode) const {
    if (!loaded || !surface) {
        return false;
    }
    return SDL_GetSurfaceBlendMode(surface, mode);
}

bool Image::lock() {
    if (!loaded || !surface) {
        return false;
    }
    return SDL_LockSurface(surface);
}

void Image::unlock() {
    if (loaded && surface) {
        SDL_UnlockSurface(surface);
    }
}

} // Draw

} // WSDC
