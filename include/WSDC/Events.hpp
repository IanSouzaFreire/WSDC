#pragma once

#include <vector>
#include <SDL3/SDL_events.h>
#include <vector>
#include <SDL3/SDL_events.h>

struct Events {
    const bool *key_states;
    std::vector<Uint32> type;
    std::vector<SDL_CommonEvent> common;
    std::vector<SDL_DisplayEvent> display;
    std::vector<SDL_WindowEvent> window;
    std::vector<SDL_KeyboardDeviceEvent> kdevice;
    std::vector<SDL_KeyboardEvent> key;
    std::vector<SDL_TextEditingEvent> edit;
    std::vector<SDL_TextEditingCandidatesEvent> edit_candidates;
    std::vector<SDL_TextInputEvent> text;
    std::vector<SDL_MouseDeviceEvent> mdevice;
    std::vector<SDL_MouseMotionEvent> motion;
    std::vector<SDL_MouseButtonEvent> button;
    std::vector<SDL_MouseWheelEvent> wheel;
    std::vector<SDL_JoyDeviceEvent> jdevice;
    std::vector<SDL_JoyAxisEvent> jaxis;
    std::vector<SDL_JoyBallEvent> jball;
    std::vector<SDL_JoyHatEvent> jhat;
    std::vector<SDL_JoyButtonEvent> jbutton;
    std::vector<SDL_JoyBatteryEvent> jbattery;
    std::vector<SDL_GamepadDeviceEvent> gdevice;
    std::vector<SDL_GamepadAxisEvent> gaxis;
    std::vector<SDL_GamepadButtonEvent> gbutton;
    std::vector<SDL_GamepadTouchpadEvent> gtouchpad;
    std::vector<SDL_GamepadSensorEvent> gsensor;
    std::vector<SDL_AudioDeviceEvent> adevice;
    std::vector<SDL_CameraDeviceEvent> cdevice;
    std::vector<SDL_SensorEvent> sensor;
    std::vector<SDL_QuitEvent> quit;
    std::vector<SDL_UserEvent> user;
    std::vector<SDL_TouchFingerEvent> tfinger;
    // std::vector<SDL_PinchFingerEvent> pinch;
    std::vector<SDL_PenProximityEvent> pproximity;
    std::vector<SDL_PenTouchEvent> ptouch;
    std::vector<SDL_PenMotionEvent> pmotion;
    std::vector<SDL_PenButtonEvent> pbutton;
    std::vector<SDL_PenAxisEvent> paxis;
    std::vector<SDL_RenderEvent> render;
    std::vector<SDL_DropEvent> drop;
    std::vector<SDL_ClipboardEvent> clipboard;

