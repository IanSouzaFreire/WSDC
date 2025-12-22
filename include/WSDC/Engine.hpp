#pragma once

#include <thread>
#include <functional>
#include "WSDC/Window.hpp"
#include "WSDC/Events.hpp"
#include "WSDC/SceneManager.hpp"

namespace WSDC {

namespace Managers {

using SubWindow_l = std::vector<WSDC::Display::Window>;

template <class Key=std::string, class... ExtraData>
struct Engine {
    using Manager = WSDC::Managers::SceneManager<Key, SubWindow_l, ExtraData...>;
    using ExtraDataTuple = std::tuple<ExtraData*...>;

    struct SceneDefinition {
        Key name;
        bool _default = false;
    };

    SubWindow_l sub_windows;
    Manager manager;
    WSDC::Managers::Events events;
    bool is_running;
    ExtraDataTuple extra_data;
    WSDC::Display::Window display;
    Engine();
    ~Engine();

    bool& isRunning(const bool&) noexcept;
    bool& isRunning(void) noexcept;

    void set_extra(ExtraData&...);

    // ==================== WINDOW EVENTS ====================
    virtual void onWindowShown(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_SHOWN
    virtual void onWindowHidden(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_HIDDEN
    virtual void onWindowExposed(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_EXPOSED
    virtual void onWindowMoved(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_MOVED
    virtual void onWindowResized(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_RESIZED
    virtual void onWindowPixelSizeChanged(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED
    virtual void onWindowMetalViewResized(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_METAL_VIEW_RESIZED
    virtual void onWindowMinimized(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_MINIMIZED
    virtual void onWindowMaximized(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_MAXIMIZED
    virtual void onWindowRestored(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_RESTORED
    virtual void onWindowMouseEnter(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_MOUSE_ENTER
    virtual void onWindowMouseLeave(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_MOUSE_LEAVE
    virtual void onWindowFocusGained(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_FOCUS_GAINED
    virtual void onWindowFocusLost(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_FOCUS_LOST
    virtual void onWindowCloseRequested(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_CLOSE_REQUESTED
    virtual void onWindowHitTest(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_HIT_TEST
    virtual void onWindowICCProfChanged(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_ICCPROF_CHANGED
    virtual void onWindowDisplayChanged(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_DISPLAY_CHANGED
    virtual void onWindowDisplayScaleChanged(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED
    virtual void onWindowSafeAreaChanged(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_SAFE_AREA_CHANGED
    virtual void onWindowOccluded(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_OCCLUDED
    virtual void onWindowEnterFullscreen(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_ENTER_FULLSCREEN
    virtual void onWindowLeaveFullscreen(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_LEAVE_FULLSCREEN
    virtual void onWindowDestroyed(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_DESTROYED
    virtual void onWindowPenEnter(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_PEN_ENTER
    virtual void onWindowPenLeave(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_PEN_LEAVE

    // ==================== DISPLAY EVENTS ====================
    virtual void onDisplayOrientation(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DISPLAY_ORIENTATION
    virtual void onDisplayAdded(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DISPLAY_ADDED
    virtual void onDisplayRemoved(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DISPLAY_REMOVED
    virtual void onDisplayMoved(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DISPLAY_MOVED
    virtual void onDisplayContentScaleChanged(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED

    // ==================== KEYBOARD EVENTS ====================
    virtual void onKeyboardAdded(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_KEYBOARD_ADDED
    virtual void onKeyboardRemoved(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_KEYBOARD_REMOVED
    virtual void onKeyDown(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_KEY_DOWN
    virtual void onKeyUp(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_KEY_UP

    // ==================== TEXT INPUT EVENTS ====================
    virtual void onTextEditing(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_TEXT_EDITING
    virtual void onTextEditingCandidates(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_TEXT_EDITING_CANDIDATES
    virtual void onTextInput(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_TEXT_INPUT

    // ==================== MOUSE EVENTS ====================
    virtual void onMouseAdded(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_MOUSE_ADDED
    virtual void onMouseRemoved(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_MOUSE_REMOVED
    virtual void onMouseMotion(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_MOUSE_MOTION
    virtual void onMouseButtonDown(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_MOUSE_BUTTON_DOWN
    virtual void onMouseButtonUp(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_MOUSE_BUTTON_UP
    virtual void onMouseWheel(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_MOUSE_WHEEL

    // ==================== JOYSTICK EVENTS ====================
    virtual void onJoystickAdded(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_JOYSTICK_ADDED
    virtual void onJoystickRemoved(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_JOYSTICK_REMOVED
    virtual void onJoystickUpdateComplete(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_JOYSTICK_UPDATE_COMPLETE
    virtual void onJoystickAxisMotion(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_JOYSTICK_AXIS_MOTION
    virtual void onJoystickBallMotion(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_JOYSTICK_BALL_MOTION
    virtual void onJoystickHatMotion(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_JOYSTICK_HAT_MOTION
    virtual void onJoystickButtonDown(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_JOYSTICK_BUTTON_DOWN
    virtual void onJoystickButtonUp(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_JOYSTICK_BUTTON_UP
    virtual void onJoystickBatteryUpdated(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_JOYSTICK_BATTERY_UPDATED

    // ==================== GAMEPAD EVENTS ====================
    virtual void onGamepadAdded(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_ADDED
    virtual void onGamepadRemoved(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_REMOVED
    virtual void onGamepadRemapped(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_REMAPPED
    virtual void onGamepadUpdateComplete(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_UPDATE_COMPLETE
    virtual void onGamepadSteamHandleUpdated(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED
    virtual void onGamepadAxisMotion(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_AXIS_MOTION
    virtual void onGamepadButtonDown(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_BUTTON_DOWN
    virtual void onGamepadButtonUp(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_BUTTON_UP
    virtual void onGamepadTouchpadDown(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN
    virtual void onGamepadTouchpadMotion(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION
    virtual void onGamepadTouchpadUp(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_TOUCHPAD_UP
    virtual void onGamepadSensorUpdate(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_SENSOR_UPDATE

    // ==================== AUDIO EVENTS ====================
    virtual void onAudioDeviceAdded(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_AUDIO_DEVICE_ADDED
    virtual void onAudioDeviceRemoved(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_AUDIO_DEVICE_REMOVED
    virtual void onAudioDeviceFormatChanged(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED

    // ==================== CAMERA EVENTS ====================
    virtual void onCameraDeviceAdded(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_CAMERA_DEVICE_ADDED
    virtual void onCameraDeviceRemoved(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_CAMERA_DEVICE_REMOVED
    virtual void onCameraDeviceApproved(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_CAMERA_DEVICE_APPROVED
    virtual void onCameraDeviceDenied(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_CAMERA_DEVICE_DENIED

    // ==================== SENSOR EVENTS ====================
    virtual void onSensorUpdate(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_SENSOR_UPDATE

    // ==================== TOUCH EVENTS ====================
    virtual void onFingerDown(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_FINGER_DOWN
    virtual void onFingerUp(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_FINGER_UP
    virtual void onFingerMotion(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_FINGER_MOTION

    // ==================== GESTURE EVENTS ====================
    virtual void onPinchBegin(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PINCH_BEGIN
    virtual void onPinchRotate(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PINCH_ROTATE
    virtual void onPinchEnd(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PINCH_END

    // ==================== PEN EVENTS ====================
    virtual void onPenProximityIn(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PEN_PROXIMITY_IN
    virtual void onPenProximityOut(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PEN_PROXIMITY_OUT
    virtual void onPenDown(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PEN_DOWN
    virtual void onPenUp(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PEN_UP
    virtual void onPenMotion(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PEN_MOTION
    virtual void onPenButtonDown(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PEN_BUTTON_DOWN
    virtual void onPenButtonUp(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PEN_BUTTON_UP
    virtual void onPenAxis(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PEN_AXIS

    // ==================== RENDER EVENTS ====================
    virtual void onRenderTargetsReset(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_RENDER_TARGETS_RESET
    virtual void onRenderDeviceReset(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_RENDER_DEVICE_RESET
    virtual void onRenderDeviceLost(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_RENDER_DEVICE_LOST

    // ==================== DROP EVENTS ====================
    virtual void onDropBegin(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DROP_BEGIN
    virtual void onDropFile(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DROP_FILE
    virtual void onDropText(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DROP_TEXT
    virtual void onDropComplete(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DROP_COMPLETE
    virtual void onDropPosition(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DROP_POSITION

    // ==================== CLIPBOARD EVENTS ====================
    virtual void onClipboardUpdate(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_CLIPBOARD_UPDATE

    // ==================== APPLICATION EVENTS ====================
    virtual void onQuit(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_QUIT
    virtual void onTerminating(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_TERMINATING
    virtual void onLowMemory(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_LOW_MEMORY
    virtual void onWillEnterBackground(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WILL_ENTER_BACKGROUND
    virtual void onDidEnterBackground(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DID_ENTER_BACKGROUND
    virtual void onWillEnterForeground(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WILL_ENTER_FOREGROUND
    virtual void onDidEnterForeground(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DID_ENTER_FOREGROUND
    virtual void onLocaleChanged(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_LOCALE_CHANGED
    virtual void onSystemThemeChanged(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_SYSTEM_THEME_CHANGED

    // ==================== USER EVENTS ====================
    virtual void onUserEvent(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_USER

    // ==================== GENERIC EVENT HANDLER ====================
    virtual void onEvent(WSDC::Display::Window&, WSDC::Managers::Events&, Manager&, SubWindow_l&, ExtraData&...);

    // ==================== RUNTIME METHODS ====================
    virtual void quit(void);
    virtual void update(void);
    virtual void runtime(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...);
    template <std::size_t... Is> std::thread run_async_mod(std::index_sequence<Is...>);
    std::thread run_async();
    template <std::size_t... Is> void run_block_mod(std::index_sequence<Is...>);
    void run_block();

protected:
    // Helper method to dispatch events
    template <std::size_t... Is> void dispatchEvents(std::index_sequence<Is...>);
};

template <class Key, class... ExtraData>
Engine<Key, ExtraData...>::Engine() : is_running(false) {
    try {
        manager.window(display).events(events);
    } catch (...) {
        throw std::runtime_error("Engine<>::Engine()");
    }
}

template <class Key, class... ExtraData>
Engine<Key, ExtraData...>::~Engine() {
    quit();
}

template <class Key, class... ExtraData>
bool& Engine<Key, ExtraData...>::isRunning(const bool& b) noexcept {
    is_running = b;
    return is_running;
}

template <class Key, class... ExtraData>
bool& Engine<Key, ExtraData...>::isRunning(void) noexcept {
    return is_running;
}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::set_extra(ExtraData&... data) {
    try {
        extra_data = std::make_tuple(&data...);
        manager.extra(sub_windows, data...);
    } catch (...) {
        throw std::runtime_error("Engine<>::set_extra");
    }
}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowShown(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_SHOWN */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowHidden(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_HIDDEN */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowExposed(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_EXPOSED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowMoved(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_MOVED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowResized(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_RESIZED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowPixelSizeChanged(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowMetalViewResized(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_METAL_VIEW_RESIZED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowMinimized(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_MINIMIZED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowMaximized(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_MAXIMIZED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowRestored(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_RESTORED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowMouseEnter(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_MOUSE_ENTER */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowMouseLeave(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_MOUSE_LEAVE */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowFocusGained(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_FOCUS_GAINED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowFocusLost(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_FOCUS_LOST */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowCloseRequested(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_CLOSE_REQUESTED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowHitTest(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_HIT_TEST */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowICCProfChanged(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_ICCPROF_CHANGED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowDisplayChanged(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_DISPLAY_CHANGED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowDisplayScaleChanged(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowSafeAreaChanged(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_SAFE_AREA_CHANGED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowOccluded(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_OCCLUDED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowEnterFullscreen(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_ENTER_FULLSCREEN */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowLeaveFullscreen(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_LEAVE_FULLSCREEN */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowDestroyed(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_DESTROYED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowPenEnter(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_PEN_ENTER */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWindowPenLeave(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WINDOW_PEN_LEAVE */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onDisplayOrientation(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_DISPLAY_ORIENTATION */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onDisplayAdded(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_DISPLAY_ADDED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onDisplayRemoved(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_DISPLAY_REMOVED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onDisplayMoved(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_DISPLAY_MOVED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onDisplayContentScaleChanged(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onKeyboardAdded(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_KEYBOARD_ADDED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onKeyboardRemoved(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_KEYBOARD_REMOVED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onKeyDown(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_KEY_DOWN */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onKeyUp(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_KEY_UP */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onTextEditing(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_TEXT_EDITING */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onTextEditingCandidates(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_TEXT_EDITING_CANDIDATES */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onTextInput(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_TEXT_INPUT */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onMouseAdded(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_MOUSE_ADDED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onMouseRemoved(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_MOUSE_REMOVED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onMouseMotion(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_MOUSE_MOTION */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onMouseButtonDown(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_MOUSE_BUTTON_DOWN */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onMouseButtonUp(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_MOUSE_BUTTON_UP */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onMouseWheel(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_MOUSE_WHEEL */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onJoystickAdded(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_JOYSTICK_ADDED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onJoystickRemoved(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_JOYSTICK_REMOVED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onJoystickUpdateComplete(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_JOYSTICK_UPDATE_COMPLETE */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onJoystickAxisMotion(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_JOYSTICK_AXIS_MOTION */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onJoystickBallMotion(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_JOYSTICK_BALL_MOTION */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onJoystickHatMotion(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_JOYSTICK_HAT_MOTION */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onJoystickButtonDown(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_JOYSTICK_BUTTON_DOWN */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onJoystickButtonUp(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_JOYSTICK_BUTTON_UP */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onJoystickBatteryUpdated(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_JOYSTICK_BATTERY_UPDATED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onGamepadAdded(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_GAMEPAD_ADDED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onGamepadRemoved(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_GAMEPAD_REMOVED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onGamepadRemapped(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_GAMEPAD_REMAPPED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onGamepadUpdateComplete(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_GAMEPAD_UPDATE_COMPLETE */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onGamepadSteamHandleUpdated(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onGamepadAxisMotion(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_GAMEPAD_AXIS_MOTION */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onGamepadButtonDown(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_GAMEPAD_BUTTON_DOWN */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onGamepadButtonUp(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_GAMEPAD_BUTTON_UP */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onGamepadTouchpadDown(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onGamepadTouchpadMotion(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onGamepadTouchpadUp(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_GAMEPAD_TOUCHPAD_UP */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onGamepadSensorUpdate(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_GAMEPAD_SENSOR_UPDATE */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onAudioDeviceAdded(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_AUDIO_DEVICE_ADDED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onAudioDeviceRemoved(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_AUDIO_DEVICE_REMOVED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onAudioDeviceFormatChanged(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onCameraDeviceAdded(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_CAMERA_DEVICE_ADDED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onCameraDeviceRemoved(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_CAMERA_DEVICE_REMOVED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onCameraDeviceApproved(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_CAMERA_DEVICE_APPROVED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onCameraDeviceDenied(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_CAMERA_DEVICE_DENIED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onSensorUpdate(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_SENSOR_UPDATE */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onFingerDown(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_FINGER_DOWN */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onFingerUp(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_FINGER_UP */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onFingerMotion(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_FINGER_MOTION */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onPinchBegin(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_PINCH_BEGIN */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onPinchRotate(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_PINCH_ROTATE */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onPinchEnd(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_PINCH_END */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onPenProximityIn(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_PEN_PROXIMITY_IN */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onPenProximityOut(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_PEN_PROXIMITY_OUT */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onPenDown(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_PEN_DOWN */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onPenUp(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_PEN_UP */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onPenMotion(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_PEN_MOTION */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onPenButtonDown(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_PEN_BUTTON_DOWN */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onPenButtonUp(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_PEN_BUTTON_UP */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onPenAxis(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_PEN_AXIS */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onRenderTargetsReset(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_RENDER_TARGETS_RESET */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onRenderDeviceReset(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_RENDER_DEVICE_RESET */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onRenderDeviceLost(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_RENDER_DEVICE_LOST */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onDropBegin(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_DROP_BEGIN */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onDropFile(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_DROP_FILE */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onDropText(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_DROP_TEXT */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onDropComplete(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_DROP_COMPLETE */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onDropPosition(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_DROP_POSITION */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onClipboardUpdate(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_CLIPBOARD_UPDATE */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onQuit(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_QUIT */ {
    quit();
}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onTerminating(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_TERMINATING */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onLowMemory(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_LOW_MEMORY */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWillEnterBackground(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WILL_ENTER_BACKGROUND */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onDidEnterBackground(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_DID_ENTER_BACKGROUND */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onWillEnterForeground(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_WILL_ENTER_FOREGROUND */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onDidEnterForeground(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_DID_ENTER_FOREGROUND */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onLocaleChanged(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_LOCALE_CHANGED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onSystemThemeChanged(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_SYSTEM_THEME_CHANGED */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onUserEvent(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) /* SDL_EVENT_USER */ {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::onEvent(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) {}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::quit(void) {
    is_running = false;
    display.close();

    for (auto& win : sub_windows) {
        win.close();
    }
}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::update(void) {
    display.update();

    for (auto& d : sub_windows) {
        d.update();
    }
}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::runtime(WSDC::Display::Window&, WSDC::Managers::Events&, Engine<Key, ExtraData...>::Manager&, SubWindow_l&, ExtraData&...) {
    while (is_running) {
        events.update();
        dispatchEvents(std::index_sequence_for<ExtraData...>{});

        manager.run();

        update();
    }
}

template <class Key, class... ExtraData>
template <std::size_t... Is>
std::thread Engine<Key, ExtraData...>::run_async_mod(std::index_sequence<Is...>) {
    return std::thread([this]() { runtime(display, events, manager, sub_windows, *std::get<Is>(extra_data)...); });
}

template <class Key, class... ExtraData>
std::thread Engine<Key, ExtraData...>::run_async() {
    if (is_running == false) {
        throw std::runtime_error("Cannot execute with isRunning() == false");
    }
    
    return run_async_mod(std::index_sequence_for<ExtraData...>{});
}

template <class Key, class... ExtraData>
template <std::size_t... Is>
void Engine<Key, ExtraData...>::run_block_mod(std::index_sequence<Is...>) {
    runtime(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::run_block() {
    if (is_running == false) {
        throw std::runtime_error("Cannot execute with isRunning() == false");
    }

    run_block_mod(std::index_sequence_for<ExtraData...>{});
}

template <class Key, class... ExtraData>
template <std::size_t... Is>
void Engine<Key, ExtraData...>::dispatchEvents(std::index_sequence<Is...>) {
    for (const auto& ty : events.type) {
        switch (ty) {
            case SDL_EVENT_DISPLAY_ORIENTATION:
                onDisplayOrientation(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_DISPLAY_ADDED:
                onDisplayAdded(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_DISPLAY_REMOVED:
                onDisplayRemoved(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_DISPLAY_MOVED:
                onDisplayMoved(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED:
                onDisplayContentScaleChanged(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_SHOWN:
                onWindowShown(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_HIDDEN:
                onWindowHidden(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_EXPOSED:
                onWindowExposed(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_MOVED:
                onWindowMoved(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                onWindowResized(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
                onWindowPixelSizeChanged(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_METAL_VIEW_RESIZED:
                onWindowMetalViewResized(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_MINIMIZED:
                onWindowMinimized(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_MAXIMIZED:
                onWindowMaximized(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_RESTORED:
                onWindowRestored(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_MOUSE_ENTER:
                onWindowMouseEnter(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_MOUSE_LEAVE:
                onWindowMouseLeave(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_FOCUS_GAINED:
                onWindowFocusGained(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_FOCUS_LOST:
                onWindowFocusLost(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                onWindowCloseRequested(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_HIT_TEST:
                onWindowHitTest(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_ICCPROF_CHANGED:
                onWindowICCProfChanged(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_DISPLAY_CHANGED:
                onWindowDisplayChanged(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED:
                onWindowDisplayScaleChanged(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_SAFE_AREA_CHANGED:
                onWindowSafeAreaChanged(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_OCCLUDED:
                onWindowOccluded(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_ENTER_FULLSCREEN:
                onWindowEnterFullscreen(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN:
                onWindowLeaveFullscreen(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WINDOW_DESTROYED:
                onWindowDestroyed(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_KEYBOARD_ADDED:
                onKeyboardAdded(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_KEYBOARD_REMOVED:
                onKeyboardRemoved(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_KEY_DOWN:
                onKeyDown(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_KEY_UP:
                onKeyUp(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_TEXT_EDITING:
                onTextEditing(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_TEXT_EDITING_CANDIDATES:
                onTextEditingCandidates(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_TEXT_INPUT:
                onTextInput(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_MOUSE_ADDED:
                onMouseAdded(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_MOUSE_REMOVED:
                onMouseRemoved(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_MOUSE_MOTION:
                onMouseMotion(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                onMouseButtonDown(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                onMouseButtonUp(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_MOUSE_WHEEL:
                onMouseWheel(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_JOYSTICK_ADDED:
                onJoystickAdded(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_JOYSTICK_REMOVED:
                onJoystickRemoved(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_JOYSTICK_UPDATE_COMPLETE:
                onJoystickUpdateComplete(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_JOYSTICK_AXIS_MOTION:
                onJoystickAxisMotion(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_JOYSTICK_BALL_MOTION:
                onJoystickBallMotion(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_JOYSTICK_HAT_MOTION:
                onJoystickHatMotion(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
                onJoystickButtonDown(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_JOYSTICK_BUTTON_UP:
                onJoystickButtonUp(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_JOYSTICK_BATTERY_UPDATED:
                onJoystickBatteryUpdated(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_GAMEPAD_ADDED:
                onGamepadAdded(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_GAMEPAD_REMOVED:
                onGamepadRemoved(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_GAMEPAD_REMAPPED:
                onGamepadRemapped(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_GAMEPAD_UPDATE_COMPLETE:
                onGamepadUpdateComplete(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED:
                onGamepadSteamHandleUpdated(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_GAMEPAD_AXIS_MOTION:
                onGamepadAxisMotion(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
                onGamepadButtonDown(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_GAMEPAD_BUTTON_UP:
                onGamepadButtonUp(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN:
                onGamepadTouchpadDown(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION:
                onGamepadTouchpadMotion(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_GAMEPAD_TOUCHPAD_UP:
                onGamepadTouchpadUp(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_GAMEPAD_SENSOR_UPDATE:
                onGamepadSensorUpdate(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_AUDIO_DEVICE_ADDED:
                onAudioDeviceAdded(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_AUDIO_DEVICE_REMOVED:
                onAudioDeviceRemoved(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED:
                onAudioDeviceFormatChanged(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_CAMERA_DEVICE_ADDED:
                onCameraDeviceAdded(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_CAMERA_DEVICE_REMOVED:
                onCameraDeviceRemoved(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_CAMERA_DEVICE_APPROVED:
                onCameraDeviceApproved(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_CAMERA_DEVICE_DENIED:
                onCameraDeviceDenied(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_SENSOR_UPDATE:
                onSensorUpdate(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_QUIT:
                onQuit(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_TERMINATING:
                onTerminating(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_LOW_MEMORY:
                onLowMemory(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WILL_ENTER_BACKGROUND:
                onWillEnterBackground(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_DID_ENTER_BACKGROUND:
                onDidEnterBackground(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_WILL_ENTER_FOREGROUND:
                onWillEnterForeground(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_DID_ENTER_FOREGROUND:
                onDidEnterForeground(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_LOCALE_CHANGED:
                onLocaleChanged(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_SYSTEM_THEME_CHANGED:
                onSystemThemeChanged(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_USER:
                onUserEvent(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_FINGER_DOWN:
                onFingerDown(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_FINGER_UP:
                onFingerUp(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_FINGER_MOTION:
                onFingerMotion(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_PEN_PROXIMITY_IN:
                onPenProximityIn(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_PEN_PROXIMITY_OUT:
                onPenProximityOut(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_PEN_DOWN:
                onPenDown(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_PEN_UP:
                onPenUp(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_PEN_MOTION:
                onPenMotion(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_PEN_BUTTON_DOWN:
                onPenButtonDown(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_PEN_BUTTON_UP:
                onPenButtonUp(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_PEN_AXIS:
                onPenAxis(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_RENDER_TARGETS_RESET:
                onRenderTargetsReset(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_RENDER_DEVICE_RESET:
                onRenderDeviceReset(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_RENDER_DEVICE_LOST:
                onRenderDeviceLost(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_DROP_BEGIN:
                onDropBegin(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_DROP_FILE:
                onDropFile(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_DROP_TEXT:
                onDropText(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_DROP_COMPLETE:
                onDropComplete(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_DROP_POSITION:
                onDropPosition(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            case SDL_EVENT_CLIPBOARD_UPDATE:
                onClipboardUpdate(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
            default:
                onEvent(display, events, manager, sub_windows, *std::get<Is>(extra_data)...);
                break;
        }
    }
}

} // Managers

} // WSDC
