#pragma once

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <string>
#include <SDL3/SDL_events.h>

#include "Definitions.hpp"
#include "Events/Mapping.hpp"

/* Usage:
events.update();
    
if (events & __EVENT_TYPE__::__EVENT__) {
    #action#
}

*/

WSDC::Managers::Events& WSDC::Managers::Events::update() {
    mouse_flags = 0;
    window_flags = 0;
    system_flags = 0;
    display_flags = 0;
    keyboard_flags = 0;
    gamepad_flags = 0;
    joystick_flags = 0;
    touch_flags = 0;
    pen_flags = 0;
    audio_flags = 0;
    camera_flags = 0;
    sensor_flags = 0;
    render_flags = 0;
    drop_flags = 0;
    clipboard_flags = 0;
    user_flags = 0;
    
    mouse_dx = 0;
    mouse_dy = 0;
    wheel_x = 0;
    wheel_y = 0;
    keys_pressed_this_frame.clear();
    keys_released_this_frame.clear();
    text_input.clear();
    dropped_files.clear();
    dropped_text.clear();
    sensor_data.clear();
    
    key_states = SDL_GetKeyboardState(nullptr);
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            // Mouse events
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT: mouse_flags |= static_cast<uint32_t>(WSDC::Event::Mouse::LMB_DOWN); break;
                    case SDL_BUTTON_RIGHT: mouse_flags |= static_cast<uint32_t>(WSDC::Event::Mouse::RMB_DOWN); break;
                    case SDL_BUTTON_MIDDLE: mouse_flags |= static_cast<uint32_t>(WSDC::Event::Mouse::MMB_DOWN); break;
                    case SDL_BUTTON_X1: mouse_flags |= static_cast<uint32_t>(WSDC::Event::Mouse::X1_DOWN); break;
                    case SDL_BUTTON_X2: mouse_flags |= static_cast<uint32_t>(WSDC::Event::Mouse::X2_DOWN); break;
                }
                mouse_x = event.button.x;
                mouse_y = event.button.y;
                break;
                
            case SDL_EVENT_MOUSE_BUTTON_UP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT: mouse_flags |= static_cast<uint32_t>(WSDC::Event::Mouse::LMB_UP); break;
                    case SDL_BUTTON_RIGHT: mouse_flags |= static_cast<uint32_t>(WSDC::Event::Mouse::RMB_UP); break;
                    case SDL_BUTTON_MIDDLE: mouse_flags |= static_cast<uint32_t>(WSDC::Event::Mouse::MMB_UP); break;
                    case SDL_BUTTON_X1: mouse_flags |= static_cast<uint32_t>(WSDC::Event::Mouse::X1_UP); break;
                    case SDL_BUTTON_X2: mouse_flags |= static_cast<uint32_t>(WSDC::Event::Mouse::X2_UP); break;
                }
                mouse_x = event.button.x;
                mouse_y = event.button.y;
                break;
                
            case SDL_EVENT_MOUSE_MOTION:
                mouse_flags |= static_cast<uint32_t>(WSDC::Event::Mouse::MOTION);
                mouse_x = event.motion.x;
                mouse_y = event.motion.y;
                mouse_dx += event.motion.xrel;
                mouse_dy += event.motion.yrel;
                mouse_button_state = event.motion.state;
                break;
                
            case SDL_EVENT_MOUSE_WHEEL:
                mouse_flags |= static_cast<uint32_t>(WSDC::Event::Mouse::WHEEL);
                wheel_x += event.wheel.x;
                wheel_y += event.wheel.y;
                break;
                
            case SDL_EVENT_MOUSE_ADDED:
                mouse_flags |= static_cast<uint32_t>(WSDC::Event::Mouse::DEVICE_ADDED);
                break;
                
            case SDL_EVENT_MOUSE_REMOVED:
                mouse_flags |= static_cast<uint32_t>(WSDC::Event::Mouse::DEVICE_REMOVED);
                break;
                
            // Keyboard events
            case SDL_EVENT_KEY_DOWN:
                if (!event.key.repeat) {
                    keys_pressed_this_frame.insert(event.key.scancode);
                }
                break;
                
            case SDL_EVENT_KEY_UP:
                keys_released_this_frame.insert(event.key.scancode);
                break;
                
            case SDL_EVENT_KEYBOARD_ADDED:
                keyboard_flags |= static_cast<uint32_t>(WSDC::Event::Keyboard::DEVICE_ADDED);
                break;
                
            case SDL_EVENT_KEYBOARD_REMOVED:
                keyboard_flags |= static_cast<uint32_t>(WSDC::Event::Keyboard::DEVICE_REMOVED);
                break;
                
            case SDL_EVENT_TEXT_INPUT:
                keyboard_flags |= static_cast<uint32_t>(WSDC::Event::Keyboard::TEXT_INPUT);
                text_input += event.text.text;
                break;
                
            case SDL_EVENT_TEXT_EDITING:
                keyboard_flags |= static_cast<uint32_t>(WSDC::Event::Keyboard::TEXT_EDITING);
                text_editing = event.edit.text;
                break;
                
            case SDL_EVENT_TEXT_EDITING_CANDIDATES:
                keyboard_flags |= static_cast<uint32_t>(WSDC::Event::Keyboard::TEXT_EDITING_CANDIDATES);
                break;
                
            // Window events
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::CLOSE);
                window_id = event.window.windowID;
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::RESIZED);
                window_width = static_cast<int>(event.window.data1);
                window_height = static_cast<int>(event.window.data2);
                window_id = event.window.windowID;
                break;
            case SDL_EVENT_WINDOW_MINIMIZED:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::MINIMIZED);
                break;
            case SDL_EVENT_WINDOW_MAXIMIZED:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::MAXIMIZED);
                break;
            case SDL_EVENT_WINDOW_FOCUS_GAINED:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::FOCUS_GAINED);
                break;
            case SDL_EVENT_WINDOW_FOCUS_LOST:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::FOCUS_LOST);
                break;
            case SDL_EVENT_WINDOW_SHOWN:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::SHOWN);
                break;
            case SDL_EVENT_WINDOW_HIDDEN:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::HIDDEN);
                break;
            case SDL_EVENT_WINDOW_MOVED:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::MOVED);
                break;
            case SDL_EVENT_WINDOW_EXPOSED:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::EXPOSED);
                break;
            case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::PIXEL_SIZE_CHANGED);
                break;
            case SDL_EVENT_WINDOW_METAL_VIEW_RESIZED:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::METAL_VIEW_RESIZED);
                break;
            case SDL_EVENT_WINDOW_RESTORED:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::RESTORED);
                break;
            case SDL_EVENT_WINDOW_MOUSE_ENTER:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::MOUSE_ENTER);
                break;
            case SDL_EVENT_WINDOW_MOUSE_LEAVE:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::MOUSE_LEAVE);
                break;
            case SDL_EVENT_WINDOW_HIT_TEST:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::HIT_TEST);
                break;
            case SDL_EVENT_WINDOW_ICCPROF_CHANGED:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::ICCPROF_CHANGED);
                break;
            case SDL_EVENT_WINDOW_DISPLAY_CHANGED:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::DISPLAY_CHANGED);
                break;
            case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::DISPLAY_SCALE_CHANGED);
                break;
            case SDL_EVENT_WINDOW_SAFE_AREA_CHANGED:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::SAFE_AREA_CHANGED);
                break;
            case SDL_EVENT_WINDOW_OCCLUDED:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::OCCLUDED);
                break;
            case SDL_EVENT_WINDOW_ENTER_FULLSCREEN:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::ENTER_FULLSCREEN);
                break;
            case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::LEAVE_FULLSCREEN);
                break;
            case SDL_EVENT_WINDOW_DESTROYED:
                window_flags |= static_cast<uint32_t>(WSDC::Event::Window::DESTROYED);
                break;
                
            // System events
            case SDL_EVENT_QUIT:
                system_flags |= static_cast<uint32_t>(WSDC::Event::System::QUIT);
                break;
            case SDL_EVENT_TERMINATING:
                system_flags |= static_cast<uint32_t>(WSDC::Event::System::TERMINATING);
                break;
            case SDL_EVENT_LOW_MEMORY:
                system_flags |= static_cast<uint32_t>(WSDC::Event::System::LOW_MEMORY);
                break;
            case SDL_EVENT_WILL_ENTER_BACKGROUND:
                system_flags |= static_cast<uint32_t>(WSDC::Event::System::WILL_ENTER_BACKGROUND);
                break;
            case SDL_EVENT_DID_ENTER_BACKGROUND:
                system_flags |= static_cast<uint32_t>(WSDC::Event::System::DID_ENTER_BACKGROUND);
                break;
            case SDL_EVENT_WILL_ENTER_FOREGROUND:
                system_flags |= static_cast<uint32_t>(WSDC::Event::System::WILL_ENTER_FOREGROUND);
                break;
            case SDL_EVENT_DID_ENTER_FOREGROUND:
                system_flags |= static_cast<uint32_t>(WSDC::Event::System::DID_ENTER_FOREGROUND);
                break;
            case SDL_EVENT_LOCALE_CHANGED:
                system_flags |= static_cast<uint32_t>(WSDC::Event::System::LOCALE_CHANGED);
                break;
            case SDL_EVENT_SYSTEM_THEME_CHANGED:
                system_flags |= static_cast<uint32_t>(WSDC::Event::System::SYSTEM_THEME_CHANGED);
                break;
                
            // Display events
            case SDL_EVENT_DISPLAY_ORIENTATION:
                display_flags |= static_cast<uint32_t>(WSDC::Event::Display::ORIENTATION);
                display_id = event.display.displayID;
                display_orientation = static_cast<SDL_DisplayOrientation>(event.display.data1);
                break;
            case SDL_EVENT_DISPLAY_ADDED:
                display_flags |= static_cast<uint32_t>(WSDC::Event::Display::ADDED);
                display_id = event.display.displayID;
                break;
            case SDL_EVENT_DISPLAY_REMOVED:
                display_flags |= static_cast<uint32_t>(WSDC::Event::Display::REMOVED);
                display_id = event.display.displayID;
                break;
            case SDL_EVENT_DISPLAY_MOVED:
                display_flags |= static_cast<uint32_t>(WSDC::Event::Display::MOVED);
                display_id = event.display.displayID;
                break;
            case SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED:
                display_flags |= static_cast<uint32_t>(WSDC::Event::Display::CONTENT_SCALE_CHANGED);
                display_id = event.display.displayID;
                break;
                
            // Gamepad events
            case SDL_EVENT_GAMEPAD_ADDED:
                gamepad_flags |= static_cast<uint32_t>(WSDC::Event::Gamepad::ADDED);
                active_gamepads.insert(event.gdevice.which);
                break;
            case SDL_EVENT_GAMEPAD_REMOVED:
                gamepad_flags |= static_cast<uint32_t>(WSDC::Event::Gamepad::REMOVED);
                active_gamepads.erase(event.gdevice.which);
                break;
            case SDL_EVENT_GAMEPAD_REMAPPED:
                gamepad_flags |= static_cast<uint32_t>(WSDC::Event::Gamepad::REMAPPED);
                break;
            case SDL_EVENT_GAMEPAD_UPDATE_COMPLETE:
                gamepad_flags |= static_cast<uint32_t>(WSDC::Event::Gamepad::UPDATE_COMPLETE);
                break;
            case SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED:
                gamepad_flags |= static_cast<uint32_t>(WSDC::Event::Gamepad::STEAM_HANDLE_UPDATED);
                break;
            case SDL_EVENT_GAMEPAD_AXIS_MOTION:
                gamepad_flags |= static_cast<uint32_t>(WSDC::Event::Gamepad::AXIS_MOTION);
                gamepad_axes[event.gaxis.which] = static_cast<SDL_GamepadAxis>(event.gaxis.axis);
                break;
            case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
                gamepad_flags |= static_cast<uint32_t>(WSDC::Event::Gamepad::BUTTON_DOWN);
                gamepad_buttons[event.gbutton.which] = static_cast<SDL_GamepadButton>(event.gbutton.button);
                break;
            case SDL_EVENT_GAMEPAD_BUTTON_UP:
                gamepad_flags |= static_cast<uint32_t>(WSDC::Event::Gamepad::BUTTON_UP);
                gamepad_buttons[event.gbutton.which] = static_cast<SDL_GamepadButton>(event.gbutton.button);
                break;
            case SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN:
                gamepad_flags |= static_cast<uint32_t>(WSDC::Event::Gamepad::TOUCHPAD_DOWN);
                break;
            case SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION:
                gamepad_flags |= static_cast<uint32_t>(WSDC::Event::Gamepad::TOUCHPAD_MOTION);
                break;
            case SDL_EVENT_GAMEPAD_TOUCHPAD_UP:
                gamepad_flags |= static_cast<uint32_t>(WSDC::Event::Gamepad::TOUCHPAD_UP);
                break;
            case SDL_EVENT_GAMEPAD_SENSOR_UPDATE:
                gamepad_flags |= static_cast<uint32_t>(WSDC::Event::Gamepad::SENSOR_UPDATE);
                break;
                
            // Joystick events
            case SDL_EVENT_JOYSTICK_ADDED:
                joystick_flags |= static_cast<uint32_t>(WSDC::Event::Joystick::ADDED);
                active_joysticks.insert(event.jdevice.which);
                break;
            case SDL_EVENT_JOYSTICK_REMOVED:
                joystick_flags |= static_cast<uint32_t>(WSDC::Event::Joystick::REMOVED);
                active_joysticks.erase(event.jdevice.which);
                break;
            case SDL_EVENT_JOYSTICK_UPDATE_COMPLETE:
                joystick_flags |= static_cast<uint32_t>(WSDC::Event::Joystick::UPDATE_COMPLETE);
                break;
            case SDL_EVENT_JOYSTICK_AXIS_MOTION:
                joystick_flags |= static_cast<uint32_t>(WSDC::Event::Joystick::AXIS_MOTION);
                joystick_axes[event.jaxis.which] = event.jaxis.axis;
                break;
            case SDL_EVENT_JOYSTICK_BALL_MOTION:
                joystick_flags |= static_cast<uint32_t>(WSDC::Event::Joystick::BALL_MOTION);
                break;
            case SDL_EVENT_JOYSTICK_HAT_MOTION:
                joystick_flags |= static_cast<uint32_t>(WSDC::Event::Joystick::HAT_MOTION);
                break;
            case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
                joystick_flags |= static_cast<uint32_t>(WSDC::Event::Joystick::BUTTON_DOWN);
                joystick_buttons[event.jbutton.which] = event.jbutton.button;
                break;
            case SDL_EVENT_JOYSTICK_BUTTON_UP:
                joystick_flags |= static_cast<uint32_t>(WSDC::Event::Joystick::BUTTON_UP);
                joystick_buttons[event.jbutton.which] = event.jbutton.button;
                break;
            case SDL_EVENT_JOYSTICK_BATTERY_UPDATED:
                joystick_flags |= static_cast<uint32_t>(WSDC::Event::Joystick::BATTERY_UPDATED);
                break;
                
            // Touch events
            case SDL_EVENT_FINGER_DOWN:
                touch_flags |= static_cast<uint32_t>(WSDC::Event::Touch::FINGER_DOWN);
                touch_fingers[event.tfinger.fingerID] = {
                    event.tfinger.x, event.tfinger.y,
                    event.tfinger.dx, event.tfinger.dy,
                    event.tfinger.pressure
                };
                break;
            case SDL_EVENT_FINGER_UP:
                touch_flags |= static_cast<uint32_t>(WSDC::Event::Touch::FINGER_UP);
                touch_fingers.erase(event.tfinger.fingerID);
                break;
            case SDL_EVENT_FINGER_MOTION:
                touch_flags |= static_cast<uint32_t>(WSDC::Event::Touch::FINGER_MOTION);
                touch_fingers[event.tfinger.fingerID] = {
                    event.tfinger.x, event.tfinger.y,
                    event.tfinger.dx, event.tfinger.dy,
                    event.tfinger.pressure
                };
                break;
                
            // Pen events
            case SDL_EVENT_PEN_PROXIMITY_IN:
                pen_flags |= static_cast<uint32_t>(WSDC::Event::Pen::PROXIMITY_IN);
                pen_id = event.pproximity.which;
                break;
            case SDL_EVENT_PEN_PROXIMITY_OUT:
                pen_flags |= static_cast<uint32_t>(WSDC::Event::Pen::PROXIMITY_OUT);
                pen_id = event.pproximity.which;
                break;
            case SDL_EVENT_PEN_DOWN:
                pen_flags |= static_cast<uint32_t>(WSDC::Event::Pen::DOWN);
                pen_x = event.ptouch.x;
                pen_y = event.ptouch.y;
                break;
            case SDL_EVENT_PEN_UP:
                pen_flags |= static_cast<uint32_t>(WSDC::Event::Pen::UP);
                pen_x = event.ptouch.x;
                pen_y = event.ptouch.y;
                break;
            case SDL_EVENT_PEN_MOTION:
                pen_flags |= static_cast<uint32_t>(WSDC::Event::Pen::MOTION);
                pen_x = event.pmotion.x;
                pen_y = event.pmotion.y;
                break;
            case SDL_EVENT_PEN_BUTTON_DOWN:
                pen_flags |= static_cast<uint32_t>(WSDC::Event::Pen::BUTTON_DOWN);
                break;
            case SDL_EVENT_PEN_BUTTON_UP:
                pen_flags |= static_cast<uint32_t>(WSDC::Event::Pen::BUTTON_UP);
                break;
            case SDL_EVENT_PEN_AXIS:
                pen_flags |= static_cast<uint32_t>(WSDC::Event::Pen::AXIS);
                if (event.paxis.axis == SDL_PEN_AXIS_PRESSURE) {
                    pen_pressure = event.paxis.value;
                } else if (event.paxis.axis == SDL_PEN_AXIS_XTILT) {
                    pen_tilt_x = event.paxis.value;
                } else if (event.paxis.axis == SDL_PEN_AXIS_YTILT) {
                    pen_tilt_y = event.paxis.value;
                }
                break;
                
            // Audio events
            case SDL_EVENT_AUDIO_DEVICE_ADDED:
                audio_flags |= static_cast<uint32_t>(WSDC::Event::Audio::DEVICE_ADDED);
                audio_device_id = event.adevice.which;
                break;
            case SDL_EVENT_AUDIO_DEVICE_REMOVED:
                audio_flags |= static_cast<uint32_t>(WSDC::Event::Audio::DEVICE_REMOVED);
                audio_device_id = event.adevice.which;
                break;
            case SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED:
                audio_flags |= static_cast<uint32_t>(WSDC::Event::Audio::DEVICE_FORMAT_CHANGED);
                audio_device_id = event.adevice.which;
                break;
                
            // Camera events
            case SDL_EVENT_CAMERA_DEVICE_ADDED:
                camera_flags |= static_cast<uint32_t>(WSDC::Event::Camera::DEVICE_ADDED);
                camera_device_id = event.cdevice.which;
                break;
            case SDL_EVENT_CAMERA_DEVICE_REMOVED:
                camera_flags |= static_cast<uint32_t>(WSDC::Event::Camera::DEVICE_REMOVED);
                camera_device_id = event.cdevice.which;
                break;
            case SDL_EVENT_CAMERA_DEVICE_APPROVED:
                camera_flags |= static_cast<uint32_t>(WSDC::Event::Camera::DEVICE_APPROVED);
                camera_device_id = event.cdevice.which;
                break;
            case SDL_EVENT_CAMERA_DEVICE_DENIED:
                camera_flags |= static_cast<uint32_t>(WSDC::Event::Camera::DEVICE_DENIED);
                camera_device_id = event.cdevice.which;
                break;
                
            // Sensor events
            case SDL_EVENT_SENSOR_UPDATE:
                sensor_flags |= static_cast<uint32_t>(WSDC::Event::Sensor::UPDATE);
                sensor_data.clear();
                for (int i = 0; i < 6 && event.sensor.data[i] != 0; i++) {
                    sensor_data.push_back(event.sensor.data[i]);
                }
                break;
                
            // Render events
            case SDL_EVENT_RENDER_TARGETS_RESET:
                render_flags |= static_cast<uint32_t>(WSDC::Event::Render::TARGETS_RESET);
                break;
            case SDL_EVENT_RENDER_DEVICE_RESET:
                render_flags |= static_cast<uint32_t>(WSDC::Event::Render::DEVICE_RESET);
                break;
            case SDL_EVENT_RENDER_DEVICE_LOST:
                render_flags |= static_cast<uint32_t>(WSDC::Event::Render::DEVICE_LOST);
                break;
                
            // Drop events
            case SDL_EVENT_DROP_BEGIN:
                drop_flags |= static_cast<uint32_t>(WSDC::Event::Drop::BEGIN);
                break;
            case SDL_EVENT_DROP_FILE:
                drop_flags |= static_cast<uint32_t>(WSDC::Event::Drop::FILE);
                if (event.drop.data) {
                    dropped_files.push_back(event.drop.data);
                }
                break;
            case SDL_EVENT_DROP_TEXT:
                drop_flags |= static_cast<uint32_t>(WSDC::Event::Drop::TEXT);
                if (event.drop.data) {
                    dropped_text = event.drop.data;
                }
                break;
            case SDL_EVENT_DROP_COMPLETE:
                drop_flags |= static_cast<uint32_t>(WSDC::Event::Drop::COMPLETE);
                break;
            case SDL_EVENT_DROP_POSITION:
                drop_flags |= static_cast<uint32_t>(WSDC::Event::Drop::POSITION);
                drop_x = event.drop.x;
                drop_y = event.drop.y;
                break;
                
            // Clipboard events
            case SDL_EVENT_CLIPBOARD_UPDATE:
                clipboard_flags |= static_cast<uint32_t>(WSDC::Event::Clipboard::UPDATE);
                break;
                
            // User events
            case SDL_EVENT_USER:
                user_flags |= static_cast<uint32_t>(WSDC::Event::User::EVENT);
                user_code = event.user.code;
                user_data1 = event.user.data1;
                user_data2 = event.user.data2;
                break;
        }
    }
    
    return *this;
}