    Events& update() {
        clear();

        key_states = SDL_GetKeyboardState(NULL);
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            type.push_back(event.type);
            
            switch (event.type) {
                case SDL_EVENT_DISPLAY_ORIENTATION:
                case SDL_EVENT_DISPLAY_ADDED:
                case SDL_EVENT_DISPLAY_REMOVED:
                case SDL_EVENT_DISPLAY_MOVED:
                case SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED:
                    display.push_back(event.display);
                    break;
                    
                case SDL_EVENT_WINDOW_SHOWN:
                case SDL_EVENT_WINDOW_HIDDEN:
                case SDL_EVENT_WINDOW_EXPOSED:
                case SDL_EVENT_WINDOW_MOVED:
                case SDL_EVENT_WINDOW_RESIZED:
                case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
                case SDL_EVENT_WINDOW_METAL_VIEW_RESIZED:
                case SDL_EVENT_WINDOW_MINIMIZED:
                case SDL_EVENT_WINDOW_MAXIMIZED:
                case SDL_EVENT_WINDOW_RESTORED:
                case SDL_EVENT_WINDOW_MOUSE_ENTER:
                case SDL_EVENT_WINDOW_MOUSE_LEAVE:
                case SDL_EVENT_WINDOW_FOCUS_GAINED:
                case SDL_EVENT_WINDOW_FOCUS_LOST:
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                case SDL_EVENT_WINDOW_HIT_TEST:
                case SDL_EVENT_WINDOW_ICCPROF_CHANGED:
                case SDL_EVENT_WINDOW_DISPLAY_CHANGED:
                case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED:
                case SDL_EVENT_WINDOW_SAFE_AREA_CHANGED:
                case SDL_EVENT_WINDOW_OCCLUDED:
                case SDL_EVENT_WINDOW_ENTER_FULLSCREEN:
                case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN:
                case SDL_EVENT_WINDOW_DESTROYED:
                /*
                case SDL_EVENT_WINDOW_PEN_ENTER:
                case SDL_EVENT_WINDOW_PEN_LEAVE:
                    window.push_back(event.window);
                    break;
                */
                    
                case SDL_EVENT_KEYBOARD_ADDED:
                case SDL_EVENT_KEYBOARD_REMOVED:
                    kdevice.push_back(event.kdevice);
                    break;
                    
                case SDL_EVENT_KEY_DOWN:
                case SDL_EVENT_KEY_UP:
                    key.push_back(event.key);
                    break;
                    
                case SDL_EVENT_TEXT_EDITING:
                    edit.push_back(event.edit);
                    break;
                    
                case SDL_EVENT_TEXT_EDITING_CANDIDATES:
                    edit_candidates.push_back(event.edit_candidates);
                    break;
                    
                case SDL_EVENT_TEXT_INPUT:
                    text.push_back(event.text);
                    break;
                    
                case SDL_EVENT_MOUSE_ADDED:
                case SDL_EVENT_MOUSE_REMOVED:
                    mdevice.push_back(event.mdevice);
                    break;
                    
                case SDL_EVENT_MOUSE_MOTION:
                    motion.push_back(event.motion);
                    break;
                    
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    button.push_back(event.button);
                    break;
                    
                case SDL_EVENT_MOUSE_WHEEL:
                    wheel.push_back(event.wheel);
                    break;
                    
                case SDL_EVENT_JOYSTICK_ADDED:
                case SDL_EVENT_JOYSTICK_REMOVED:
                case SDL_EVENT_JOYSTICK_UPDATE_COMPLETE:
                    jdevice.push_back(event.jdevice);
                    break;
                    
                case SDL_EVENT_JOYSTICK_AXIS_MOTION:
                    jaxis.push_back(event.jaxis);
                    break;
                    
                case SDL_EVENT_JOYSTICK_BALL_MOTION:
                    jball.push_back(event.jball);
                    break;
                    
                case SDL_EVENT_JOYSTICK_HAT_MOTION:
                    jhat.push_back(event.jhat);
                    break;
                    
                case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
                case SDL_EVENT_JOYSTICK_BUTTON_UP:
                    jbutton.push_back(event.jbutton);
                    break;
                    
                case SDL_EVENT_JOYSTICK_BATTERY_UPDATED:
                    jbattery.push_back(event.jbattery);
                    break;
                    
                case SDL_EVENT_GAMEPAD_ADDED:
                case SDL_EVENT_GAMEPAD_REMOVED:
                case SDL_EVENT_GAMEPAD_REMAPPED:
                case SDL_EVENT_GAMEPAD_UPDATE_COMPLETE:
                case SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED:
                    gdevice.push_back(event.gdevice);
                    break;
                    
                case SDL_EVENT_GAMEPAD_AXIS_MOTION:
                    gaxis.push_back(event.gaxis);
                    break;
                    
                case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
                case SDL_EVENT_GAMEPAD_BUTTON_UP:
                    gbutton.push_back(event.gbutton);
                    break;
                    
                case SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN:
                case SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION:
                case SDL_EVENT_GAMEPAD_TOUCHPAD_UP:
                    gtouchpad.push_back(event.gtouchpad);
                    break;
                    
                case SDL_EVENT_GAMEPAD_SENSOR_UPDATE:
                    gsensor.push_back(event.gsensor);
                    break;
                    
                case SDL_EVENT_AUDIO_DEVICE_ADDED:
                case SDL_EVENT_AUDIO_DEVICE_REMOVED:
                case SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED:
                    adevice.push_back(event.adevice);
                    break;
                    
                case SDL_EVENT_CAMERA_DEVICE_ADDED:
                case SDL_EVENT_CAMERA_DEVICE_REMOVED:
                case SDL_EVENT_CAMERA_DEVICE_APPROVED:
                case SDL_EVENT_CAMERA_DEVICE_DENIED:
                    cdevice.push_back(event.cdevice);
                    break;
                    
                case SDL_EVENT_SENSOR_UPDATE:
                    sensor.push_back(event.sensor);
                    break;
                    
                case SDL_EVENT_QUIT:
                case SDL_EVENT_TERMINATING:
                case SDL_EVENT_LOW_MEMORY:
                case SDL_EVENT_WILL_ENTER_BACKGROUND:
                case SDL_EVENT_DID_ENTER_BACKGROUND:
                case SDL_EVENT_WILL_ENTER_FOREGROUND:
                case SDL_EVENT_DID_ENTER_FOREGROUND:
                case SDL_EVENT_LOCALE_CHANGED:
                case SDL_EVENT_SYSTEM_THEME_CHANGED:
                    quit.push_back(event.quit);
                    break;
                    
                case SDL_EVENT_USER:
                    user.push_back(event.user);
                    break;
                    
                case SDL_EVENT_FINGER_DOWN:
                case SDL_EVENT_FINGER_UP:
                case SDL_EVENT_FINGER_MOTION:
                    tfinger.push_back(event.tfinger);
                    break;
                /*
                case SDL_EVENT_PINCH_BEGIN:
                case SDL_EVENT_PINCH_ROTATE:
                case SDL_EVENT_PINCH_END:
                    pinch.push_back(event.pinch);
                    break;
                */
                case SDL_EVENT_PEN_PROXIMITY_IN:
                case SDL_EVENT_PEN_PROXIMITY_OUT:
                    pproximity.push_back(event.pproximity);
                    break;
                    
                case SDL_EVENT_PEN_DOWN:
                case SDL_EVENT_PEN_UP:
                    ptouch.push_back(event.ptouch);
                    break;
                    
                case SDL_EVENT_PEN_MOTION:
                    pmotion.push_back(event.pmotion);
                    break;
                    
                case SDL_EVENT_PEN_BUTTON_DOWN:
                case SDL_EVENT_PEN_BUTTON_UP:
                    pbutton.push_back(event.pbutton);
                    break;
                    
                case SDL_EVENT_PEN_AXIS:
                    paxis.push_back(event.paxis);
                    break;
                    
                case SDL_EVENT_RENDER_TARGETS_RESET:
                case SDL_EVENT_RENDER_DEVICE_RESET:
                case SDL_EVENT_RENDER_DEVICE_LOST:
                    render.push_back(event.render);
                    break;
                    
                case SDL_EVENT_DROP_BEGIN:
                case SDL_EVENT_DROP_FILE:
                case SDL_EVENT_DROP_TEXT:
                case SDL_EVENT_DROP_COMPLETE:
                case SDL_EVENT_DROP_POSITION:
                    drop.push_back(event.drop);
                    break;
                    
                case SDL_EVENT_CLIPBOARD_UPDATE:
                    clipboard.push_back(event.clipboard);
                    break;
                    
                default:
                    common.push_back(event.common);
                    break;
            }
        }
        
