#pragma once

#include "Definitions.hpp"

template <class Key, class... ExtraData>
WSDC::Engine<Key, ExtraData...>::Engine() : is_running(false) {
    try {
        sub_windows.root(&display);
        manager.window(display).events(events);
        text.renderer(display.raw.renderer);
    } catch (...) {
        throw std::runtime_error("[Engine::Engine] init failed");
    }
}

template <class Key, class... ExtraData>
WSDC::Engine<Key, ExtraData...>::~Engine() {
    quit();
}

template <class Key, class... ExtraData>
void WSDC::Engine<Key, ExtraData...>::isRunning(const bool& b) noexcept {
    is_running.store(b);
}

template <class Key, class... ExtraData>
bool WSDC::Engine<Key, ExtraData...>::isRunning(void) noexcept {
    return is_running.load();
}

template <class Key, class... ExtraData>
template <typename... Args>
void WSDC::Engine<Key, ExtraData...>::write(const std::string& _font, const WSDC::Geo::Rect<int>& _position, const std::string& _text, Args... _args) {
    text.write(_font, _position, _text, _args...);
}

template <class Key, class... ExtraData>
void WSDC::Engine<Key, ExtraData...>::fps(const float& _fps) noexcept {
    FPS = static_cast<Uint64>(1000.f / _fps);
}

template <class Key, class... ExtraData>
void WSDC::Engine<Key, ExtraData...>::set_extra(ExtraData&... data) {
    try {
        extra_data = std::make_tuple(&data...);
        manager.extra(sub_windows, text, data...);
    } catch (...) {
        throw std::runtime_error("Engine<>::set_extra");
    }
}

