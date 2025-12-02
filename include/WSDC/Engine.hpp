#pragma once

#include <thread>
#include <functional>
#include "Window.hpp"
#include "Events.hpp"
#include "SceneManager.hpp"

using SubWindow_l = std::vector<Window>;

template <class Key=std::string, class... ExtraData>
class Engine {
    using Manager = SceneManager<Key, SceneManager, SubWindow_l, ExtraData...>;

    struct SceneDefinition {
        Key name;
        bool _default = false;
    };

    SubWindow_l sub_windows;
    Manager manager;
    Events events;
public:
    Window display;
    Engine();
    ~Engine();

    // =================== SCENE MANAGMENT ===================
    Engine& editScene(const SceneDefinition&, );

    // ==================== WINDOW EVENTS ====================
    virtual void onWindowShown(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_SHOWN
    virtual void onWindowHidden(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_HIDDEN
    virtual void onWindowExposed(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_EXPOSED
    virtual void onWindowMoved(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_MOVED
    virtual void onWindowResized(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_RESIZED
    virtual void onWindowPixelSizeChanged(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED
    virtual void onWindowMetalViewResized(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_METAL_VIEW_RESIZED
    virtual void onWindowMinimized(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_MINIMIZED
    virtual void onWindowMaximized(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_MAXIMIZED
    virtual void onWindowRestored(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_RESTORED
    virtual void onWindowMouseEnter(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_MOUSE_ENTER
    virtual void onWindowMouseLeave(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_MOUSE_LEAVE
    virtual void onWindowFocusGained(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_FOCUS_GAINED
    virtual void onWindowFocusLost(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_FOCUS_LOST
    virtual void onWindowCloseRequested(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_CLOSE_REQUESTED
    virtual void onWindowHitTest(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_HIT_TEST
    virtual void onWindowICCProfChanged(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_ICCPROF_CHANGED
    virtual void onWindowDisplayChanged(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_DISPLAY_CHANGED
    virtual void onWindowDisplayScaleChanged(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED
    virtual void onWindowSafeAreaChanged(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_SAFE_AREA_CHANGED
    virtual void onWindowOccluded(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_OCCLUDED
    virtual void onWindowEnterFullscreen(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_ENTER_FULLSCREEN
    virtual void onWindowLeaveFullscreen(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_LEAVE_FULLSCREEN
    virtual void onWindowDestroyed(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_DESTROYED
    virtual void onWindowPenEnter(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_PEN_ENTER
    virtual void onWindowPenLeave(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WINDOW_PEN_LEAVE

    // ==================== DISPLAY EVENTS ====================
    virtual void onDisplayOrientation(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DISPLAY_ORIENTATION
    virtual void onDisplayAdded(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DISPLAY_ADDED
    virtual void onDisplayRemoved(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DISPLAY_REMOVED
    virtual void onDisplayMoved(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DISPLAY_MOVED
    virtual void onDisplayContentScaleChanged(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED

    // ==================== KEYBOARD EVENTS ====================
    virtual void onKeyboardAdded(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_KEYBOARD_ADDED
    virtual void onKeyboardRemoved(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_KEYBOARD_REMOVED
    virtual void onKeyDown(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_KEY_DOWN
    virtual void onKeyUp(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_KEY_UP

    // ==================== TEXT INPUT EVENTS ====================
    virtual void onTextEditing(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_TEXT_EDITING
    virtual void onTextEditingCandidates(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_TEXT_EDITING_CANDIDATES
    virtual void onTextInput(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_TEXT_INPUT

    // ==================== MOUSE EVENTS ====================
    virtual void onMouseAdded(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_MOUSE_ADDED
    virtual void onMouseRemoved(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_MOUSE_REMOVED
    virtual void onMouseMotion(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_MOUSE_MOTION
    virtual void onMouseButtonDown(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_MOUSE_BUTTON_DOWN
    virtual void onMouseButtonUp(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_MOUSE_BUTTON_UP
    virtual void onMouseWheel(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_MOUSE_WHEEL

    // ==================== JOYSTICK EVENTS ====================
    virtual void onJoystickAdded(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_JOYSTICK_ADDED
    virtual void onJoystickRemoved(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_JOYSTICK_REMOVED
    virtual void onJoystickUpdateComplete(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_JOYSTICK_UPDATE_COMPLETE
    virtual void onJoystickAxisMotion(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_JOYSTICK_AXIS_MOTION
    virtual void onJoystickBallMotion(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_JOYSTICK_BALL_MOTION
    virtual void onJoystickHatMotion(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_JOYSTICK_HAT_MOTION
    virtual void onJoystickButtonDown(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_JOYSTICK_BUTTON_DOWN
    virtual void onJoystickButtonUp(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_JOYSTICK_BUTTON_UP
    virtual void onJoystickBatteryUpdated(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_JOYSTICK_BATTERY_UPDATED

    // ==================== GAMEPAD EVENTS ====================
    virtual void onGamepadAdded(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_ADDED
    virtual void onGamepadRemoved(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_REMOVED
    virtual void onGamepadRemapped(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_REMAPPED
    virtual void onGamepadUpdateComplete(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_UPDATE_COMPLETE
    virtual void onGamepadSteamHandleUpdated(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED
    virtual void onGamepadAxisMotion(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_AXIS_MOTION
    virtual void onGamepadButtonDown(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_BUTTON_DOWN
    virtual void onGamepadButtonUp(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_BUTTON_UP
    virtual void onGamepadTouchpadDown(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN
    virtual void onGamepadTouchpadMotion(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION
    virtual void onGamepadTouchpadUp(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_TOUCHPAD_UP
    virtual void onGamepadSensorUpdate(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_GAMEPAD_SENSOR_UPDATE

    // ==================== AUDIO EVENTS ====================
    virtual void onAudioDeviceAdded(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_AUDIO_DEVICE_ADDED
    virtual void onAudioDeviceRemoved(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_AUDIO_DEVICE_REMOVED
    virtual void onAudioDeviceFormatChanged(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED

    // ==================== CAMERA EVENTS ====================
    virtual void onCameraDeviceAdded(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_CAMERA_DEVICE_ADDED
    virtual void onCameraDeviceRemoved(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_CAMERA_DEVICE_REMOVED
    virtual void onCameraDeviceApproved(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_CAMERA_DEVICE_APPROVED
    virtual void onCameraDeviceDenied(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_CAMERA_DEVICE_DENIED

    // ==================== SENSOR EVENTS ====================
    virtual void onSensorUpdate(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_SENSOR_UPDATE

    // ==================== TOUCH EVENTS ====================
    virtual void onFingerDown(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_FINGER_DOWN
    virtual void onFingerUp(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_FINGER_UP
    virtual void onFingerMotion(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_FINGER_MOTION

    // ==================== GESTURE EVENTS ====================
    virtual void onPinchBegin(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PINCH_BEGIN
    virtual void onPinchRotate(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PINCH_ROTATE
    virtual void onPinchEnd(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PINCH_END

    // ==================== PEN EVENTS ====================
    virtual void onPenProximityIn(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PEN_PROXIMITY_IN
    virtual void onPenProximityOut(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PEN_PROXIMITY_OUT
    virtual void onPenDown(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PEN_DOWN
    virtual void onPenUp(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PEN_UP
    virtual void onPenMotion(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PEN_MOTION
    virtual void onPenButtonDown(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PEN_BUTTON_DOWN
    virtual void onPenButtonUp(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PEN_BUTTON_UP
    virtual void onPenAxis(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_PEN_AXIS

    // ==================== RENDER EVENTS ====================
    virtual void onRenderTargetsReset(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_RENDER_TARGETS_RESET
    virtual void onRenderDeviceReset(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_RENDER_DEVICE_RESET
    virtual void onRenderDeviceLost(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_RENDER_DEVICE_LOST

    // ==================== DROP EVENTS ====================
    virtual void onDropBegin(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DROP_BEGIN
    virtual void onDropFile(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DROP_FILE
    virtual void onDropText(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DROP_TEXT
    virtual void onDropComplete(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DROP_COMPLETE
    virtual void onDropPosition(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DROP_POSITION

    // ==================== CLIPBOARD EVENTS ====================
    virtual void onClipboardUpdate(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_CLIPBOARD_UPDATE

    // ==================== APPLICATION EVENTS ====================
    virtual void onQuit(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_QUIT
    virtual void onTerminating(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_TERMINATING
    virtual void onLowMemory(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_LOW_MEMORY
    virtual void onWillEnterBackground(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WILL_ENTER_BACKGROUND
    virtual void onDidEnterBackground(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DID_ENTER_BACKGROUND
    virtual void onWillEnterForeground(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_WILL_ENTER_FOREGROUND
    virtual void onDidEnterForeground(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_DID_ENTER_FOREGROUND
    virtual void onLocaleChanged(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_LOCALE_CHANGED
    virtual void onSystemThemeChanged(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_SYSTEM_THEME_CHANGED

    // ==================== USER EVENTS ====================
    virtual void onUserEvent(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...); // SDL_EVENT_USER

    // ==================== GENERIC EVENT HANDLER ====================
    virtual void onEvent(Window&, Events&, Manager&, SubWindow_l&, ExtraData&...);

    // ==================== RUNTIME METHODS ====================
    virtual void runtime(void);
    std::thread run_async(void);
    void run_block();

protected:
    // Helper method to dispatch events
    void dispatchEvents(ExtraData&... extra);
};
