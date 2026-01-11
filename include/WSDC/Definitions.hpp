#pragma once

#include <array>
#include <string_view>
#include <utility>
#include <cstddef>
#include <unordered_set>
#include <unordered_map>
#include <cstdlib>
#include <cstdint>
#include <variant>
#include <vector>
#include <string>
#include <functional>
#include <optional>
#include <stdexcept>
#include <algorithm>
#include <atomic>
#include <thread>
#include <map>
#include <tuple>
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

namespace WSDC {


namespace Geo {
    template <typename RR>
    struct SDL_RectWrapper {
        RR* ref;

        SDL_RectWrapper(const RR&);
        void destroy();
        ~SDL_RectWrapper();
        RR* operator&(void) noexcept;
    };

    template <typename T>
    struct Rect {
        T x, y, w, h, &horizontal=x, &vertical=y, &width=w, &height=h;

        template<typename S> WSDC::Geo::SDL_RectWrapper<S> get(void) const;
        template<typename S> operator S() const;
        template<typename Float_t> WSDC::Geo::Rect<T>& scale(const Float_t& sc) noexcept;
    };
}

namespace Math {
    template<typename T, typename I> constexpr T findD(I, I, I) noexcept;
}

namespace Core {
    namespace Ratio {
        template<typename T, typename T2> constexpr float r(const T&, const T2&);
        
        #define DEFINE_NEW_RATIO(v1, v2) static const float r##v1##_##v2 = (static_cast<float>(v1) / static_cast<float>(v2));
        DEFINE_NEW_RATIO(1, 1)
        static const float r185_1 = (static_cast<float>(1.85) / static_cast<float>(1));
        static const float r235_1 = (static_cast<float>(2.35) / static_cast<float>(1));
        DEFINE_NEW_RATIO(3, 2)
        DEFINE_NEW_RATIO(4, 3)
        DEFINE_NEW_RATIO(5, 4)
        DEFINE_NEW_RATIO(9, 16)
        DEFINE_NEW_RATIO(16, 9)
        DEFINE_NEW_RATIO(16, 10)
        DEFINE_NEW_RATIO(21, 9)
        #undef DEFINE_NEW_RATIO
    }

    template <typename T=int>
    struct Size {
        T w, h, &width=this->w, &height=this->h;

        Size(void) noexcept;
        Size(const Size<T>&) noexcept;
        Size(const T&, const T&) noexcept;
        Size<T>& operator=(const Size<T>&) noexcept;
    };

    namespace Util {
        template<typename T> WSDC::Core::Size<T> applyMonitorTo(const float&, const float&, SDL_DisplayID);
        template<typename T> WSDC::Core::Size<T> applyNativeMonitorTo(const float&, const float&);
    }

    using rgb_t = uint8_t;

    struct Color {
        WSDC::Core::rgb_t r=0, g=r, b=g, a=255;

        constexpr Color(const WSDC::Core::Color& col) {
            this->r = col.r;
            this->g = col.g;
            this->b = col.a;
            this->a = col.a;
        }

        constexpr Color(const WSDC::Core::rgb_t& _r, const WSDC::Core::rgb_t& _g, const WSDC::Core::rgb_t& _b, const WSDC::Core::rgb_t& _a) {
            this->r = _r;
            this->g = _g;
            this->b = _b;
            this->a = _a;
        }
                
        WSDC::Core::Color& operator=(const WSDC::Core::Color& other) {
            r = other.r;
            g = other.g;
            b = other.b;
            a = other.a;
            return *this;
        }
    };

    template <typename T=int>
    struct Position {
        T x, y, &horizontal=this->x, &vertical=this->y;

        constexpr Position() noexcept;
        constexpr Position(const Position<T>&) noexcept;
        constexpr Position(const T&, const T&) noexcept;
        Position<T>& operator=(const Position<T>&) noexcept;
    };

}

[[nodiscard]] auto rgb(const WSDC::Core::rgb_t&, const WSDC::Core::rgb_t&, const WSDC::Core::rgb_t&);
[[nodiscard]] auto rgb(const WSDC::Core::rgb_t&, const WSDC::Core::rgb_t&);
[[nodiscard]] auto rgb(const WSDC::Core::rgb_t&);
[[nodiscard]] auto rgb(const WSDC::Core::Color&);

template <std::size_t N>
struct ConstStringColorMap {
    std::array<std::pair<std::string_view, WSDC::Core::Color>, N> data;


    constexpr ConstStringColorMap(
        std::array<std::pair<std::string_view, WSDC::Core::Color>, N> init
    ) : data(init) {}

    constexpr const WSDC::Core::Color& operator[](std::string_view key) const {
        for (const auto& [k, v] : data) {
            if (k == key)
                return v;
        }

        throw "ConstStringColorMap: key not found";
    }
};

constexpr static std::size_t palette_size = 
#ifndef WSDC_BASIC_PALETTE
31868
#else
6
#endif
;
constexpr static WSDC::ConstStringColorMap<palette_size> Colors {
    #define DEFINE_NEW_COLOR(name, r, g, b) std::pair { std::string_view{name},\
                                            WSDC::Core::Color{static_cast<WSDC::Core::rgb_t>(r),\
                                                              static_cast<WSDC::Core::rgb_t>(g),\
                                                              static_cast<WSDC::Core::rgb_t>(b),\
                                                              static_cast<WSDC::Core::rgb_t>(255)}},
    std::array{
        #ifndef WSDC_BASIC_PALETTE
        #include "Core/__COLORS__.hpp"
        #else
        DEFINE_NEW_COLOR("White", 255, 255, 255)
        DEFINE_NEW_COLOR("Red", 255, 0, 0)
        DEFINE_NEW_COLOR("Green", 0, 255, 0)
        DEFINE_NEW_COLOR("Blue", 0, 0, 255)
        DEFINE_NEW_COLOR("Gray", 127, 127, 127)
        DEFINE_NEW_COLOR("Black", 0, 0, 0)
        #endif
    }
    #undef DEFINE_NEW_COLOR
};

