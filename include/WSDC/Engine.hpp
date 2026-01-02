#pragma once

#include <thread>
#include <functional>
#include "Window.hpp"
#include "Events.hpp"
#include "SceneManager.hpp"
#include "TextRenderer.hpp"
#include "Draw/Wrappers.hpp"

namespace WSDC {

namespace Managers {


using SubWindow_l = std::vector<WSDC::Display::Window>;

template <class Key=std::string, class... ExtraData>
struct Engine {
    using Manager = WSDC::Managers::SceneManager<Key, SubWindow_l, WSDC::Managers::TextRenderer, ExtraData...>;
    using ExtraDataTuple = std::tuple<ExtraData*...>;
    using CONFIG = Engine<Key, ExtraData...>;

    struct SceneDefinition {
        Key name;
        bool _default = false;
    };

    bool use_onEvents = true;
    SubWindow_l sub_windows;
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
    void write(const std::string& _font, const WSDC::Geo::Rect<int>& _position, const std::string& _text, Args... _args) {
        text.write(_font, _position, _text, _args...);
    }

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

    // ==================== GENERIC EVENT HANDLER ====================
    virtual void onEvent();

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

template <class Key, class... ExtraData>
Engine<Key, ExtraData...>::Engine() : is_running(false) {
    try {
        manager.window(display).events(events);
        text.renderer(display.raw.renderer);
    } catch (...) {
        throw std::runtime_error("[Engine::Engine] init failed");
    }
}

template <class Key, class... ExtraData>
Engine<Key, ExtraData...>::~Engine() {
    quit();
}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::isRunning(const bool& b) noexcept {
    is_running.store(b);
}

template <class Key, class... ExtraData>
bool Engine<Key, ExtraData...>::isRunning(void) noexcept {
    return is_running.load();
}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::set_extra(ExtraData&... data) {
    try {
        extra_data = std::make_tuple(&data...);
        manager.extra(sub_windows, text, data...);
    } catch (...) {
        throw std::runtime_error("Engine<>::set_extra");
    }
}

template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowShown() /* SDL_EVENT_WINDOW_SHOWN */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowHidden() /* SDL_EVENT_WINDOW_HIDDEN */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowExposed() /* SDL_EVENT_WINDOW_EXPOSED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowMoved() /* SDL_EVENT_WINDOW_MOVED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowResized() /* SDL_EVENT_WINDOW_RESIZED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowPixelSizeChanged() /* SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowMetalViewResized() /* SDL_EVENT_WINDOW_METAL_VIEW_RESIZED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowMinimized() /* SDL_EVENT_WINDOW_MINIMIZED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowMaximized() /* SDL_EVENT_WINDOW_MAXIMIZED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowRestored() /* SDL_EVENT_WINDOW_RESTORED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowMouseEnter() /* SDL_EVENT_WINDOW_MOUSE_ENTER */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowMouseLeave() /* SDL_EVENT_WINDOW_MOUSE_LEAVE */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowFocusGained() /* SDL_EVENT_WINDOW_FOCUS_GAINED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowFocusLost() /* SDL_EVENT_WINDOW_FOCUS_LOST */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowCloseRequested() /* SDL_EVENT_WINDOW_CLOSE_REQUESTED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowHitTest() /* SDL_EVENT_WINDOW_HIT_TEST */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowICCProfChanged() /* SDL_EVENT_WINDOW_ICCPROF_CHANGED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowDisplayChanged() /* SDL_EVENT_WINDOW_DISPLAY_CHANGED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowDisplayScaleChanged() /* SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowSafeAreaChanged() /* SDL_EVENT_WINDOW_SAFE_AREA_CHANGED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowOccluded() /* SDL_EVENT_WINDOW_OCCLUDED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowEnterFullscreen() /* SDL_EVENT_WINDOW_ENTER_FULLSCREEN */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowLeaveFullscreen() /* SDL_EVENT_WINDOW_LEAVE_FULLSCREEN */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowDestroyed() /* SDL_EVENT_WINDOW_DESTROYED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowPenEnter() /* SDL_EVENT_WINDOW_PEN_ENTER */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWindowPenLeave() /* SDL_EVENT_WINDOW_PEN_LEAVE */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onDisplayOrientation() /* SDL_EVENT_DISPLAY_ORIENTATION */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onDisplayAdded() /* SDL_EVENT_DISPLAY_ADDED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onDisplayRemoved() /* SDL_EVENT_DISPLAY_REMOVED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onDisplayMoved() /* SDL_EVENT_DISPLAY_MOVED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onDisplayContentScaleChanged() /* SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onKeyboardAdded() /* SDL_EVENT_KEYBOARD_ADDED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onKeyboardRemoved() /* SDL_EVENT_KEYBOARD_REMOVED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onKeyDown() /* SDL_EVENT_KEY_DOWN */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onKeyUp() /* SDL_EVENT_KEY_UP */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onTextEditing() /* SDL_EVENT_TEXT_EDITING */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onTextEditingCandidates() /* SDL_EVENT_TEXT_EDITING_CANDIDATES */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onTextInput() /* SDL_EVENT_TEXT_INPUT */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onMouseAdded() /* SDL_EVENT_MOUSE_ADDED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onMouseRemoved() /* SDL_EVENT_MOUSE_REMOVED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onMouseMotion() /* SDL_EVENT_MOUSE_MOTION */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onMouseButtonDown() /* SDL_EVENT_MOUSE_BUTTON_DOWN */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onMouseButtonUp() /* SDL_EVENT_MOUSE_BUTTON_UP */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onMouseWheel() /* SDL_EVENT_MOUSE_WHEEL */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onJoystickAdded() /* SDL_EVENT_JOYSTICK_ADDED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onJoystickRemoved() /* SDL_EVENT_JOYSTICK_REMOVED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onJoystickUpdateComplete() /* SDL_EVENT_JOYSTICK_UPDATE_COMPLETE */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onJoystickAxisMotion() /* SDL_EVENT_JOYSTICK_AXIS_MOTION */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onJoystickBallMotion() /* SDL_EVENT_JOYSTICK_BALL_MOTION */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onJoystickHatMotion() /* SDL_EVENT_JOYSTICK_HAT_MOTION */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onJoystickButtonDown() /* SDL_EVENT_JOYSTICK_BUTTON_DOWN */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onJoystickButtonUp() /* SDL_EVENT_JOYSTICK_BUTTON_UP */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onJoystickBatteryUpdated() /* SDL_EVENT_JOYSTICK_BATTERY_UPDATED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onGamepadAdded() /* SDL_EVENT_GAMEPAD_ADDED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onGamepadRemoved() /* SDL_EVENT_GAMEPAD_REMOVED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onGamepadRemapped() /* SDL_EVENT_GAMEPAD_REMAPPED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onGamepadUpdateComplete() /* SDL_EVENT_GAMEPAD_UPDATE_COMPLETE */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onGamepadSteamHandleUpdated() /* SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onGamepadAxisMotion() /* SDL_EVENT_GAMEPAD_AXIS_MOTION */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onGamepadButtonDown() /* SDL_EVENT_GAMEPAD_BUTTON_DOWN */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onGamepadButtonUp() /* SDL_EVENT_GAMEPAD_BUTTON_UP */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onGamepadTouchpadDown() /* SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onGamepadTouchpadMotion() /* SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onGamepadTouchpadUp() /* SDL_EVENT_GAMEPAD_TOUCHPAD_UP */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onGamepadSensorUpdate() /* SDL_EVENT_GAMEPAD_SENSOR_UPDATE */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onAudioDeviceAdded() /* SDL_EVENT_AUDIO_DEVICE_ADDED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onAudioDeviceRemoved() /* SDL_EVENT_AUDIO_DEVICE_REMOVED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onAudioDeviceFormatChanged() /* SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onCameraDeviceAdded() /* SDL_EVENT_CAMERA_DEVICE_ADDED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onCameraDeviceRemoved() /* SDL_EVENT_CAMERA_DEVICE_REMOVED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onCameraDeviceApproved() /* SDL_EVENT_CAMERA_DEVICE_APPROVED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onCameraDeviceDenied() /* SDL_EVENT_CAMERA_DEVICE_DENIED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onSensorUpdate() /* SDL_EVENT_SENSOR_UPDATE */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onFingerDown() /* SDL_EVENT_FINGER_DOWN */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onFingerUp() /* SDL_EVENT_FINGER_UP */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onFingerMotion() /* SDL_EVENT_FINGER_MOTION */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onPinchBegin() /* SDL_EVENT_PINCH_BEGIN */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onPinchRotate() /* SDL_EVENT_PINCH_ROTATE */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onPinchEnd() /* SDL_EVENT_PINCH_END */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onPenProximityIn() /* SDL_EVENT_PEN_PROXIMITY_IN */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onPenProximityOut() /* SDL_EVENT_PEN_PROXIMITY_OUT */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onPenDown() /* SDL_EVENT_PEN_DOWN */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onPenUp() /* SDL_EVENT_PEN_UP */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onPenMotion() /* SDL_EVENT_PEN_MOTION */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onPenButtonDown() /* SDL_EVENT_PEN_BUTTON_DOWN */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onPenButtonUp() /* SDL_EVENT_PEN_BUTTON_UP */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onPenAxis() /* SDL_EVENT_PEN_AXIS */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onRenderTargetsReset() /* SDL_EVENT_RENDER_TARGETS_RESET */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onRenderDeviceReset() /* SDL_EVENT_RENDER_DEVICE_RESET */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onRenderDeviceLost() /* SDL_EVENT_RENDER_DEVICE_LOST */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onDropBegin() /* SDL_EVENT_DROP_BEGIN */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onDropFile() /* SDL_EVENT_DROP_FILE */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onDropText() /* SDL_EVENT_DROP_TEXT */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onDropComplete() /* SDL_EVENT_DROP_COMPLETE */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onDropPosition() /* SDL_EVENT_DROP_POSITION */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onClipboardUpdate() /* SDL_EVENT_CLIPBOARD_UPDATE */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onQuit() /* SDL_EVENT_QUIT */ { quit(); }
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onTerminating() /* SDL_EVENT_TERMINATING */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onLowMemory() /* SDL_EVENT_LOW_MEMORY */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWillEnterBackground() /* SDL_EVENT_WILL_ENTER_BACKGROUND */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onDidEnterBackground() /* SDL_EVENT_DID_ENTER_BACKGROUND */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onWillEnterForeground() /* SDL_EVENT_WILL_ENTER_FOREGROUND */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onDidEnterForeground() /* SDL_EVENT_DID_ENTER_FOREGROUND */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onLocaleChanged() /* SDL_EVENT_LOCALE_CHANGED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onSystemThemeChanged() /* SDL_EVENT_SYSTEM_THEME_CHANGED */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onUserEvent() /* SDL_EVENT_USER */ {}
template <class Key, class... ExtraData> void Engine<Key, ExtraData...>::onEvent() {}

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