// Operator overloads for flag checking
bool WSDC::Managers::Events::operator&(WSDC::Event::Mouse m) const { return (mouse_flags & static_cast<uint32_t>(m)) != 0; }
bool WSDC::Managers::Events::operator&(WSDC::Event::Window w) const { return (window_flags & static_cast<uint32_t>(w)) != 0; }
bool WSDC::Managers::Events::operator&(WSDC::Event::System s) const { return (system_flags & static_cast<uint32_t>(s)) != 0; }
bool WSDC::Managers::Events::operator&(WSDC::Event::Display d) const { return (display_flags & static_cast<uint32_t>(d)) != 0; }
bool WSDC::Managers::Events::operator&(WSDC::Event::Keyboard k) const { return (keyboard_flags & static_cast<uint32_t>(k)) != 0; }
bool WSDC::Managers::Events::operator&(WSDC::Event::Gamepad g) const { return (gamepad_flags & static_cast<uint32_t>(g)) != 0; }
bool WSDC::Managers::Events::operator&(WSDC::Event::Joystick j) const { return (joystick_flags & static_cast<uint32_t>(j)) != 0; }
bool WSDC::Managers::Events::operator&(WSDC::Event::Touch t) const { return (touch_flags & static_cast<uint32_t>(t)) != 0; }
bool WSDC::Managers::Events::operator&(WSDC::Event::Pen p) const { return (pen_flags & static_cast<uint32_t>(p)) != 0; }
bool WSDC::Managers::Events::operator&(WSDC::Event::Audio a) const { return (audio_flags & static_cast<uint32_t>(a)) != 0; }
bool WSDC::Managers::Events::operator&(WSDC::Event::Camera c) const { return (camera_flags & static_cast<uint32_t>(c)) != 0; }
bool WSDC::Managers::Events::operator&(WSDC::Event::Sensor s) const { return (sensor_flags & static_cast<uint32_t>(s)) != 0; }
bool WSDC::Managers::Events::operator&(WSDC::Event::Render r) const { return (render_flags & static_cast<uint32_t>(r)) != 0; }
bool WSDC::Managers::Events::operator&(WSDC::Event::Drop d) const { return (drop_flags & static_cast<uint32_t>(d)) != 0; }
bool WSDC::Managers::Events::operator&(WSDC::Event::Clipboard c) const { return (clipboard_flags & static_cast<uint32_t>(c)) != 0; }
bool WSDC::Managers::Events::operator&(WSDC::Event::User u) const { return (user_flags & static_cast<uint32_t>(u)) != 0; }
template <class EV> bool WSDC::Managers::Events::isEvent(EV e) { return this->operator&(e); }