namespace Display {
    using flags_t = Uint64;
    namespace Flags {
        #define DEFINE_NEW_FLAG(name, flag) const static WSDC::Display::flags_t name = ( flag )
        DEFINE_NEW_FLAG(NONE, 0);
        DEFINE_NEW_FLAG(FULLSCREEN, SDL_WINDOW_FULLSCREEN);
        DEFINE_NEW_FLAG(OPENGL, SDL_WINDOW_OPENGL);
        DEFINE_NEW_FLAG(OCCLUDED, SDL_WINDOW_OCCLUDED);
        DEFINE_NEW_FLAG(HIDDEN, SDL_WINDOW_HIDDEN);
        DEFINE_NEW_FLAG(BORDERLESS, SDL_WINDOW_BORDERLESS);
        DEFINE_NEW_FLAG(RESIZABLE, SDL_WINDOW_RESIZABLE);
        DEFINE_NEW_FLAG(MINIMIZED, SDL_WINDOW_MINIMIZED);
        DEFINE_NEW_FLAG(MAXIMIZED, SDL_WINDOW_MAXIMIZED);
        DEFINE_NEW_FLAG(MOUSE_GRABBED, SDL_WINDOW_MOUSE_GRABBED);
        DEFINE_NEW_FLAG(INPUT_FOCUS, SDL_WINDOW_INPUT_FOCUS);
        DEFINE_NEW_FLAG(MOUSE_FOCUS, SDL_WINDOW_MOUSE_FOCUS);
        DEFINE_NEW_FLAG(EXTERNAL, SDL_WINDOW_EXTERNAL);
        DEFINE_NEW_FLAG(MODAL, SDL_WINDOW_MODAL);
        DEFINE_NEW_FLAG(HIGH_PIXEL_DENSITY, SDL_WINDOW_HIGH_PIXEL_DENSITY);
        DEFINE_NEW_FLAG(MOUSE_CAPTURE, SDL_WINDOW_MOUSE_CAPTURE);
        DEFINE_NEW_FLAG(MOUSE_RELATIVE_MODE, SDL_WINDOW_MOUSE_RELATIVE_MODE);
        DEFINE_NEW_FLAG(ALWAYS_ON_TOP, SDL_WINDOW_ALWAYS_ON_TOP);
        DEFINE_NEW_FLAG(UTILITY, SDL_WINDOW_UTILITY);
        DEFINE_NEW_FLAG(TOOLTIP, SDL_WINDOW_TOOLTIP);
        DEFINE_NEW_FLAG(POPUP_MENU, SDL_WINDOW_POPUP_MENU);
        DEFINE_NEW_FLAG(KEYBOARD_GRABBED, SDL_WINDOW_KEYBOARD_GRABBED);
        #ifdef __EMSCRIPTEN__
        DEFINE_NEW_FLAG(FILL_DOCUMENT, SDL_WINDOW_FILL_DOCUMENT);
        #endif
        DEFINE_NEW_FLAG(VULKAN, SDL_WINDOW_VULKAN);
        DEFINE_NEW_FLAG(METAL, SDL_WINDOW_METAL);
        DEFINE_NEW_FLAG(INVISIBLE, SDL_WINDOW_TRANSPARENT);
        DEFINE_NEW_FLAG(NOT_FOCUSABLE, SDL_WINDOW_NOT_FOCUSABLE);
        #undef DEFINE_NEW_FLAG
    }

    struct SDL_VIDEO_Quitter {
        ~SDL_VIDEO_Quitter();
    };

    struct RawWindow {
        WSDC::Core::Size<int> size;
        WSDC::Core::Position<int> position;
        std::string title, renderer_name;
        SDL_WindowFlags flags{WSDC::Display::Flags::NONE};
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_AudioDeviceID audio_device;
        RawWindow() = default;
    };

    struct Window {
        WSDC::Display::Window& self = (*this);
        WSDC::Display::RawWindow raw;

        Window(void);
        ~Window(void);

        // set flags
        WSDC::Display::Window& flags(const SDL_WindowFlags&);
        WSDC::Display::Window& setFlag(const SDL_WindowFlags&, const bool&);
        WSDC::Display::Window& highPixelDensity(const bool&);
        WSDC::Display::Window& resizeable(const bool&);

        // configure without rebuilding
        template <typename T> WSDC::Display::Window& position(const WSDC::Core::Position<T>&);
        template <typename T> WSDC::Display::Window& size(const WSDC::Core::Size<T>&);
        WSDC::Display::Window& size(const float&, const float&, const SDL_DisplayID&);
        WSDC::Display::Window& size(const float&, const float&);

        // remount window with set configurations
        WSDC::Display::Window& build(void);

        // exit facilities
        WSDC::Display::Window& close(void);

        // use while running
        WSDC::Display::Window& update(void);
        WSDC::Display::Window& setTitle(const char*);
        WSDC::Display::Window& setIcon(const char*);
        WSDC::Display::Window& setVSync(const int&);
        template <class F, class... Args> [[maybe_unused]] inline WSDC::Display::Window& drawRaw(F&&, const WSDC::Core::Color&, Args...) const noexcept;
        template <class F, class... Args> [[maybe_unused]] inline WSDC::Display::Window& renderRaw(F&&, Args...) const noexcept;

        // get data
        float getWidth(const float&) const noexcept;
        float getHeight(const float&) const noexcept;
    };

    /*template <typename T>
    class SubWindowAllocator {
    public:
        using value_type = T;

        MyAllocator() noexcept {}

        T* allocate(std::size_t n) {
            return static_cast<T*>(::operator new(n * sizeof(T)));
        }

        void deallocate(T* p, std::size_t n) noexcept {
            ::operator delete(p);
        }
    };*/

    class SubWindows {
        // using SubWin_Allocator = std::vector<WSDC::Display::Window, WSDC::Display::SubWindowAllocator<WSDC::Display::Window>>;
        WSDC::Display::Window *_root_window = nullptr;
        // SubWin_Allocator _sub_windows;
    public:
        SubWindows() = default;
        ~SubWindows() = default;

        SubWindows(WSDC::Display::Window&) noexcept;
        SubWindows(WSDC::Display::Window*&) noexcept;
        SubWindows& root(WSDC::Display::Window&) noexcept;
        SubWindows& root(WSDC::Display::Window*&) noexcept;

        SubWindows& close_all() noexcept;
        SubWindows& update_all() noexcept;
    };
}

namespace Event {
    using flag_t = uint32_t;

    struct TouchFinger {
        float x, y;
        float dx, dy;
        float pressure;
    };

    // Mouse button flags
    enum class Mouse : WSDC::Event::flag_t {
        NONE = 0,
        LMB_DOWN = 1 << 0,
        LMB_UP = 1 << 1,
        RMB_DOWN = 1 << 2,
        RMB_UP = 1 << 3,
        MMB_DOWN = 1 << 4,
        MMB_UP = 1 << 5,
        X1_DOWN = 1 << 6,
        X1_UP = 1 << 7,
        X2_DOWN = 1 << 8,
        X2_UP = 1 << 9,
        MOTION = 1 << 10,
        WHEEL = 1 << 11,
        DEVICE_ADDED = 1 << 12,
        DEVICE_REMOVED = 1 << 13
    };

    // Window event flags
    enum class Window : WSDC::Event::flag_t {
        NONE = 0,
        CLOSE = 1 << 0,
        RESIZED = 1 << 1,
        MINIMIZED = 1 << 2,
        MAXIMIZED = 1 << 3,
        FOCUS_GAINED = 1 << 4,
        FOCUS_LOST = 1 << 5,
        SHOWN = 1 << 6,
        HIDDEN = 1 << 7,
        MOVED = 1 << 8,
        EXPOSED = 1 << 9,
        PIXEL_SIZE_CHANGED = 1 << 10,
        METAL_VIEW_RESIZED = 1 << 11,
        RESTORED = 1 << 12,
        MOUSE_ENTER = 1 << 13,
        MOUSE_LEAVE = 1 << 14,
        HIT_TEST = 1 << 15,
        ICCPROF_CHANGED = 1 << 16,
        DISPLAY_CHANGED = 1 << 17,
        DISPLAY_SCALE_CHANGED = 1 << 18,
        SAFE_AREA_CHANGED = 1 << 19,
        OCCLUDED = 1 << 20,
        ENTER_FULLSCREEN = 1 << 21,
        LEAVE_FULLSCREEN = 1 << 22,
        DESTROYED = 1 << 23
    };

