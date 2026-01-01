#pragma once

#include <string>
#include <algorithm>
#include <SDL3/SDL.h>
#include <SDL3/SDL_filesystem.h>
#include <SDL3_image/SDL_image.h>

namespace WSDC {

namespace Draw {

struct TextureWrapper {
    SDL_Texture* ref;

    TextureWrapper(SDL_Texture* other) {
        ref = other;
    }

    void destroy() {
        SDL_DestroyTexture(ref);
    }

    ~TextureWrapper() {
        destroy();
    }

    SDL_Texture* operator&(void) noexcept {
        return ref;
    }
};


struct SDL_SurfaceWrapper {
    SDL_Surface* ref;

    SDL_SurfaceWrapper(SDL_Surface* other) {
        ref = other;
    }

    void destroy() {
        SDL_DestroySurface(ref);
    }

    ~SDL_SurfaceWrapper() {
        destroy();
    }

    SDL_Surface* operator&(void) noexcept {
        return ref;
    }

    bool operator!(void) const noexcept {
        return ref == nullptr;
    }

    bool okay(void) const noexcept {
        return ref != nullptr;
    }
};

class Image {
    const std::string base_path;
    SDL_SurfaceWrapper surface;
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

    Image(SDL_Surface*);

    Image(const std::string&);

    ~Image();

    // Load image from file
    bool load(const std::string&);

    // Free the surface
    void free();

    // Get as SDL_Surface (CPU memory)
    SDL_Surface* getSurface() const;

    // Get as SDL_Texture (GPU memory) - requires renderer
    TextureWrapper getTexture(SDL_Renderer*&) const;

    // Load directly as texture (more efficient if you don't need the surface)
    TextureWrapper loadAsTexture(SDL_Renderer*&, const std::string&);

    // Get scaled surface
    SDL_SurfaceWrapper getScaledSurface(int, int, SDL_ScaleMode) const;

    // Convert surface to different pixel format
    SDL_SurfaceWrapper convertSurface(SDL_PixelFormat format) const;

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

    // Crop image
    Image crop(const Geo::Rect<int>& rect) const;
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

Image::Image(SDL_Surface* surf)
        : base_path(""),
          surface(SDL_SurfaceWrapper(surf)),
          width(surface.ref->w),
          height(surface.ref->h),
          loaded(true) {}

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
    
    surface.ref = IMG_Load(filepath.c_str());

    if (!surface.okay()) {
        throw std::runtime_error("[Image::load] Failed to load image '" + filepath + "': " + SDL_GetError());
    }

    // Extract dimensions
    width = surface.ref->w;
    height = surface.ref->h;
    loaded = true;