// Keyboard queries
bool WSDC::Managers::Events::isKeyHeld(SDL_Scancode sc) const { return key_states && key_states[sc]; }
bool WSDC::Managers::Events::isKeyPressed(SDL_Scancode sc) const { return keys_pressed_this_frame.count(sc) > 0; }
bool WSDC::Managers::Events::isKeyReleased(SDL_Scancode sc) const { return keys_released_this_frame.count(sc) > 0; }

// Mouse state
float WSDC::Managers::Events::mouseX() const { return mouse_x; }
float WSDC::Managers::Events::mouseY() const { return mouse_y; }
WSDC::Core::Position<float> WSDC::Managers::Events::mouse() const { return {mouse_x, mouse_y}; }
float WSDC::Managers::Events::mouseDX() const { return mouse_dx; }
float WSDC::Managers::Events::mouseDY() const { return mouse_dy; }
WSDC::Core::Position<float> WSDC::Managers::Events::mouseDelta() const { return {mouse_dx, mouse_dy}; }
float WSDC::Managers::Events::wheelX() const { return wheel_x; }
float WSDC::Managers::Events::wheelY() const { return wheel_y; }
WSDC::Core::Position<float> WSDC::Managers::Events::wheel() const { return {wheel_x, wheel_y}; }
uint32_t WSDC::Managers::Events::mouseButtonState() const { return mouse_button_state; }