    // System events
    enum class System : WSDC::Event::flag_t {
        NONE = 0,
        QUIT = 1 << 0,
        TERMINATING = 1 << 1,
        LOW_MEMORY = 1 << 2,
        WILL_ENTER_BACKGROUND = 1 << 3,
        DID_ENTER_BACKGROUND = 1 << 4,
        WILL_ENTER_FOREGROUND = 1 << 5,
        DID_ENTER_FOREGROUND = 1 << 6,
        LOCALE_CHANGED = 1 << 7,
        SYSTEM_THEME_CHANGED = 1 << 8
    };

    // Display events
    enum class Display : WSDC::Event::flag_t {
        NONE = 0,
        ORIENTATION = 1 << 0,
        ADDED = 1 << 1,
        REMOVED = 1 << 2,
        MOVED = 1 << 3,
        CONTENT_SCALE_CHANGED = 1 << 4
    };

    // Keyboard events
    enum class Keyboard : WSDC::Event::flag_t {
        NONE = 0,
        DEVICE_ADDED = 1 << 0,
        DEVICE_REMOVED = 1 << 1,
        TEXT_INPUT = 1 << 2,
        TEXT_EDITING = 1 << 3,
        TEXT_EDITING_CANDIDATES = 1 << 4
    };

    // Gamepad events
    enum class Gamepad : WSDC::Event::flag_t {
        NONE = 0,
        ADDED = 1 << 0,
        REMOVED = 1 << 1,
        REMAPPED = 1 << 2,
        UPDATE_COMPLETE = 1 << 3,
        STEAM_HANDLE_UPDATED = 1 << 4,
        AXIS_MOTION = 1 << 5,
        BUTTON_DOWN = 1 << 6,
        BUTTON_UP = 1 << 7,
        TOUCHPAD_DOWN = 1 << 8,
        TOUCHPAD_MOTION = 1 << 9,
        TOUCHPAD_UP = 1 << 10,
        SENSOR_UPDATE = 1 << 11
    };

    // Joystick events
    enum class Joystick : WSDC::Event::flag_t {
        NONE = 0,
        ADDED = 1 << 0,
        REMOVED = 1 << 1,
        UPDATE_COMPLETE = 1 << 2,
        AXIS_MOTION = 1 << 3,
        BALL_MOTION = 1 << 4,
        HAT_MOTION = 1 << 5,
        BUTTON_DOWN = 1 << 6,
        BUTTON_UP = 1 << 7,
        BATTERY_UPDATED = 1 << 8
    };

    // Touch events
    enum class Touch : WSDC::Event::flag_t {
        NONE = 0,
        FINGER_DOWN = 1 << 0,
        FINGER_UP = 1 << 1,
        FINGER_MOTION = 1 << 2
    };

    // Pen/Stylus events
    enum class Pen : WSDC::Event::flag_t {
        NONE = 0,
        PROXIMITY_IN = 1 << 0,
        PROXIMITY_OUT = 1 << 1,
        DOWN = 1 << 2,
        UP = 1 << 3,
        MOTION = 1 << 4,
        BUTTON_DOWN = 1 << 5,
        BUTTON_UP = 1 << 6,
        AXIS = 1 << 7
    };

    // Audio events
    enum class Audio : WSDC::Event::flag_t {
        NONE = 0,
        DEVICE_ADDED = 1 << 0,
        DEVICE_REMOVED = 1 << 1,
        DEVICE_FORMAT_CHANGED = 1 << 2
    };

    // Camera events
    enum class Camera : WSDC::Event::flag_t {
        NONE = 0,
        DEVICE_ADDED = 1 << 0,
        DEVICE_REMOVED = 1 << 1,
        DEVICE_APPROVED = 1 << 2,
        DEVICE_DENIED = 1 << 3
    };

    // Sensor events
    enum class Sensor : WSDC::Event::flag_t {
        NONE = 0,
        UPDATE = 1 << 0
    };

    // Render events
    enum class Render : WSDC::Event::flag_t {
        NONE = 0,
        TARGETS_RESET = 1 << 0,
        DEVICE_RESET = 1 << 1,
        DEVICE_LOST = 1 << 2
    };

    // Drop events (drag and drop)
    enum class Drop : WSDC::Event::flag_t {
        NONE = 0,
        BEGIN = 1 << 0,
        FILE = 1 << 1,
        TEXT = 1 << 2,
        COMPLETE = 1 << 3,
        POSITION = 1 << 4
    };

    // Clipboard events
    enum class Clipboard : WSDC::Event::flag_t {
        NONE = 0,
        UPDATE = 1 << 0
    };

    // User custom events
    enum class User : WSDC::Event::flag_t {
        NONE = 0,
        EVENT = 1 << 0
    };

    #define CAST(value) static_cast<WSDC::Event::flag_t>(value)
    #define EVENT_ANY (~(static_cast<WSDC::Event::flag_t>(0)))
    #define NEW_EVENT(EnumType, name, value) const static EnumType name = static_cast<EnumType>(value);
    NEW_EVENT(WSDC::Event::System, EXIT, CAST(WSDC::Event::System::QUIT) | CAST(WSDC::Event::System::TERMINATING))
    NEW_EVENT(WSDC::Event::Mouse, Mouse_DOWN, CAST(WSDC::Event::Mouse::LMB_DOWN) | CAST(WSDC::Event::Mouse::RMB_DOWN) | CAST(WSDC::Event::Mouse::MMB_DOWN) | CAST(WSDC::Event::Mouse::X1_DOWN) | CAST(WSDC::Event::Mouse::X2_DOWN))
    NEW_EVENT(WSDC::Event::Mouse, Mouse_UP, CAST(WSDC::Event::Mouse::LMB_UP) | CAST(WSDC::Event::Mouse::RMB_UP) | CAST(WSDC::Event::Mouse::MMB_UP) | CAST(WSDC::Event::Mouse::X1_UP) | CAST(WSDC::Event::Mouse::X2_UP))
    NEW_EVENT(WSDC::Event::Mouse, Mouse_ANY, EVENT_ANY)
    NEW_EVENT(WSDC::Event::Window, Window_ANY, EVENT_ANY)
    NEW_EVENT(WSDC::Event::System, System_ANY, EVENT_ANY)
    NEW_EVENT(WSDC::Event::Display, Display_ANY, EVENT_ANY)
    NEW_EVENT(WSDC::Event::Keyboard, Keyboard_ANY, EVENT_ANY)
    NEW_EVENT(WSDC::Event::Gamepad, Gamepad_ANY, EVENT_ANY)
    NEW_EVENT(WSDC::Event::Joystick, Joystick_ANY, EVENT_ANY)
    NEW_EVENT(WSDC::Event::Touch, Touch_ANY, EVENT_ANY)
    NEW_EVENT(WSDC::Event::Pen, Pen_ANY, EVENT_ANY)
    NEW_EVENT(WSDC::Event::Audio, Audio_ANY, EVENT_ANY)
    NEW_EVENT(WSDC::Event::Camera, Camera_ANY, EVENT_ANY)
    NEW_EVENT(WSDC::Event::Sensor, Sensor_ANY, EVENT_ANY)
    NEW_EVENT(WSDC::Event::Render, Render_ANY, EVENT_ANY)
    NEW_EVENT(WSDC::Event::Drop, Drop_ANY, EVENT_ANY)
    NEW_EVENT(WSDC::Event::Clipboard, Clipboard_ANY, EVENT_ANY)
    NEW_EVENT(WSDC::Event::User, User_ANY, EVENT_ANY)
    #undef NEW_EVENT
    #undef EVENT_ANY
    #undef CAST
}