        return *this;
    }
    
    Events& clear() {
        type.clear();
        common.clear();
        display.clear();
        window.clear();
        kdevice.clear();
        key.clear();
        edit.clear();
        edit_candidates.clear();
        text.clear();
        mdevice.clear();
        motion.clear();
        button.clear();
        wheel.clear();
        jdevice.clear();
        jaxis.clear();
        jball.clear();
        jhat.clear();
        jbutton.clear();
        jbattery.clear();
        gdevice.clear();
        gaxis.clear();
        gbutton.clear();
        gtouchpad.clear();
        gsensor.clear();
        adevice.clear();
        cdevice.clear();
        sensor.clear();
        quit.clear();
        user.clear();
        tfinger.clear();
        // pinch.clear();
        pproximity.clear();
        ptouch.clear();
        pmotion.clear();
        pbutton.clear();
        paxis.clear();
        render.clear();
        drop.clear();
        clipboard.clear();

        return *this;
    }

    bool isPressed(const SDL_Scancode& scan) {
        return key_states[scan];
    }

    bool isInTypes(const Uint32& c) { for ( const auto& ev : type) if (ev == c) return true; return false; } // does not work on this one
    bool isInCommonEvents(const SDL_CommonEvent& c) { for ( const auto& ev : common) if (ev.type == c.type) return true; return false; }
    bool isInDisplayEvents(const SDL_DisplayEvent& c) { for ( const auto& ev : display) if (ev.type == c.type) return true; return false; }
    bool isInWindowEvents(const SDL_WindowEvent& c) { for ( const auto& ev : window) if (ev.type == c.type) return true; return false; }
    bool isInKeyboardDeviceEvents(const SDL_KeyboardDeviceEvent& c) { for ( const auto& ev : kdevice) if (ev.type == c.type) return true; return false; }
    bool isInKeyboardEvents(const SDL_KeyboardEvent& c) { for ( const auto& ev : key) if (ev.type == c.type) return true; return false; }
    bool isInTextEditingEvents(const SDL_TextEditingEvent& c) { for ( const auto& ev : edit) if (ev.type == c.type) return true; return false; }
    bool isInTextEditingCandidatesEvents(const SDL_TextEditingCandidatesEvent& c) { for ( const auto& ev : edit_candidates) if (ev.type == c.type) return true; return false; }
    bool isInTextInputEvents(const SDL_TextInputEvent& c) { for ( const auto& ev : text) if (ev.type == c.type) return true; return false; }
    bool isInMouseDeviceEvents(const SDL_MouseDeviceEvent& c) { for ( const auto& ev : mdevice) if (ev.type == c.type) return true; return false; }
    bool isInMouseMotionEvents(const SDL_MouseMotionEvent& c) { for ( const auto& ev : motion) if (ev.type == c.type) return true; return false; }
    bool isInMouseButtonEvents(const SDL_MouseButtonEvent& c) { for ( const auto& ev : button) if (ev.type == c.type) return true; return false; }
    bool isInMouseWheelEvents(const SDL_MouseWheelEvent& c) { for ( const auto& ev : wheel) if (ev.type == c.type) return true; return false; }
    bool isInJoyDeviceEvents(const SDL_JoyDeviceEvent& c) { for ( const auto& ev : jdevice) if (ev.type == c.type) return true; return false; }
    bool isInJoyAxisEvents(const SDL_JoyAxisEvent& c) { for ( const auto& ev : jaxis) if (ev.type == c.type) return true; return false; }
    bool isInJoyBallEvents(const SDL_JoyBallEvent& c) { for ( const auto& ev : jball) if (ev.type == c.type) return true; return false; }
    bool isInJoyHatEvents(const SDL_JoyHatEvent& c) { for ( const auto& ev : jhat) if (ev.type == c.type) return true; return false; }
    bool isInJoyButtonEvents(const SDL_JoyButtonEvent& c) { for ( const auto& ev : jbutton) if (ev.type == c.type) return true; return false; }
    bool isInJoyBatteryEvents(const SDL_JoyBatteryEvent& c) { for ( const auto& ev : jbattery) if (ev.type == c.type) return true; return false; }
    bool isInGamepadDeviceEvents(const SDL_GamepadDeviceEvent& c) { for ( const auto& ev : gdevice) if (ev.type == c.type) return true; return false; }
    bool isInGamepadAxisEvents(const SDL_GamepadAxisEvent& c) { for ( const auto& ev : gaxis) if (ev.type == c.type) return true; return false; }
    bool isInGamepadButtonEvents(const SDL_GamepadButtonEvent& c) { for ( const auto& ev : gbutton) if (ev.type == c.type) return true; return false; }
    bool isInGamepadTouchpadEvents(const SDL_GamepadTouchpadEvent& c) { for ( const auto& ev : gtouchpad) if (ev.type == c.type) return true; return false; }
    bool isInGamepadSensorEvents(const SDL_GamepadSensorEvent& c) { for ( const auto& ev : gsensor) if (ev.type == c.type) return true; return false; }
    bool isInAudioDeviceEvents(const SDL_AudioDeviceEvent& c) { for ( const auto& ev : adevice) if (ev.type == c.type) return true; return false; }
    bool isInCameraDeviceEvents(const SDL_CameraDeviceEvent& c) { for ( const auto& ev : cdevice) if (ev.type == c.type) return true; return false; }
    bool isInSensorEvents(const SDL_SensorEvent& c) { for ( const auto& ev : sensor) if (ev.type == c.type) return true; return false; }
    bool isInQuitEvents(const SDL_QuitEvent& c) { for ( const auto& ev : quit) if (ev.type == c.type) return true; return false; }
    bool isInUserEvents(const SDL_UserEvent& c) { for ( const auto& ev : user) if (ev.type == c.type) return true; return false; }
    bool isInTouchFingerEvents(const SDL_TouchFingerEvent& c) { for ( const auto& ev : tfinger) if (ev.type == c.type) return true; return false; }
    // bool isInPinchFingerEvents(const SDL_PinchFingerEvent& c) { for ( const auto& ev : pinch) if (ev.type == c.type) return true; return false; }
    bool isInPenProximityEvents(const SDL_PenProximityEvent& c) { for ( const auto& ev : pproximity) if (ev.type == c.type) return true; return false; }
    bool isInPenTouchEvents(const SDL_PenTouchEvent& c) { for ( const auto& ev : ptouch) if (ev.type == c.type) return true; return false; }
    bool isInPenMotionEvents(const SDL_PenMotionEvent& c) { for ( const auto& ev : pmotion) if (ev.type == c.type) return true; return false; }
    bool isInPenButtonEvents(const SDL_PenButtonEvent& c) { for ( const auto& ev : pbutton) if (ev.type == c.type) return true; return false; }
    bool isInPenAxisEvents(const SDL_PenAxisEvent& c) { for ( const auto& ev : paxis) if (ev.type == c.type) return true; return false; }
    bool isInRenderEvents(const SDL_RenderEvent& c) { for ( const auto& ev : render) if (ev.type == c.type) return true; return false; }
    bool isInDropEvents(const SDL_DropEvent& c) { for ( const auto& ev : drop) if (ev.type == c.type) return true; return false; }
    bool isInClipboardEvents(const SDL_ClipboardEvent& c) { for ( const auto& ev : clipboard) if (ev.type == c.type) return true; return false; }

    // /std::vector<SDL_(\w+)> (\w+);/g -> /const std::vector<SDL_$1>& get$1(void) const { return $2; }/
    const std::vector<Uint32>& getTypes() const { return type; } // does not work on this one
    const std::vector<SDL_CommonEvent>& getCommonEvent(void) const { return common; }
    const std::vector<SDL_DisplayEvent>& getDisplayEvent(void) const { return display; }
    const std::vector<SDL_WindowEvent>& getWindowEvent(void) const { return window; }
    const std::vector<SDL_KeyboardDeviceEvent>& getKeyboardDeviceEvent(void) const { return kdevice; }
    const std::vector<SDL_KeyboardEvent>& getKeyboardEvent(void) const { return key; }
    const std::vector<SDL_TextEditingEvent>& getTextEditingEvent(void) const { return edit; }
    const std::vector<SDL_TextEditingCandidatesEvent>& getTextEditingCandidatesEvent(void) const { return edit_candidates; }
    const std::vector<SDL_TextInputEvent>& getTextInputEvent(void) const { return text; }
    const std::vector<SDL_MouseDeviceEvent>& getMouseDeviceEvent(void) const { return mdevice; }
    const std::vector<SDL_MouseMotionEvent>& getMouseMotionEvent(void) const { return motion; }
    const std::vector<SDL_MouseButtonEvent>& getMouseButtonEvent(void) const { return button; }
    const std::vector<SDL_MouseWheelEvent>& getMouseWheelEvent(void) const { return wheel; }
    const std::vector<SDL_JoyDeviceEvent>& getJoyDeviceEvent(void) const { return jdevice; }
    const std::vector<SDL_JoyAxisEvent>& getJoyAxisEvent(void) const { return jaxis; }
    const std::vector<SDL_JoyBallEvent>& getJoyBallEvent(void) const { return jball; }
    const std::vector<SDL_JoyHatEvent>& getJoyHatEvent(void) const { return jhat; }
    const std::vector<SDL_JoyButtonEvent>& getJoyButtonEvent(void) const { return jbutton; }
    const std::vector<SDL_JoyBatteryEvent>& getJoyBatteryEvent(void) const { return jbattery; }
    const std::vector<SDL_GamepadDeviceEvent>& getGamepadDeviceEvent(void) const { return gdevice; }
    const std::vector<SDL_GamepadAxisEvent>& getGamepadAxisEvent(void) const { return gaxis; }
    const std::vector<SDL_GamepadButtonEvent>& getGamepadButtonEvent(void) const { return gbutton; }
    const std::vector<SDL_GamepadTouchpadEvent>& getGamepadTouchpadEvent(void) const { return gtouchpad; }
    const std::vector<SDL_GamepadSensorEvent>& getGamepadSensorEvent(void) const { return gsensor; }
    const std::vector<SDL_AudioDeviceEvent>& getAudioDeviceEvent(void) const { return adevice; }
    const std::vector<SDL_CameraDeviceEvent>& getCameraDeviceEvent(void) const { return cdevice; }
    const std::vector<SDL_SensorEvent>& getSensorEvent(void) const { return sensor; }
    const std::vector<SDL_QuitEvent>& getQuitEvent(void) const { return quit; }
    const std::vector<SDL_UserEvent>& getUserEvent(void) const { return user; }
    const std::vector<SDL_TouchFingerEvent>& getTouchFingerEvent(void) const { return tfinger; }
    // const std::vector<SDL_PinchFingerEvent>& getPinchFingerEvent(void) const { return pinch; }
    const std::vector<SDL_PenProximityEvent>& getPenProximityEvent(void) const { return pproximity; }
    const std::vector<SDL_PenTouchEvent>& getPenTouchEvent(void) const { return ptouch; }
    const std::vector<SDL_PenMotionEvent>& getPenMotionEvent(void) const { return pmotion; }
    const std::vector<SDL_PenButtonEvent>& getPenButtonEvent(void) const { return pbutton; }
    const std::vector<SDL_PenAxisEvent>& getPenAxisEvent(void) const { return paxis; }
    const std::vector<SDL_RenderEvent>& getRenderEvent(void) const { return render; }
    const std::vector<SDL_DropEvent>& getDropEvent(void) const { return drop; }
    const std::vector<SDL_ClipboardEvent>& getClipboardEvent(void) const { return clipboard; }
    
};