// Window state
int WSDC::Managers::Events::windowWidth() const { return window_width; }
int WSDC::Managers::Events::windowHeight() const { return window_height; }
WSDC::Core::Size<int> WSDC::Managers::Events::window() const { return {window_width, window_height}; }
SDL_WindowID WSDC::Managers::Events::windowID() const { return window_id; }

// Display state
SDL_DisplayID WSDC::Managers::Events::displayID() const { return display_id; }
SDL_DisplayOrientation WSDC::Managers::Events::displayOrientation() const { return display_orientation; }

// Text input
const std::string& WSDC::Managers::Events::textInput() const { return text_input; }
const std::string& WSDC::Managers::Events::textEditing() const { return text_editing; }

// Touch state
const std::unordered_map<SDL_FingerID, WSDC::Event::TouchFinger>& WSDC::Managers::Events::touchFingers() const { return touch_fingers; }

// Pen state
float WSDC::Managers::Events::penX() const { return pen_x; }
float WSDC::Managers::Events::penY() const { return pen_y; }
WSDC::Core::Position<float> WSDC::Managers::Events::pen() const { return {pen_x, pen_y}; }
float WSDC::Managers::Events::penPressure() const { return pen_pressure; }
float WSDC::Managers::Events::penTiltX() const { return pen_tilt_x; }
float WSDC::Managers::Events::penTiltY() const { return pen_tilt_y; }
WSDC::Core::Position<float> WSDC::Managers::Events::penTilt() const { return {pen_tilt_x, pen_tilt_y}; }
SDL_PenID WSDC::Managers::Events::penID() const { return pen_id; }