// Bitwise operators for all flag enums
#define DEFINE_FLAG_OPERATORS(EnumType) \
inline EnumType operator|(EnumType a, EnumType b) noexcept { \
    return static_cast<EnumType>(static_cast<WSDC::Event::flag_t>(a) | static_cast<WSDC::Event::flag_t>(b)); \
} \
inline EnumType operator&(EnumType a, EnumType b) noexcept { \
    return static_cast<EnumType>(static_cast<WSDC::Event::flag_t>(a) & static_cast<WSDC::Event::flag_t>(b)); \
} \
inline EnumType& operator|=(EnumType& a, EnumType b) noexcept { \
    return a = a | b; \
} \
inline EnumType& operator&=(EnumType& a, EnumType b) noexcept { \
    return a = a & b; \
}

DEFINE_FLAG_OPERATORS(WSDC::Event::Mouse)
DEFINE_FLAG_OPERATORS(WSDC::Event::Window)
DEFINE_FLAG_OPERATORS(WSDC::Event::System)
DEFINE_FLAG_OPERATORS(WSDC::Event::Display)
DEFINE_FLAG_OPERATORS(WSDC::Event::Keyboard)
DEFINE_FLAG_OPERATORS(WSDC::Event::Gamepad)
DEFINE_FLAG_OPERATORS(WSDC::Event::Joystick)
DEFINE_FLAG_OPERATORS(WSDC::Event::Touch)
DEFINE_FLAG_OPERATORS(WSDC::Event::Pen)
DEFINE_FLAG_OPERATORS(WSDC::Event::Audio)
DEFINE_FLAG_OPERATORS(WSDC::Event::Camera)
DEFINE_FLAG_OPERATORS(WSDC::Event::Sensor)
DEFINE_FLAG_OPERATORS(WSDC::Event::Render)
DEFINE_FLAG_OPERATORS(WSDC::Event::Drop)
DEFINE_FLAG_OPERATORS(WSDC::Event::Clipboard)
DEFINE_FLAG_OPERATORS(WSDC::Event::User)

#undef DEFINE_FLAG_OPERATORS

namespace Entity {
    class Button;
}

namespace Draw {
    void clearScreen(SDL_Renderer*&, const WSDC::Core::Color&);
    void clearScreen(SDL_Window*&, const WSDC::Core::Color&);

    struct TextureWrapper {
        SDL_Texture* ref;

        TextureWrapper(SDL_Texture*);
        void destroy();
        ~TextureWrapper();
        SDL_Texture* operator&(void) noexcept;
    };

    struct SDL_SurfaceWrapper {
        SDL_Surface* ref;

        SDL_SurfaceWrapper(SDL_Surface*);
        void destroy();
        ~SDL_SurfaceWrapper();
        SDL_Surface* operator&(void) noexcept;
        bool operator!(void) const noexcept;
        bool okay(void) const noexcept;
    };

    class Image {
        const std::string base_path;
        WSDC::Draw::SDL_SurfaceWrapper surface;
        std::string filepath;
        std::string extension;
        int width;
        int height;
        bool loaded;
        
        mutable SDL_Texture* cached_texture;
        mutable SDL_Renderer* cached_renderer;

        std::string getExtension(const std::string&);
        std::string getFullPath(const std::string&) const;
        void clearTextureCache();

    public:
        Image();
        Image(SDL_Surface*);
        Image(const std::string&);
        ~Image();

        bool load(const std::string&); // Load image from file
        void free(); // Free the surface and cached texture
        SDL_Surface* getSurface() const; // Get as SDL_Surface (CPU memory) - returns the internal surface

        /* Get as SDL_Texture (GPU memory) - CACHED version
           Returns cached texture if available for the same renderer */
        SDL_Texture* getTexture(SDL_Renderer*) const;
        SDL_Texture* recreateTexture(SDL_Renderer*); // Force recreate texture (useful if surface was modified)
        WSDC::Draw::TextureWrapper loadAsTexture(SDL_Renderer*&, const std::string&); // Load directly as texture (more efficient if you don't need the surface)
        WSDC::Draw::SDL_SurfaceWrapper getScaledSurface(int, int, SDL_ScaleMode) const; // Get scaled surface
        WSDC::Draw::SDL_SurfaceWrapper convertSurface(SDL_PixelFormat) const; // Convert surface to different pixel format
        
        void* getPixels() const; // Get raw pixel data
        int getPitch() const; // Get pitch (bytes per row)
        SDL_PixelFormat getFormat() const; // Get pixel format

        bool blitTo(SDL_Surface*, const SDL_Rect*, SDL_Rect*) const; // Blit to another surface
        bool blitScaledTo(SDL_Surface*, const SDL_Rect*, SDL_Rect*, SDL_ScaleMode) const;

        bool saveBMP(const std::string&) const;

        int getWidth() const;
        int getHeight() const;
        bool isLoaded() const;

        std::string getFilepath() const;
        std::string getExtension() const;
        std::string getBasePath() const;

        bool setColorMod(Uint8, Uint8, Uint8);
        bool getColorMod(Uint8*&, Uint8*&, Uint8*&);
        WSDC::Core::Color getColorMod();

        bool setAlphaMod(Uint8);
        bool getAlphaMod(Uint8*&) const;

        bool setBlendMode(SDL_BlendMode);
        bool getBlendMode(SDL_BlendMode*&) const;

        // Lock surface for direct pixel access
        bool lock();
        void unlock();

        WSDC::Draw::Image crop(const WSDC::Geo::Rect<int>& rect) const;
    };

    class SpriteSheet {
        WSDC::Draw::Image _sprite_sheet;
        WSDC::Core::Size<int> _offset;
        WSDC::Core::Size<int> _separation;
        WSDC::Core::Size<int> _sprite_size;

    public:
        // configuration
        SpriteSheet& offset(const int&, const int&) noexcept;
        SpriteSheet& separator(const int&, const int&) noexcept;
        SpriteSheet& size(const int&, const int&) noexcept;

        // handle sheet
        SpriteSheet& load(const char*);

        std::optional<WSDC::Draw::Image> operator()(const int&, const int&) const;
    };
}

namespace Types {
    template<typename T> using Size = WSDC::Core::Size<T>;
    template<typename T> using Position = WSDC::Core::Position<T>;
    using Color = WSDC::Core::Color;
    using index_t = uint64_t;
}

namespace Text {
    using Alignment = TTF_HorizontalAlignment;
    namespace Align {
        #define DEFINE_NEW_ALIGNMENT(n, v) constexpr static WSDC::Text::Alignment n = v;
        DEFINE_NEW_ALIGNMENT(LEFT,   TTF_HORIZONTAL_ALIGN_LEFT)
        DEFINE_NEW_ALIGNMENT(CENTER, TTF_HORIZONTAL_ALIGN_CENTER)
        DEFINE_NEW_ALIGNMENT(RIGHT,  TTF_HORIZONTAL_ALIGN_RIGHT)
        DEFINE_NEW_ALIGNMENT(NONE,   TTF_HORIZONTAL_ALIGN_INVALID)
        #undef DEFINE_NEW_ALIGNMENT
    }