template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowShown() /* SDL_EVENT_WINDOW_SHOWN */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowHidden() /* SDL_EVENT_WINDOW_HIDDEN */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowExposed() /* SDL_EVENT_WINDOW_EXPOSED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowMoved() /* SDL_EVENT_WINDOW_MOVED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowResized() /* SDL_EVENT_WINDOW_RESIZED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowPixelSizeChanged() /* SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowMetalViewResized() /* SDL_EVENT_WINDOW_METAL_VIEW_RESIZED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowMinimized() /* SDL_EVENT_WINDOW_MINIMIZED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowMaximized() /* SDL_EVENT_WINDOW_MAXIMIZED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowRestored() /* SDL_EVENT_WINDOW_RESTORED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowMouseEnter() /* SDL_EVENT_WINDOW_MOUSE_ENTER */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowMouseLeave() /* SDL_EVENT_WINDOW_MOUSE_LEAVE */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowFocusGained() /* SDL_EVENT_WINDOW_FOCUS_GAINED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowFocusLost() /* SDL_EVENT_WINDOW_FOCUS_LOST */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowCloseRequested() /* SDL_EVENT_WINDOW_CLOSE_REQUESTED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowHitTest() /* SDL_EVENT_WINDOW_HIT_TEST */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowICCProfChanged() /* SDL_EVENT_WINDOW_ICCPROF_CHANGED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowDisplayChanged() /* SDL_EVENT_WINDOW_DISPLAY_CHANGED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowDisplayScaleChanged() /* SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowSafeAreaChanged() /* SDL_EVENT_WINDOW_SAFE_AREA_CHANGED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowOccluded() /* SDL_EVENT_WINDOW_OCCLUDED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowEnterFullscreen() /* SDL_EVENT_WINDOW_ENTER_FULLSCREEN */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowLeaveFullscreen() /* SDL_EVENT_WINDOW_LEAVE_FULLSCREEN */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowDestroyed() /* SDL_EVENT_WINDOW_DESTROYED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowPenEnter() /* SDL_EVENT_WINDOW_PEN_ENTER */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWindowPenLeave() /* SDL_EVENT_WINDOW_PEN_LEAVE */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onDisplayOrientation() /* SDL_EVENT_DISPLAY_ORIENTATION */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onDisplayAdded() /* SDL_EVENT_DISPLAY_ADDED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onDisplayRemoved() /* SDL_EVENT_DISPLAY_REMOVED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onDisplayMoved() /* SDL_EVENT_DISPLAY_MOVED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onDisplayContentScaleChanged() /* SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onKeyboardAdded() /* SDL_EVENT_KEYBOARD_ADDED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onKeyboardRemoved() /* SDL_EVENT_KEYBOARD_REMOVED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onKeyDown() /* SDL_EVENT_KEY_DOWN */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onKeyUp() /* SDL_EVENT_KEY_UP */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onTextEditing() /* SDL_EVENT_TEXT_EDITING */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onTextEditingCandidates() /* SDL_EVENT_TEXT_EDITING_CANDIDATES */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onTextInput() /* SDL_EVENT_TEXT_INPUT */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onMouseAdded() /* SDL_EVENT_MOUSE_ADDED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onMouseRemoved() /* SDL_EVENT_MOUSE_REMOVED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onMouseMotion() /* SDL_EVENT_MOUSE_MOTION */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onMouseButtonDown() /* SDL_EVENT_MOUSE_BUTTON_DOWN */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onMouseButtonUp() /* SDL_EVENT_MOUSE_BUTTON_UP */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onMouseWheel() /* SDL_EVENT_MOUSE_WHEEL */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onJoystickAdded() /* SDL_EVENT_JOYSTICK_ADDED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onJoystickRemoved() /* SDL_EVENT_JOYSTICK_REMOVED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onJoystickUpdateComplete() /* SDL_EVENT_JOYSTICK_UPDATE_COMPLETE */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onJoystickAxisMotion() /* SDL_EVENT_JOYSTICK_AXIS_MOTION */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onJoystickBallMotion() /* SDL_EVENT_JOYSTICK_BALL_MOTION */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onJoystickHatMotion() /* SDL_EVENT_JOYSTICK_HAT_MOTION */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onJoystickButtonDown() /* SDL_EVENT_JOYSTICK_BUTTON_DOWN */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onJoystickButtonUp() /* SDL_EVENT_JOYSTICK_BUTTON_UP */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onJoystickBatteryUpdated() /* SDL_EVENT_JOYSTICK_BATTERY_UPDATED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onGamepadAdded() /* SDL_EVENT_GAMEPAD_ADDED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onGamepadRemoved() /* SDL_EVENT_GAMEPAD_REMOVED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onGamepadRemapped() /* SDL_EVENT_GAMEPAD_REMAPPED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onGamepadUpdateComplete() /* SDL_EVENT_GAMEPAD_UPDATE_COMPLETE */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onGamepadSteamHandleUpdated() /* SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onGamepadAxisMotion() /* SDL_EVENT_GAMEPAD_AXIS_MOTION */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onGamepadButtonDown() /* SDL_EVENT_GAMEPAD_BUTTON_DOWN */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onGamepadButtonUp() /* SDL_EVENT_GAMEPAD_BUTTON_UP */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onGamepadTouchpadDown() /* SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onGamepadTouchpadMotion() /* SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onGamepadTouchpadUp() /* SDL_EVENT_GAMEPAD_TOUCHPAD_UP */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onGamepadSensorUpdate() /* SDL_EVENT_GAMEPAD_SENSOR_UPDATE */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onAudioDeviceAdded() /* SDL_EVENT_AUDIO_DEVICE_ADDED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onAudioDeviceRemoved() /* SDL_EVENT_AUDIO_DEVICE_REMOVED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onAudioDeviceFormatChanged() /* SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onCameraDeviceAdded() /* SDL_EVENT_CAMERA_DEVICE_ADDED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onCameraDeviceRemoved() /* SDL_EVENT_CAMERA_DEVICE_REMOVED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onCameraDeviceApproved() /* SDL_EVENT_CAMERA_DEVICE_APPROVED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onCameraDeviceDenied() /* SDL_EVENT_CAMERA_DEVICE_DENIED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onSensorUpdate() /* SDL_EVENT_SENSOR_UPDATE */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onFingerDown() /* SDL_EVENT_FINGER_DOWN */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onFingerUp() /* SDL_EVENT_FINGER_UP */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onFingerMotion() /* SDL_EVENT_FINGER_MOTION */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onPinchBegin() /* SDL_EVENT_PINCH_BEGIN */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onPinchRotate() /* SDL_EVENT_PINCH_ROTATE */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onPinchEnd() /* SDL_EVENT_PINCH_END */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onPenProximityIn() /* SDL_EVENT_PEN_PROXIMITY_IN */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onPenProximityOut() /* SDL_EVENT_PEN_PROXIMITY_OUT */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onPenDown() /* SDL_EVENT_PEN_DOWN */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onPenUp() /* SDL_EVENT_PEN_UP */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onPenMotion() /* SDL_EVENT_PEN_MOTION */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onPenButtonDown() /* SDL_EVENT_PEN_BUTTON_DOWN */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onPenButtonUp() /* SDL_EVENT_PEN_BUTTON_UP */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onPenAxis() /* SDL_EVENT_PEN_AXIS */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onRenderTargetsReset() /* SDL_EVENT_RENDER_TARGETS_RESET */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onRenderDeviceReset() /* SDL_EVENT_RENDER_DEVICE_RESET */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onRenderDeviceLost() /* SDL_EVENT_RENDER_DEVICE_LOST */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onDropBegin() /* SDL_EVENT_DROP_BEGIN */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onDropFile() /* SDL_EVENT_DROP_FILE */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onDropText() /* SDL_EVENT_DROP_TEXT */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onDropComplete() /* SDL_EVENT_DROP_COMPLETE */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onDropPosition() /* SDL_EVENT_DROP_POSITION */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onClipboardUpdate() /* SDL_EVENT_CLIPBOARD_UPDATE */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onQuit() /* SDL_EVENT_QUIT */ { quit(); }
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onTerminating() /* SDL_EVENT_TERMINATING */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onLowMemory() /* SDL_EVENT_LOW_MEMORY */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWillEnterBackground() /* SDL_EVENT_WILL_ENTER_BACKGROUND */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onDidEnterBackground() /* SDL_EVENT_DID_ENTER_BACKGROUND */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onWillEnterForeground() /* SDL_EVENT_WILL_ENTER_FOREGROUND */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onDidEnterForeground() /* SDL_EVENT_DID_ENTER_FOREGROUND */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onLocaleChanged() /* SDL_EVENT_LOCALE_CHANGED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onSystemThemeChanged() /* SDL_EVENT_SYSTEM_THEME_CHANGED */ {}
template <class Key, class... ExtraData> void WSDC::Engine<Key, ExtraData...>::onUserEvent() /* SDL_EVENT_USER */ {}