// Gamepad state
const std::unordered_set<SDL_JoystickID>& WSDC::Managers::Events::activeGamepads() const { return active_gamepads; }

// Joystick state
const std::unordered_set<SDL_JoystickID>& WSDC::Managers::Events::activeJoysticks() const { return active_joysticks; }

// Drop state
const std::vector<std::string>& WSDC::Managers::Events::droppedFiles() const { return dropped_files; }
const std::string& WSDC::Managers::Events::droppedText() const { return dropped_text; }
float WSDC::Managers::Events::dropX() const { return drop_x; }
float WSDC::Managers::Events::dropY() const { return drop_y; }
WSDC::Core::Position<float> WSDC::Managers::Events::drop() const { return {drop_x, drop_y}; }

// Sensor state
const std::vector<float>& WSDC::Managers::Events::sensorData() const { return sensor_data; }

// Audio state
SDL_AudioDeviceID WSDC::Managers::Events::audioDeviceID() const { return audio_device_id; }

// Camera state
SDL_CameraID WSDC::Managers::Events::cameraDeviceID() const { return camera_device_id; }

// User event state
void* WSDC::Managers::Events::userData1() const { return user_data1; }
void* WSDC::Managers::Events::userData2() const { return user_data2; }
int32_t WSDC::Managers::Events::userCode() const { return user_code; }