    using Weight = uint32_t;
    enum class Weights : WSDC::Text::Weight {
        THIN      = TTF_FONT_WEIGHT_THIN,
        LIGHTER   = TTF_FONT_WEIGHT_EXTRA_LIGHT,
        LIGHT     = TTF_FONT_WEIGHT_LIGHT,
        NORMAL    = TTF_FONT_WEIGHT_NORMAL,
        MEDIUM    = TTF_FONT_WEIGHT_MEDIUM,
        SEMI_BOLD = TTF_FONT_WEIGHT_SEMI_BOLD,
        BOLD      = TTF_FONT_WEIGHT_BOLD,
        BOLDER    = TTF_FONT_WEIGHT_EXTRA_BOLD,
        EXTRA     = TTF_FONT_WEIGHT_BLACK,
        GIGA      = TTF_FONT_WEIGHT_EXTRA_BLACK
    };

    using Style = TTF_FontStyleFlags;
    enum class Styles : WSDC::Text::Weight {
        NORMAL    = TTF_STYLE_NORMAL,
        BOLD      = TTF_STYLE_BOLD,
        ITALIC    = TTF_STYLE_ITALIC,
        UNDERLINE = TTF_STYLE_UNDERLINE,
        STRIKE    = TTF_STYLE_STRIKETHROUGH
    };

    struct FontStyle {
        float size;
        WSDC::Text::Weights weight;
        WSDC::Text::Styles style;
        WSDC::Text::Alignment align;
        WSDC::Core::Color color;

        FontStyle();

        // cache comparison
        bool operator==(const FontStyle&) const;
        bool operator!=(const FontStyle&) const;
        
        // Helper
        static FontStyle withSize(float s);
        static FontStyle withColor(const WSDC::Core::Color&);
        static FontStyle withWeight(const WSDC::Text::Weights&);
        
        // Preset styles
        static FontStyle heading();
        static FontStyle subheading();
        static FontStyle body();
        static FontStyle small();
        
        // chaining
        FontStyle& setSize(float s);
        FontStyle& setColor(const WSDC::Core::Color&);
        FontStyle& setWeight(const WSDC::Text::Weights&);
        FontStyle& setStyle(const WSDC::Text::Styles&);
        FontStyle& setAlign(const WSDC::Text::Alignment&);
    };

    struct CachedText {
        SDL_Surface* surface;
        SDL_Texture* texture;
        SDL_Renderer* renderer;
        std::string text;
        WSDC::Text::FontStyle style;
        int actual_width;
        int actual_height;
        
        CachedText();
        ~CachedText();
        void clear();
        bool matches(const std::string&, const WSDC::Text::FontStyle&, SDL_Renderer*) const;
    };

    class Font {
        TTF_Font* raw = nullptr;
        std::string _filepath;
        WSDC::Text::FontStyle _style;
        
        mutable WSDC::Text::CachedText cache;

        void prepareContext(SDL_Renderer*&, SDL_Surface*&, SDL_Texture*&, const std::string&, int&, int&);
        void clearCache();
        void applyStyesToFont();

    public:
        friend class WSDC::Entity::Button;
        
        Font(void);
        ~Font(void);

        WSDC::Text::Font& close(void);
        WSDC::Text::Font& unload(void);

        WSDC::Text::Font& color(const WSDC::Core::Color&);
        WSDC::Core::Color& color(void);

        WSDC::Text::Font& size(const float& size);
        float& size(void);

        WSDC::Text::Font& weight(const WSDC::Text::Weights&);
        WSDC::Text::Weights& weight(void);

        WSDC::Text::Font& style(const WSDC::Text::Styles&);
        WSDC::Text::Styles& style(void);

        WSDC::Text::Font& align(const WSDC::Text::Alignment&);

        WSDC::Text::Font& load(const std::string&);
        std::string& filepath(void);

        WSDC::Text::Font& styles(const WSDC::Text::FontStyle&);
        WSDC::Text::FontStyle& styles(void);

        [[maybe_unused]] SDL_FRect write(SDL_Renderer*, const WSDC::Core::Position<float>&, const std::string&);
        template<typename... Args> [[maybe_unused]] SDL_FRect write(SDL_Renderer*, const WSDC::Core::Position<float>&, const std::string&, Args...);
        
        // Get text dimensions without rendering
        SDL_FRect measureText(const std::string&);
        
        // Get font height
        int getHeight() const;
        
        // Get font ascent
        int getAscent() const;
        
        // Get font descent
        int getDescent() const;
        
        // Check if font is loaded
        bool isLoaded() const;
        
        // Force cache clear
        WSDC::Text::Font& invalidateCache();
    };

    struct TTF_Quitter {
        ~TTF_Quitter();
    };
}

namespace Managers {
    class Events {
        uint32_t mouse_flags    = 0, window_flags  = 0, system_flags    = 0, display_flags = 0,
                 keyboard_flags = 0, gamepad_flags = 0, joystick_flags  = 0, touch_flags   = 0,
                 pen_flags      = 0, audio_flags   = 0, camera_flags    = 0, sensor_flags  = 0,
                 render_flags   = 0, drop_flags    = 0, clipboard_flags = 0, user_flags    = 0;
        
        // Keyboard state
        const bool* key_states = nullptr;
        std::unordered_set<SDL_Scancode> keys_pressed_this_frame;
        std::unordered_set<SDL_Scancode> keys_released_this_frame;
        
        // Mouse state
        float mouse_x = 0, mouse_y = 0;
        float mouse_dx = 0, mouse_dy = 0;
        float wheel_x = 0, wheel_y = 0;
        uint32_t mouse_button_state = 0;
        
        // Window state
        int window_width = 0, window_height = 0;
        SDL_WindowID window_id = 0;
        
        // Display state
        SDL_DisplayID display_id = 0;
        SDL_DisplayOrientation display_orientation = SDL_ORIENTATION_UNKNOWN;
        
        // Gamepad state
        std::unordered_map<SDL_JoystickID, SDL_GamepadAxis> gamepad_axes;
        std::unordered_map<SDL_JoystickID, SDL_GamepadButton> gamepad_buttons;
        std::unordered_set<SDL_JoystickID> active_gamepads;
        
        // Joystick state
        std::unordered_map<SDL_JoystickID, int> joystick_axes;
        std::unordered_map<SDL_JoystickID, int> joystick_buttons;
        std::unordered_set<SDL_JoystickID> active_joysticks;
        
        // Touch state
        std::unordered_map<SDL_FingerID, WSDC::Event::TouchFinger> touch_fingers;
        
        // Pen state
        float pen_x = 0, pen_y = 0;
        float pen_pressure = 0;
        float pen_tilt_x = 0, pen_tilt_y = 0;
        SDL_PenID pen_id = 0;
        
        // Text input
        std::string text_input;
        std::string text_editing;
        
        // Drop state
        std::vector<std::string> dropped_files;
        std::string dropped_text;
        float drop_x = 0, drop_y = 0;
        
        // Sensor state
        std::vector<float> sensor_data;
        
        // Audio state
        SDL_AudioDeviceID audio_device_id = 0;
        
        // Camera state
        SDL_CameraID camera_device_id = 0;
        
        // User event state
        void* user_data1 = nullptr;
        void* user_data2 = nullptr;
        int32_t user_code = 0;