    return true;
}

void Image::free() {
    if (surface.okay()) {
        surface.destroy();
        surface = SDL_SurfaceWrapper(nullptr);
    }
    loaded = false;
    width = 0;
    height = 0;
}

SDL_Surface* Image::getSurface() const {
    return surface.ref;
}

TextureWrapper Image::getTexture(SDL_Renderer*& renderer) const {
    if (!loaded || !surface.okay() || !renderer) {
        throw std::runtime_error("[Image::getTexture] Image is not loaded or renderer is not set");
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface.ref);
    if (!texture) {
        throw std::runtime_error("[Image::getTexture] Failed to create texture: " + std::string(SDL_GetError()));
    }
    
    return { texture };
}

TextureWrapper Image::loadAsTexture(SDL_Renderer*& renderer, const std::string& filename) {
    if (!renderer) throw std::runtime_error("[Image::loadAsTexture] Renderer is not set");
    
    std::string fullpath = getFullPath(filename);
    SDL_Texture* texture = IMG_LoadTexture(renderer, fullpath.c_str());
    
    if (!texture) {
        throw std::runtime_error("[Image::loadAsTexture] Failed to load texture: " + std::string(SDL_GetError()));
    }

    // Get texture dimensions
    auto fw = static_cast<float>(width),
         fh = static_cast<float>(height);
    SDL_GetTextureSize(texture, &fw, &fh);
    filepath = fullpath;
    extension = getExtension(filepath);
    loaded = true;
    
    return { texture };
}

SDL_SurfaceWrapper Image::getScaledSurface(int new_width, int new_height, SDL_ScaleMode mode = SDL_SCALEMODE_LINEAR) const {
    if (!loaded || !surface.okay()) {
        throw std::runtime_error("[Image::getScaledSurface] Image is not loaded or surface is not set");
    }
    
    SDL_Surface* scaled = SDL_ScaleSurface(surface.ref, new_width, new_height, mode);
    if (!scaled) {
        throw std::runtime_error("[Image::getScaledSurface] Failed to scale surface: " + std::string(SDL_GetError()));
    }
    
    return { scaled };
}

SDL_SurfaceWrapper Image::convertSurface(SDL_PixelFormat format) const {
    if (!loaded || !surface.okay()) {
        throw std::runtime_error("[Image::convertSurface] Image is not loaded or surface is not set");
    }
    
    SDL_Surface* converted = SDL_ConvertSurface(surface.ref, format);
    if (!converted) {
        throw std::runtime_error("[Image::convertSurface] Failed to convert surface: " + std::string(SDL_GetError()));
    }
    
    return { converted };
}

void* Image::getPixels() const {
    if (!loaded || !surface.okay()) {
        throw std::runtime_error("[Image::getPixels] Image is not loaded or surface is not set");
    }
    return surface.ref->pixels;
}

int Image::getPitch() const {
    if (!loaded || !surface.okay()) {
        throw std::runtime_error("[Image::getPitch] Image is not loaded or surface is not set");
    }
    return surface.ref->pitch;
}

SDL_PixelFormat Image::getFormat() const {
    if (!loaded || !surface.okay()) {
        throw std::runtime_error("[Image::getFormat] Image is not loaded or surface is not set");
    }
    return surface.ref->format;
}

bool Image::blitTo(SDL_Surface* dest, const SDL_Rect* srcRect = nullptr, SDL_Rect* destRect = nullptr) const {
    if (!loaded || !surface.okay() || !dest) {
        throw std::runtime_error("[Image::blitTo] Image is not loaded or surface is not set");
    }
    
    return SDL_BlitSurface(surface.ref, srcRect, dest, destRect);
}

bool Image::blitScaledTo(SDL_Surface* dest, const SDL_Rect* srcRect = nullptr, SDL_Rect* destRect = nullptr, SDL_ScaleMode mode = SDL_SCALEMODE_LINEAR) const {
    if (!loaded || !surface.okay() || !dest) {
        throw std::runtime_error("[Image::blitScaledTo] Image is not loaded or surface is not set");
    }
    
    return SDL_BlitSurfaceScaled(surface.ref, srcRect, dest, destRect, mode);
}

bool Image::saveBMP(const std::string& filename) const {
    if (!loaded || !surface.okay()) {
        throw std::runtime_error("[Image::saveBMP] Image is not loaded or surface is not set");
    }
    
    std::string fullpath = getFullPath(filename);
    return SDL_SaveBMP(surface.ref, fullpath.c_str());
}

int Image::getWidth() const { return width; }
int Image::getHeight() const { return height; }
bool Image::isLoaded() const { return loaded; }
std::string Image::getFilepath() const { return filepath; }
std::string Image::getExtension() const { return extension; }
std::string Image::getBasePath() const { return base_path; }

bool Image::setColorMod(Uint8 r, Uint8 g, Uint8 b) {
    if (!loaded || !surface.okay()) {
        throw std::runtime_error("[Image::setColorMod] Image is not loaded or surface is not set");
    }
    return SDL_SetSurfaceColorMod(surface.ref, r, g, b);
}

bool Image::getColorMod(Uint8* r, Uint8* g, Uint8* b) {
    if (!loaded || !surface.okay()) {
        throw std::runtime_error("[Image::getColorMod] Image is not loaded or surface is not set");
    }
    return SDL_GetSurfaceColorMod(surface.ref, r, g, b);
}

bool Image::setAlphaMod(Uint8 a) {
    if (!loaded || !surface.okay()) {
        throw std::runtime_error("[Image::setAlphaMod] Image is not loaded or surface is not set");
    }
    return SDL_SetSurfaceAlphaMod(surface.ref, a);
}

bool Image::getAlphaMod(Uint8* a) const {
    if (!loaded || !surface.okay()) {
        throw std::runtime_error("[Image::getAlphaMod] Image is not loaded or surface is not set");
    }
    return SDL_GetSurfaceAlphaMod(surface.ref, a);
}

bool Image::setBlendMode(SDL_BlendMode mode) {
    if (!loaded || !surface.okay()) {
        throw std::runtime_error("[Image::setBlendMode] Image is not loaded or surface is not set");
    }
    return SDL_SetSurfaceBlendMode(surface.ref, mode);
}

bool Image::getBlendMode(SDL_BlendMode* mode) const {
    if (!loaded || !surface.okay()) {
        throw std::runtime_error("[Image::getBlendMode] Image is not loaded or surface is not set");
    }
    return SDL_GetSurfaceBlendMode(surface.ref, mode);
}

bool Image::lock() {
    if (!loaded || !surface.okay()) {
        throw std::runtime_error("[Image::lock] Image is not loaded or surface is not set");
    }
    return SDL_LockSurface(surface.ref);
}

void Image::unlock() {
    if (loaded && surface.okay()) {
        SDL_UnlockSurface(surface.ref);
    }
}

Image Image::crop(const Geo::Rect<int>& rect) const {
    if (!loaded || !surface.okay()) {
        throw std::runtime_error("[Image::crop] Image is not loaded or surface is not set");
    }

    SDL_Rect clip_rect;
    SDL_GetSurfaceClipRect(surface.ref, &clip_rect);
    SDL_Surface* cropped = SDL_CreateSurface(rect.width, rect.height, surface.ref->format);
    if (!cropped) {
        throw std::runtime_error("[Image::crop] Failed to create cropped surface: " + std::string(SDL_GetError()));
    }
    SDL_BlitSurface(surface.ref, &rect.get<SDL_Rect>(), cropped, nullptr);
    return Image(cropped);
}

} // Draw

} // WSDC