    if (!sub_windows.empty()) {
        for (auto& d : sub_windows) {
            d.update();
        }
    }
}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::runtime() {
    while (true) {
        if (!(is_running.load())) break;

        events.update();

        if (use_onEvents) {
            dispatchEvents();
        }

        manager.run();

        update();
    }
}

template <class Key, class... ExtraData>
std::thread Engine<Key, ExtraData...>::run_async_mod() {
    return std::thread([this](void) -> void { runtime(); });
}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::run_async(std::thread& thread) {
    if (is_running == false) {
        throw std::runtime_error("Cannot execute with isRunning() == false");
    }

    thread = run_async_mod();
}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::run_block_mod() {
    runtime();
}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::run_block() {
    if (is_running == false) {
        throw std::runtime_error("Cannot execute with isRunning() == false");
    }

    run_block_mod();
}

template <class Key, class... ExtraData>
void Engine<Key, ExtraData...>::dispatchEvents() {
    for (const auto& ty : events.type) {
        switch (ty) {
            case SDL_EVENT_DISPLAY_ORIENTATION:
                onDisplayOrientation();
                break;
            case SDL_EVENT_DISPLAY_ADDED:
                onDisplayAdded();
                break;
            case SDL_EVENT_DISPLAY_REMOVED:
                onDisplayRemoved();
                break;
            case SDL_EVENT_DISPLAY_MOVED:
                onDisplayMoved();
                break;
            case SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED:
                onDisplayContentScaleChanged();
                break;
            case SDL_EVENT_WINDOW_SHOWN:
                onWindowShown();
                break;
            case SDL_EVENT_WINDOW_HIDDEN:
                onWindowHidden();
                break;
            case SDL_EVENT_WINDOW_EXPOSED:
                onWindowExposed();
                break;
            case SDL_EVENT_WINDOW_MOVED:
                onWindowMoved();
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                onWindowResized();
                break;
            case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
                onWindowPixelSizeChanged();
                break;
            case SDL_EVENT_WINDOW_METAL_VIEW_RESIZED:
                onWindowMetalViewResized();
                break;
            case SDL_EVENT_WINDOW_MINIMIZED:
                onWindowMinimized();
                break;
            case SDL_EVENT_WINDOW_MAXIMIZED:
                onWindowMaximized();
                break;
            case SDL_EVENT_WINDOW_RESTORED:
                onWindowRestored();
                break;
            case SDL_EVENT_WINDOW_MOUSE_ENTER:
                onWindowMouseEnter();
                break;
            case SDL_EVENT_WINDOW_MOUSE_LEAVE:
                onWindowMouseLeave();
                break;
            case SDL_EVENT_WINDOW_FOCUS_GAINED:
                onWindowFocusGained();
                break;
            case SDL_EVENT_WINDOW_FOCUS_LOST:
                onWindowFocusLost();
                break;
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                onWindowCloseRequested();
                break;
            case SDL_EVENT_WINDOW_HIT_TEST:
                onWindowHitTest();
                break;
            case SDL_EVENT_WINDOW_ICCPROF_CHANGED:
                onWindowICCProfChanged();
                break;
            case SDL_EVENT_WINDOW_DISPLAY_CHANGED:
                onWindowDisplayChanged();
                break;
            case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED:
                onWindowDisplayScaleChanged();
                break;
            case SDL_EVENT_WINDOW_SAFE_AREA_CHANGED:
                onWindowSafeAreaChanged();
                break;
            case SDL_EVENT_WINDOW_OCCLUDED:
                onWindowOccluded();
                break;
            case SDL_EVENT_WINDOW_ENTER_FULLSCREEN:
                onWindowEnterFullscreen();
                break;
            case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN:
                onWindowLeaveFullscreen();
                break;
            case SDL_EVENT_WINDOW_DESTROYED:
                onWindowDestroyed();
                break;
            case SDL_EVENT_KEYBOARD_ADDED:
                onKeyboardAdded();
                break;
            case SDL_EVENT_KEYBOARD_REMOVED:
                onKeyboardRemoved();
                break;
            case SDL_EVENT_KEY_DOWN:
                onKeyDown();
                break;
            case SDL_EVENT_KEY_UP:
                onKeyUp();
                break;
            case SDL_EVENT_TEXT_EDITING:
                onTextEditing();
                break;
            case SDL_EVENT_TEXT_EDITING_CANDIDATES:
                onTextEditingCandidates();
                break;
            case SDL_EVENT_TEXT_INPUT:
                onTextInput();
                break;
            case SDL_EVENT_MOUSE_ADDED:
                onMouseAdded();
                break;
            case SDL_EVENT_MOUSE_REMOVED:
                onMouseRemoved();
                break;
            case SDL_EVENT_MOUSE_MOTION:
                onMouseMotion();
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                onMouseButtonDown();
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                onMouseButtonUp();
                break;
            case SDL_EVENT_MOUSE_WHEEL:
                onMouseWheel();
                break;
            case SDL_EVENT_JOYSTICK_ADDED:
                onJoystickAdded();
                break;
            case SDL_EVENT_JOYSTICK_REMOVED:
                onJoystickRemoved();
                break;
            case SDL_EVENT_JOYSTICK_UPDATE_COMPLETE:
                onJoystickUpdateComplete();
                break;
            case SDL_EVENT_JOYSTICK_AXIS_MOTION:
                onJoystickAxisMotion();
                break;
            case SDL_EVENT_JOYSTICK_BALL_MOTION:
                onJoystickBallMotion();
                break;
            case SDL_EVENT_JOYSTICK_HAT_MOTION:
                onJoystickHatMotion();
                break;
            case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
                onJoystickButtonDown();
                break;
            case SDL_EVENT_JOYSTICK_BUTTON_UP:
                onJoystickButtonUp();
                break;
            case SDL_EVENT_JOYSTICK_BATTERY_UPDATED:
                onJoystickBatteryUpdated();
                break;
            case SDL_EVENT_GAMEPAD_ADDED:
                onGamepadAdded();
                break;
            case SDL_EVENT_GAMEPAD_REMOVED:
                onGamepadRemoved();
                break;
            case SDL_EVENT_GAMEPAD_REMAPPED:
                onGamepadRemapped();
                break;
            case SDL_EVENT_GAMEPAD_UPDATE_COMPLETE:
                onGamepadUpdateComplete();
                break;
            case SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED:
                onGamepadSteamHandleUpdated();
                break;
            case SDL_EVENT_GAMEPAD_AXIS_MOTION:
                onGamepadAxisMotion();
                break;
            case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
                onGamepadButtonDown();
                break;
            case SDL_EVENT_GAMEPAD_BUTTON_UP:
                onGamepadButtonUp();
                break;
            case SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN:
                onGamepadTouchpadDown();
                break;
            case SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION:
                onGamepadTouchpadMotion();
                break;
            case SDL_EVENT_GAMEPAD_TOUCHPAD_UP:
                onGamepadTouchpadUp();
                break;
            case SDL_EVENT_GAMEPAD_SENSOR_UPDATE:
                onGamepadSensorUpdate();
                break;
            case SDL_EVENT_AUDIO_DEVICE_ADDED:
                onAudioDeviceAdded();
                break;
            case SDL_EVENT_AUDIO_DEVICE_REMOVED:
                onAudioDeviceRemoved();
                break;
            case SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED:
                onAudioDeviceFormatChanged();
                break;
            case SDL_EVENT_CAMERA_DEVICE_ADDED:
                onCameraDeviceAdded();
                break;
            case SDL_EVENT_CAMERA_DEVICE_REMOVED:
                onCameraDeviceRemoved();
                break;
            case SDL_EVENT_CAMERA_DEVICE_APPROVED:
                onCameraDeviceApproved();
                break;
            case SDL_EVENT_CAMERA_DEVICE_DENIED:
                onCameraDeviceDenied();
                break;
            case SDL_EVENT_SENSOR_UPDATE:
                onSensorUpdate();
                break;
            case SDL_EVENT_QUIT:
                onQuit();
                break;
            case SDL_EVENT_TERMINATING:
                onTerminating();
                break;
            case SDL_EVENT_LOW_MEMORY:
                onLowMemory();
                break;
            case SDL_EVENT_WILL_ENTER_BACKGROUND:
                onWillEnterBackground();
                break;
            case SDL_EVENT_DID_ENTER_BACKGROUND:
                onDidEnterBackground();
                break;
            case SDL_EVENT_WILL_ENTER_FOREGROUND:
                onWillEnterForeground();
                break;
            case SDL_EVENT_DID_ENTER_FOREGROUND:
                onDidEnterForeground();
                break;
            case SDL_EVENT_LOCALE_CHANGED:
                onLocaleChanged();
                break;
            case SDL_EVENT_SYSTEM_THEME_CHANGED:
                onSystemThemeChanged();
                break;
            case SDL_EVENT_USER:
                onUserEvent();
                break;
            case SDL_EVENT_FINGER_DOWN:
                onFingerDown();
                break;
            case SDL_EVENT_FINGER_UP:
                onFingerUp();
                break;
            case SDL_EVENT_FINGER_MOTION:
                onFingerMotion();
                break;
            case SDL_EVENT_PEN_PROXIMITY_IN:
                onPenProximityIn();
                break;
            case SDL_EVENT_PEN_PROXIMITY_OUT:
                onPenProximityOut();
                break;
            case SDL_EVENT_PEN_DOWN:
                onPenDown();
                break;
            case SDL_EVENT_PEN_UP:
                onPenUp();
                break;
            case SDL_EVENT_PEN_MOTION:
                onPenMotion();
                break;
            case SDL_EVENT_PEN_BUTTON_DOWN:
                onPenButtonDown();
                break;
            case SDL_EVENT_PEN_BUTTON_UP:
                onPenButtonUp();
                break;
            case SDL_EVENT_PEN_AXIS:
                onPenAxis();
                break;
            case SDL_EVENT_RENDER_TARGETS_RESET:
                onRenderTargetsReset();
                break;
            case SDL_EVENT_RENDER_DEVICE_RESET:
                onRenderDeviceReset();
                break;
            case SDL_EVENT_RENDER_DEVICE_LOST:
                onRenderDeviceLost();
                break;
            case SDL_EVENT_DROP_BEGIN:
                onDropBegin();
                break;
            case SDL_EVENT_DROP_FILE:
                onDropFile();
                break;
            case SDL_EVENT_DROP_TEXT:
                onDropText();
                break;
            case SDL_EVENT_DROP_COMPLETE:
                onDropComplete();
                break;
            case SDL_EVENT_DROP_POSITION:
                onDropPosition();
                break;
            case SDL_EVENT_CLIPBOARD_UPDATE:
                onClipboardUpdate();
                break;
            default:
                onEvent();
                break;
        }
    }
}

} // Managers

} // WSDC