    public:
        WSDC::Managers::Events& update();
        
        // Operator overloads for flag checking
        bool operator&(WSDC::Event::Mouse) const;
        bool operator&(WSDC::Event::Window) const;
        bool operator&(WSDC::Event::System) const;
        bool operator&(WSDC::Event::Display) const;
        bool operator&(WSDC::Event::Keyboard) const;
        bool operator&(WSDC::Event::Gamepad) const;
        bool operator&(WSDC::Event::Joystick) const;
        bool operator&(WSDC::Event::Touch) const;
        bool operator&(WSDC::Event::Pen) const;
        bool operator&(WSDC::Event::Audio) const;
        bool operator&(WSDC::Event::Camera) const;
        bool operator&(WSDC::Event::Sensor) const;
        bool operator&(WSDC::Event::Render) const;
        bool operator&(WSDC::Event::Drop) const;
        bool operator&(WSDC::Event::Clipboard) const;
        bool operator&(WSDC::Event::User) const;
        template <class EV> bool isEvent(EV);
        
        // Keyboard queries
        bool isKeyHeld(SDL_Scancode sc) const;
        bool isKeyPressed(SDL_Scancode sc) const;
        bool isKeyReleased(SDL_Scancode sc) const;
        
        // Mouse state
        float mouseX() const;
        float mouseY() const;
        WSDC::Core::Position<float> mouse() const;
        float mouseDX() const;
        float mouseDY() const;
        WSDC::Core::Position<float> mouseDelta() const;
        float wheelX() const;
        float wheelY() const;
        WSDC::Core::Position<float> wheel() const;
        uint32_t mouseButtonState() const;
        
        // Window state
        int windowWidth() const;
        int windowHeight() const;
        WSDC::Core::Size<int> window() const;
        SDL_WindowID windowID() const;
        
        // Display state
        SDL_DisplayID displayID() const;
        SDL_DisplayOrientation displayOrientation() const;
        
        // Text input
        const std::string& textInput() const;
        const std::string& textEditing() const;
        
        // Touch state
        const std::unordered_map<SDL_FingerID, WSDC::Event::TouchFinger>& touchFingers() const;
        
        // Pen state
        float penX() const;
        float penY() const;
        WSDC::Core::Position<float> pen() const;
        float penPressure() const;
        float penTiltX() const;
        float penTiltY() const;
        WSDC::Core::Position<float> penTilt() const;
        SDL_PenID penID() const;
        
        // Gamepad state
        const std::unordered_set<SDL_JoystickID>& activeGamepads() const;
        
        // Joystick state
        const std::unordered_set<SDL_JoystickID>& activeJoysticks() const;
        
        // Drop state
        const std::vector<std::string>& droppedFiles() const;
        const std::string& droppedText() const;
        float dropX() const;
        float dropY() const;
        WSDC::Core::Position<float> drop() const;
        
        // Sensor state
        const std::vector<float>& sensorData() const;
        
        // Audio state
        SDL_AudioDeviceID audioDeviceID() const;
        
        // Camera state
        SDL_CameraID cameraDeviceID() const;
        
        // User event state
        void* userData1() const;
        void* userData2() const;
        int32_t userCode() const;
    };

    template <class... Others>
    class Scene {
        using scene_raw_t = std::function<void(WSDC::Display::Window&, WSDC::Managers::Events&, Others&...)>;
        scene_raw_t scene;

    public:
        Scene(const scene_raw_t&);
        Scene() = default;
        ~Scene() = default;

        scene_raw_t& get();
        scene_raw_t& operator*(void);

        Scene& run(WSDC::Display::Window&, WSDC::Managers::Events&, Others&...);

        Scene& operator=(const scene_raw_t&);
    };

    template <class Key=std::string, class... ExtraData>
    class SceneManager {
        using sig_function_t = std::function<void(WSDC::Display::Window&, ExtraData&...)>;
        using SceneW = WSDC::Managers::Scene<ExtraData&...>;
        using ExtraDataTuple = std::tuple<ExtraData*...>;

        std::map<Key, SceneW> scenes;
        std::map<Key, sig_function_t> on_change;

        SceneW* current_scene;
        WSDC::Display::Window* current_window;
        WSDC::Managers::Events* current_events;
        ExtraDataTuple current_outdata;

    public:
        SceneManager() : current_scene(nullptr), current_window(nullptr), 
                        current_events(nullptr), current_outdata() {}
        ~SceneManager() {}

        SceneW& createScene(const Key&, const bool&);
        SceneW& createScene(const Key&);
        SceneW& scene(const Key&);
        SceneW& createSceneWithSignal(const Key&, const bool&, const sig_function_t&);
        SceneW& createSceneWithSignal(const Key&, const sig_function_t&);
        SceneW& sceneWithSignal(const Key&, const bool&, const sig_function_t&);
        
        SceneManager<Key, ExtraData...>& extra(ExtraData&...);
        SceneManager<Key, ExtraData...>& window(WSDC::Display::Window&);
        SceneManager<Key, ExtraData...>& events(WSDC::Managers::Events&);
        
        void changeTo(const Key&);
        sig_function_t& onChangeTo(const Key&);

        SceneManager<Key, ExtraData...>& run();

    private:
        template<std::size_t... Is>
        void callOnChange(const Key& key, std::index_sequence<Is...>) {
            on_change[key](*current_window, *std::get<Is>(current_outdata)...);
        }

        template<std::size_t... Is>
        void callSceneRun(std::index_sequence<Is...>) {
            current_scene->run(*current_window, *current_events, *std::get<Is>(current_outdata)...);
        }
    };

    class TextRenderer {
        std::unordered_map<std::string, WSDC::Text::Font> fonts;
        SDL_Renderer* _renderer;
        
    public:
        TextRenderer& renderer(SDL_Renderer*&);
        WSDC::Text::Font& operator[](const std::string&);
        [[maybe_unused]] SDL_FRect write(const std::string&, const WSDC::Core::Position<float>&, const std::string&);
        template<typename... Args> [[maybe_unused]] SDL_FRect write(const std::string& f, const WSDC::Core::Position<float>&, const std::string&, Args...);
    };
}

namespace Entity {
    class Button : public WSDC::Geo::Rect<float> {
        bool _use_text, _use_bg_image, _is_in_area,
             _last_check, _last_click_state;
        WSDC::Core::Color _bg, _fg;
        WSDC::Text::Font* _font;
        WSDC::Draw::Image* _img;
        SDL_FRect _prect;

    public:
        std::function<void(void)> onClick, onRelease, onHover, onLeave;

        Button();
        ~Button();

        WSDC::Entity::Button& set(const WSDC::Geo::Rect<float>&);
        WSDC::Entity::Button& useText(const bool&) noexcept;
        WSDC::Entity::Button& useImg(const bool&) noexcept;
        WSDC::Entity::Button& font(WSDC::Text::Font&) noexcept;
        WSDC::Entity::Button& font(WSDC::Text::Font*&) noexcept;

        WSDC::Draw::Image& img(const std::string&) noexcept;
        WSDC::Draw::Image& img();

        WSDC::Core::Color& bg() noexcept;
        WSDC::Entity::Button& bg(const WSDC::Core::Color&) noexcept;

        WSDC::Core::Color& fg() noexcept;
        WSDC::Entity::Button& fg(const WSDC::Core::Color&) noexcept;