template <class Key, class... ExtraData>
void WSDC::Engine<Key, ExtraData...>::quit(void) {
    is_running = false;
    display.close();

    for (auto& win : sub_windows) {
        win.close();
    }
}

template <class Key, class... ExtraData>
void WSDC::Engine<Key, ExtraData...>::update(void) {
    display.update();

    if (!sub_windows.empty()) {
        for (auto& d : sub_windows) {
            d.update();
        }
    }
}

template <class Key, class... ExtraData>
void WSDC::Engine<Key, ExtraData...>::runtime() {
    while (true) {
        if (!(is_running.load())) break;

        while (last_frame_time - SDL_GetTicks() < FPS) {
            SDL_Delay(1);
        }

        events.update();

        if (use_onEvents) {
            dispatchEvents();
        }

        manager.run();

        update();
        last_frame_time = SDL_GetTicks();
    }
}

template <class Key, class... ExtraData>
std::thread WSDC::Engine<Key, ExtraData...>::run_async_mod() {
    return std::thread([this](void) -> void { runtime(); });
}

template <class Key, class... ExtraData>
void WSDC::Engine<Key, ExtraData...>::run_async(std::thread& thread) {
    if (is_running == false) {
        throw std::runtime_error("Cannot execute with isRunning() == false");
    }

    thread = run_async_mod();
}

template <class Key, class... ExtraData>
void WSDC::Engine<Key, ExtraData...>::run_block_mod() {
    runtime();
}

template <class Key, class... ExtraData>
void WSDC::Engine<Key, ExtraData...>::run_block() {
    if (is_running == false) {
        throw std::runtime_error("Cannot execute with isRunning() == false");
    }

    run_block_mod();
}