        bool isAlignedHorizontal(const SDL_FRect&) noexcept;
        bool isAlignedVertical(const SDL_FRect&) noexcept;
        bool isInArea(const SDL_FRect&) noexcept;

        void check(const WSDC::Core::Position<float>, const bool&);

        void render(SDL_Renderer*&, const std::string&);
    };
}

namespace Format {
    template<std::size_t, typename... Ts> std::variant<Ts...> tuple_runtime_get(std::size_t, const std::tuple<Ts...>&);
    template<typename T> constexpr std::string to_string_any(const T&);
    template<typename... Types> constexpr std::string format(const std::string&, const Types&...);
    inline std::string format(const std::string&) noexcept;
    template<typename... Args> void format_p(std::string&, Args...);
}

namespace Log {
    using Style = uint8_t;
    namespace Styles {}

    struct TextStyle {
        WSDC::Core::Color  *fg = nullptr,
                           *bg = nullptr;
        WSDC::Log::Style style = 0;
        
        bool has(const WSDC::Log::Style& s) const;
    };

    std::string style_to_esc(const WSDC::Log::TextStyle&);
    inline std::string toLink(const std::string&);
    inline std::string toLink(const std::string&, const std::string&);
    inline std::string toLink(WSDC::Log::TextStyle&&, const std::string&, const std::string&);
    inline std::string toLink(WSDC::Log::TextStyle&&, const std::string&);
    void print(const std::string&);
    void println(const std::string&);
    void print(WSDC::Log::TextStyle&&, const std::string&);
    void println(TextStyle&&, const std::string&);
    template<typename... Args> void print(TextStyle&&, const std::string&, Args...);
    template<typename... Args> void println(TextStyle&&, const std::string&, Args...);
    template<typename... Args> void print(const std::string&, Args...);
    template<typename... Args> void println(const std::string&, Args...);
    void setPointerPosition(const int32_t&, const int32_t&);
    void setPointerPosition(const WSDC::Core::Position<int32_t>&);
    void clear();
}

template <class Key=std::string, class... ExtraData>
struct Engine {
    using Manager = WSDC::Managers::SceneManager<Key, WSDC::Display::SubWindows, WSDC::Managers::TextRenderer, ExtraData...>;
    using ExtraDataTuple = std::tuple<ExtraData*...>;
    using CONFIG = Engine<Key, ExtraData...>;

    struct SceneDefinition {
        Key name;
        bool _default = false;
    };

    bool use_onEvents = true;
    Uint64 FPS = 16; // ~60
    Uint64 last_frame_time = 0;
    WSDC::Display::SubWindows sub_windows;
    Manager manager;
    WSDC::Managers::Events events;
    std::atomic_bool is_running;
    ExtraDataTuple extra_data;
    WSDC::Display::Window display;
    WSDC::Managers::TextRenderer text;
    Engine();
    ~Engine();

    void isRunning(const bool&) noexcept;
    bool isRunning(void) noexcept;

    template <typename... Args>
    void write(const std::string&, const WSDC::Geo::Rect<int>&, const std::string&, Args...);

    void fps(const float&) noexcept;

    void set_extra(ExtraData&...);

    // ==================== WINDOW EVENTS ====================
    virtual void onWindowShown(); // SDL_EVENT_WINDOW_SHOWN
    virtual void onWindowHidden(); // SDL_EVENT_WINDOW_HIDDEN
    virtual void onWindowExposed(); // SDL_EVENT_WINDOW_EXPOSED
    virtual void onWindowMoved(); // SDL_EVENT_WINDOW_MOVED
    virtual void onWindowResized(); // SDL_EVENT_WINDOW_RESIZED
    virtual void onWindowPixelSizeChanged(); // SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED
    virtual void onWindowMetalViewResized(); // SDL_EVENT_WINDOW_METAL_VIEW_RESIZED
    virtual void onWindowMinimized(); // SDL_EVENT_WINDOW_MINIMIZED
    virtual void onWindowMaximized(); // SDL_EVENT_WINDOW_MAXIMIZED
    virtual void onWindowRestored(); // SDL_EVENT_WINDOW_RESTORED
    virtual void onWindowMouseEnter(); // SDL_EVENT_WINDOW_MOUSE_ENTER
    virtual void onWindowMouseLeave(); // SDL_EVENT_WINDOW_MOUSE_LEAVE
    virtual void onWindowFocusGained(); // SDL_EVENT_WINDOW_FOCUS_GAINED
    virtual void onWindowFocusLost(); // SDL_EVENT_WINDOW_FOCUS_LOST
    virtual void onWindowCloseRequested(); // SDL_EVENT_WINDOW_CLOSE_REQUESTED
    virtual void onWindowHitTest(); // SDL_EVENT_WINDOW_HIT_TEST
    virtual void onWindowICCProfChanged(); // SDL_EVENT_WINDOW_ICCPROF_CHANGED
    virtual void onWindowDisplayChanged(); // SDL_EVENT_WINDOW_DISPLAY_CHANGED
    virtual void onWindowDisplayScaleChanged(); // SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED
    virtual void onWindowSafeAreaChanged(); // SDL_EVENT_WINDOW_SAFE_AREA_CHANGED
    virtual void onWindowOccluded(); // SDL_EVENT_WINDOW_OCCLUDED
    virtual void onWindowEnterFullscreen(); // SDL_EVENT_WINDOW_ENTER_FULLSCREEN
    virtual void onWindowLeaveFullscreen(); // SDL_EVENT_WINDOW_LEAVE_FULLSCREEN
    virtual void onWindowDestroyed(); // SDL_EVENT_WINDOW_DESTROYED
    virtual void onWindowPenEnter(); // SDL_EVENT_WINDOW_PEN_ENTER
    virtual void onWindowPenLeave(); // SDL_EVENT_WINDOW_PEN_LEAVE

    // ==================== DISPLAY EVENTS ====================
    virtual void onDisplayOrientation(); // SDL_EVENT_DISPLAY_ORIENTATION
    virtual void onDisplayAdded(); // SDL_EVENT_DISPLAY_ADDED
    virtual void onDisplayRemoved(); // SDL_EVENT_DISPLAY_REMOVED
    virtual void onDisplayMoved(); // SDL_EVENT_DISPLAY_MOVED
    virtual void onDisplayContentScaleChanged(); // SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED

    // ==================== KEYBOARD EVENTS ====================
    virtual void onKeyboardAdded(); // SDL_EVENT_KEYBOARD_ADDED
    virtual void onKeyboardRemoved(); // SDL_EVENT_KEYBOARD_REMOVED
    virtual void onKeyDown(); // SDL_EVENT_KEY_DOWN
    virtual void onKeyUp(); // SDL_EVENT_KEY_UP

    // ==================== TEXT INPUT EVENTS ====================
    virtual void onTextEditing(); // SDL_EVENT_TEXT_EDITING
    virtual void onTextEditingCandidates(); // SDL_EVENT_TEXT_EDITING_CANDIDATES
    virtual void onTextInput(); // SDL_EVENT_TEXT_INPUT

    // ==================== MOUSE EVENTS ====================
    virtual void onMouseAdded(); // SDL_EVENT_MOUSE_ADDED
    virtual void onMouseRemoved(); // SDL_EVENT_MOUSE_REMOVED
    virtual void onMouseMotion(); // SDL_EVENT_MOUSE_MOTION
    virtual void onMouseButtonDown(); // SDL_EVENT_MOUSE_BUTTON_DOWN
    virtual void onMouseButtonUp(); // SDL_EVENT_MOUSE_BUTTON_UP
    virtual void onMouseWheel(); // SDL_EVENT_MOUSE_WHEEL

    // ==================== JOYSTICK EVENTS ====================
    virtual void onJoystickAdded(); // SDL_EVENT_JOYSTICK_ADDED
    virtual void onJoystickRemoved(); // SDL_EVENT_JOYSTICK_REMOVED
    virtual void onJoystickUpdateComplete(); // SDL_EVENT_JOYSTICK_UPDATE_COMPLETE
    virtual void onJoystickAxisMotion(); // SDL_EVENT_JOYSTICK_AXIS_MOTION
    virtual void onJoystickBallMotion(); // SDL_EVENT_JOYSTICK_BALL_MOTION
    virtual void onJoystickHatMotion(); // SDL_EVENT_JOYSTICK_HAT_MOTION
    virtual void onJoystickButtonDown(); // SDL_EVENT_JOYSTICK_BUTTON_DOWN
    virtual void onJoystickButtonUp(); // SDL_EVENT_JOYSTICK_BUTTON_UP
    virtual void onJoystickBatteryUpdated(); // SDL_EVENT_JOYSTICK_BATTERY_UPDATED

    // ==================== GAMEPAD EVENTS ====================
    virtual void onGamepadAdded(); // SDL_EVENT_GAMEPAD_ADDED
    virtual void onGamepadRemoved(); // SDL_EVENT_GAMEPAD_REMOVED
    virtual void onGamepadRemapped(); // SDL_EVENT_GAMEPAD_REMAPPED
    virtual void onGamepadUpdateComplete(); // SDL_EVENT_GAMEPAD_UPDATE_COMPLETE
    virtual void onGamepadSteamHandleUpdated(); // SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED
    virtual void onGamepadAxisMotion(); // SDL_EVENT_GAMEPAD_AXIS_MOTION
    virtual void onGamepadButtonDown(); // SDL_EVENT_GAMEPAD_BUTTON_DOWN
    virtual void onGamepadButtonUp(); // SDL_EVENT_GAMEPAD_BUTTON_UP
    virtual void onGamepadTouchpadDown(); // SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN
    virtual void onGamepadTouchpadMotion(); // SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION
    virtual void onGamepadTouchpadUp(); // SDL_EVENT_GAMEPAD_TOUCHPAD_UP
    virtual void onGamepadSensorUpdate(); // SDL_EVENT_GAMEPAD_SENSOR_UPDATE

    // ==================== AUDIO EVENTS ====================
    virtual void onAudioDeviceAdded(); // SDL_EVENT_AUDIO_DEVICE_ADDED
    virtual void onAudioDeviceRemoved(); // SDL_EVENT_AUDIO_DEVICE_REMOVED
    virtual void onAudioDeviceFormatChanged(); // SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED

    // ==================== CAMERA EVENTS ====================
    virtual void onCameraDeviceAdded(); // SDL_EVENT_CAMERA_DEVICE_ADDED
    virtual void onCameraDeviceRemoved(); // SDL_EVENT_CAMERA_DEVICE_REMOVED
    virtual void onCameraDeviceApproved(); // SDL_EVENT_CAMERA_DEVICE_APPROVED
    virtual void onCameraDeviceDenied(); // SDL_EVENT_CAMERA_DEVICE_DENIED

    // ==================== SENSOR EVENTS ====================
    virtual void onSensorUpdate(); // SDL_EVENT_SENSOR_UPDATE

    // ==================== TOUCH EVENTS ====================
    virtual void onFingerDown(); // SDL_EVENT_FINGER_DOWN
    virtual void onFingerUp(); // SDL_EVENT_FINGER_UP
    virtual void onFingerMotion(); // SDL_EVENT_FINGER_MOTION

    // ==================== GESTURE EVENTS ====================
    virtual void onPinchBegin(); // SDL_EVENT_PINCH_BEGIN
    virtual void onPinchRotate(); // SDL_EVENT_PINCH_ROTATE
    virtual void onPinchEnd(); // SDL_EVENT_PINCH_END

    // ==================== PEN EVENTS ====================
    virtual void onPenProximityIn(); // SDL_EVENT_PEN_PROXIMITY_IN
    virtual void onPenProximityOut(); // SDL_EVENT_PEN_PROXIMITY_OUT
    virtual void onPenDown(); // SDL_EVENT_PEN_DOWN
    virtual void onPenUp(); // SDL_EVENT_PEN_UP
    virtual void onPenMotion(); // SDL_EVENT_PEN_MOTION
    virtual void onPenButtonDown(); // SDL_EVENT_PEN_BUTTON_DOWN
    virtual void onPenButtonUp(); // SDL_EVENT_PEN_BUTTON_UP
    virtual void onPenAxis(); // SDL_EVENT_PEN_AXIS

    // ==================== RENDER EVENTS ====================
    virtual void onRenderTargetsReset(); // SDL_EVENT_RENDER_TARGETS_RESET
    virtual void onRenderDeviceReset(); // SDL_EVENT_RENDER_DEVICE_RESET
    virtual void onRenderDeviceLost(); // SDL_EVENT_RENDER_DEVICE_LOST

    // ==================== DROP EVENTS ====================
    virtual void onDropBegin(); // SDL_EVENT_DROP_BEGIN
    virtual void onDropFile(); // SDL_EVENT_DROP_FILE
    virtual void onDropText(); // SDL_EVENT_DROP_TEXT
    virtual void onDropComplete(); // SDL_EVENT_DROP_COMPLETE
    virtual void onDropPosition(); // SDL_EVENT_DROP_POSITION

    // ==================== CLIPBOARD EVENTS ====================
    virtual void onClipboardUpdate(); // SDL_EVENT_CLIPBOARD_UPDATE

    // ==================== APPLICATION EVENTS ====================
    virtual void onQuit(); // SDL_EVENT_QUIT
    virtual void onTerminating(); // SDL_EVENT_TERMINATING
    virtual void onLowMemory(); // SDL_EVENT_LOW_MEMORY
    virtual void onWillEnterBackground(); // SDL_EVENT_WILL_ENTER_BACKGROUND
    virtual void onDidEnterBackground(); // SDL_EVENT_DID_ENTER_BACKGROUND
    virtual void onWillEnterForeground(); // SDL_EVENT_WILL_ENTER_FOREGROUND
    virtual void onDidEnterForeground(); // SDL_EVENT_DID_ENTER_FOREGROUND
    virtual void onLocaleChanged(); // SDL_EVENT_LOCALE_CHANGED
    virtual void onSystemThemeChanged(); // SDL_EVENT_SYSTEM_THEME_CHANGED

    // ==================== USER EVENTS ====================
    virtual void onUserEvent(); // SDL_EVENT_USER

    // ==================== RUNTIME METHODS ====================
    virtual void quit(void);
    virtual void update(void);
    virtual void runtime();
    std::thread run_async_mod();
    void run_async(std::thread&);
    void run_block_mod();
    void run_block();

protected:
    // Helper method to dispatch events
    void dispatchEvents();
};

} // WSDC