template <class Key, class... ExtraData>
void WSDC::Engine<Key, ExtraData...>::dispatchEvents() {
    if (events & WSDC::Event::Display::ORIENTATION) onDisplayOrientation();
    if (events & WSDC::Event::Display::ADDED) onDisplayAdded();
    if (events & WSDC::Event::Display::REMOVED) onDisplayRemoved();
    if (events & WSDC::Event::Display::CONTENT_SCALE_CHANGED) onDisplayContentScaleChanged();
    if (events & WSDC::Event::Display::MOVED) onDisplayMoved();

    if (events & WSDC::Event::Window::CLOSE) onWindowCloseRequested();
    if (events & WSDC::Event::Window::DESTROYED) onWindowDestroyed();
    if (events & WSDC::Event::Window::DISPLAY_CHANGED) onWindowDisplayChanged();
    if (events & WSDC::Event::Window::DISPLAY_SCALE_CHANGED) onWindowDisplayScaleChanged();
    if (events & WSDC::Event::Window::ENTER_FULLSCREEN) onWindowEnterFullscreen();
    if (events & WSDC::Event::Window::EXPOSED) onWindowExposed();
    if (events & WSDC::Event::Window::FOCUS_GAINED) onWindowFocusGained();
    if (events & WSDC::Event::Window::FOCUS_LOST) onWindowFocusLost();
    if (events & WSDC::Event::Window::HIDDEN) onWindowHidden();
    if (events & WSDC::Event::Window::HIT_TEST) onWindowHitTest();
    if (events & WSDC::Event::Window::ICCPROF_CHANGED) onWindowICCProfChanged();
    if (events & WSDC::Event::Window::LEAVE_FULLSCREEN) onWindowLeaveFullscreen();
    if (events & WSDC::Event::Window::MAXIMIZED) onWindowMaximized();
    if (events & WSDC::Event::Window::METAL_VIEW_RESIZED) onWindowMetalViewResized();
    if (events & WSDC::Event::Window::MINIMIZED) onWindowMinimized();
    if (events & WSDC::Event::Window::MOUSE_ENTER) onWindowMouseEnter();
    if (events & WSDC::Event::Window::MOUSE_LEAVE) onWindowMouseLeave();
    if (events & WSDC::Event::Window::MOVED) onWindowMoved();
    if (events & WSDC::Event::Window::OCCLUDED) onWindowOccluded();
    if (events & WSDC::Event::Window::PIXEL_SIZE_CHANGED) onWindowPixelSizeChanged();
    if (events & WSDC::Event::Window::RESIZED) onWindowResized();
    if (events & WSDC::Event::Window::RESTORED) onWindowRestored();
    if (events & WSDC::Event::Window::SAFE_AREA_CHANGED) onWindowSafeAreaChanged();
    if (events & WSDC::Event::Window::SHOWN) onWindowShown();

    if (events & WSDC::Event::Keyboard::DEVICE_ADDED) onKeyboardAdded();
    if (events & WSDC::Event::Keyboard::DEVICE_REMOVED) onKeyboardRemoved();
    if (events & WSDC::Event::Keyboard::TEXT_EDITING) onTextEditing();
    if (events & WSDC::Event::Keyboard::TEXT_EDITING_CANDIDATES) onTextEditingCandidates();
    if (events & WSDC::Event::Keyboard::TEXT_INPUT) onTextInput();

    if (events & WSDC::Event::Mouse::DEVICE_ADDED) onMouseAdded();
    if (events & WSDC::Event::Mouse::DEVICE_REMOVED) onMouseRemoved();
    if (events & (WSDC::Event::Mouse_DOWN)) onMouseButtonDown();
    if (events & (WSDC::Event::Mouse_UP)) onMouseButtonUp();
    if (events & WSDC::Event::Mouse::MOTION) onMouseMotion();
    if (events & WSDC::Event::Mouse::WHEEL) onMouseWheel();

    if (events & WSDC::Event::Joystick::ADDED) onJoystickAdded();
    if (events & WSDC::Event::Joystick::AXIS_MOTION) onJoystickAxisMotion();
    if (events & WSDC::Event::Joystick::BALL_MOTION) onJoystickBallMotion();
    if (events & WSDC::Event::Joystick::BATTERY_UPDATED) onJoystickBatteryUpdated();
    if (events & WSDC::Event::Joystick::BUTTON_DOWN) onJoystickButtonDown();
    if (events & WSDC::Event::Joystick::BUTTON_UP) onJoystickButtonUp();
    if (events & WSDC::Event::Joystick::HAT_MOTION) onJoystickHatMotion();
    if (events & WSDC::Event::Joystick::REMOVED) onJoystickRemoved();
    if (events & WSDC::Event::Joystick::UPDATE_COMPLETE) onJoystickUpdateComplete();

    if (events & WSDC::Event::Gamepad::ADDED) onGamepadAdded();
    if (events & WSDC::Event::Gamepad::AXIS_MOTION) onGamepadAxisMotion();
    if (events & WSDC::Event::Gamepad::BUTTON_DOWN) onGamepadButtonDown();
    if (events & WSDC::Event::Gamepad::BUTTON_UP) onGamepadButtonUp();
    if (events & WSDC::Event::Gamepad::REMAPPED) onGamepadRemapped();
    if (events & WSDC::Event::Gamepad::REMOVED) onGamepadRemoved();
    if (events & WSDC::Event::Gamepad::SENSOR_UPDATE) onGamepadSensorUpdate();
    if (events & WSDC::Event::Gamepad::STEAM_HANDLE_UPDATED) onGamepadSteamHandleUpdated();
    if (events & WSDC::Event::Gamepad::TOUCHPAD_DOWN) onGamepadTouchpadDown();
    if (events & WSDC::Event::Gamepad::TOUCHPAD_MOTION) onGamepadTouchpadMotion();
    if (events & WSDC::Event::Gamepad::TOUCHPAD_UP) onGamepadTouchpadUp();
    if (events & WSDC::Event::Gamepad::UPDATE_COMPLETE) onGamepadUpdateComplete();

    if (events & WSDC::Event::Audio::DEVICE_ADDED) onAudioDeviceAdded();
    if (events & WSDC::Event::Audio::DEVICE_FORMAT_CHANGED) onAudioDeviceFormatChanged();
    if (events & WSDC::Event::Audio::DEVICE_REMOVED) onAudioDeviceRemoved();

    if (events & WSDC::Event::Camera::DEVICE_ADDED) onCameraDeviceAdded();
    if (events & WSDC::Event::Camera::DEVICE_APPROVED) onCameraDeviceApproved();
    if (events & WSDC::Event::Camera::DEVICE_DENIED) onCameraDeviceDenied();
    if (events & WSDC::Event::Camera::DEVICE_REMOVED) onCameraDeviceRemoved();

    if (events & WSDC::Event::Sensor::UPDATE) onSensorUpdate();

    if (events & WSDC::Event::System::DID_ENTER_BACKGROUND) onDidEnterBackground();
    if (events & WSDC::Event::System::DID_ENTER_FOREGROUND) onDidEnterForeground();
    if (events & WSDC::Event::System::LOCALE_CHANGED) onLocaleChanged();
    if (events & WSDC::Event::System::LOW_MEMORY) onLowMemory();
    if (events & WSDC::Event::System::QUIT) onQuit();
    if (events & WSDC::Event::System::SYSTEM_THEME_CHANGED) onSystemThemeChanged();
    if (events & WSDC::Event::System::TERMINATING) onTerminating();
    if (events & WSDC::Event::System::WILL_ENTER_BACKGROUND) onWillEnterBackground();
    if (events & WSDC::Event::System::WILL_ENTER_FOREGROUND) onWillEnterForeground();

    if (events & WSDC::Event::User::EVENT) onUserEvent();

    if (events & WSDC::Event::Touch::FINGER_DOWN) onFingerDown();
    if (events & WSDC::Event::Touch::FINGER_UP) onFingerUp();
    if (events & WSDC::Event::Touch::FINGER_MOTION) onFingerMotion();

    if (events & WSDC::Event::Pen::AXIS) onPenAxis();
    if (events & WSDC::Event::Pen::BUTTON_DOWN) onPenButtonDown();
    if (events & WSDC::Event::Pen::BUTTON_UP) onPenButtonUp();
    if (events & WSDC::Event::Pen::DOWN) onPenDown();
    if (events & WSDC::Event::Pen::MOTION) onPenMotion();
    if (events & WSDC::Event::Pen::PROXIMITY_IN) onPenProximityIn();
    if (events & WSDC::Event::Pen::PROXIMITY_OUT) onPenProximityOut();
    if (events & WSDC::Event::Pen::UP) onPenUp();

    if (events & WSDC::Event::Render::DEVICE_LOST) onRenderDeviceLost();
    if (events & WSDC::Event::Render::DEVICE_RESET) onRenderDeviceReset();
    if (events & WSDC::Event::Render::TARGETS_RESET) onRenderTargetsReset();

    if (events & WSDC::Event::Drop::BEGIN) onDropBegin();
    if (events & WSDC::Event::Drop::COMPLETE) onDropComplete();
    if (events & WSDC::Event::Drop::FILE) onDropFile();
    if (events & WSDC::Event::Drop::POSITION) onDropPosition();
    if (events & WSDC::Event::Drop::TEXT) onDropText();

    if (events & WSDC::Event::Clipboard::UPDATE) onClipboardUpdate();
}
