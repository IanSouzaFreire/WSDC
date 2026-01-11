#pragma once

#include "Definitions.hpp"

template <class Key, class... ExtraData>
WSDC::Managers::Scene<ExtraData&...>& WSDC::Managers::SceneManager<Key, ExtraData...>::createScene(const Key& key, const bool& _default) {
    if (scenes.find(key) != scenes.end()) {
        throw std::runtime_error("Scene already defined");
    }

    scenes[key] = SceneW();

    if (_default) this->changeTo(key);

    return scenes[key];
}

template <class Key, class... ExtraData>
WSDC::Managers::Scene<ExtraData&...>& WSDC::Managers::SceneManager<Key, ExtraData...>::createScene(const Key& key) {
    return this->createScene(key, false);
}

template <class Key, class... ExtraData>
WSDC::Managers::Scene<ExtraData&...>& WSDC::Managers::SceneManager<Key, ExtraData...>::scene(const Key& key) {
    if (scenes.find(key) == scenes.end()) {
        throw std::runtime_error("Scene not found");
    }
    
    return scenes[key];
}

template <class Key, class... ExtraData>
WSDC::Managers::Scene<ExtraData&...>& WSDC::Managers::SceneManager<Key, ExtraData...>::createSceneWithSignal(const Key& key, const bool& _default, const sig_function_t& fn) {
    this->createScene(key, false);
    this->onChangeTo(key) = fn;

    if (_default) this->changeTo(key);

    return this->scene(key);
}

template <class Key, class... ExtraData>
WSDC::Managers::Scene<ExtraData&...>& WSDC::Managers::SceneManager<Key, ExtraData...>::createSceneWithSignal(const Key& key, const sig_function_t& fn) {
    return this->createSceneWithSignal(key, false, fn);
}

template <class Key, class... ExtraData>
WSDC::Managers::Scene<ExtraData&...>& WSDC::Managers::SceneManager<Key, ExtraData...>::sceneWithSignal(const Key& key, const bool& _default, const sig_function_t& fn) {
    this->onChangeTo(key) = fn;

    if (_default) this->changeTo(key);

    return this->scene(key);
}

template <class Key, class... ExtraData>
WSDC::Managers::SceneManager<Key, ExtraData...>& WSDC::Managers::SceneManager<Key, ExtraData...>::extra(ExtraData&... data) {
    current_outdata = std::make_tuple(&data...);

    return *this;
}

template <class Key, class... ExtraData>
WSDC::Managers::SceneManager<Key, ExtraData...>& WSDC::Managers::SceneManager<Key, ExtraData...>::window(WSDC::Display::Window& win) {
    current_window = &win;

    return *this;
}

template <class Key, class... ExtraData>
WSDC::Managers::SceneManager<Key, ExtraData...>& WSDC::Managers::SceneManager<Key, ExtraData...>::events(WSDC::Managers::Events& eve) {
    current_events = &eve;

    return *this;
}

template <class Key, class... ExtraData>
void WSDC::Managers::SceneManager<Key, ExtraData...>::changeTo(const Key& key) {
    if (scenes.find(key) == scenes.end()) {
        throw std::runtime_error("Scene not found");
    }

    if (on_change.find(key) != on_change.end()) {
        if (current_window) {
            callOnChange(key, std::index_sequence_for<ExtraData...>{});
        }
    }

    current_scene = &scenes[key];
}

template <class Key, class... ExtraData>
std::function<void(WSDC::Display::Window&, ExtraData&...)>& WSDC::Managers::SceneManager<Key, ExtraData...>::onChangeTo(const Key& key) {
    if (scenes.find(key) == scenes.end()) {
        throw std::runtime_error("Scene not defined");
    }

    return on_change[key];
}

template <class Key, class... ExtraData>
WSDC::Managers::SceneManager<Key, ExtraData...>& WSDC::Managers::SceneManager<Key, ExtraData...>::run() {
    if (current_scene == nullptr) {
        throw std::runtime_error("No scene was chosen");
    }
    
    if (current_window == nullptr) {
        throw std::runtime_error("No window was set");
    }
    
    if (current_events == nullptr) {
        throw std::runtime_error("No events object was set");
    }

    callSceneRun(std::index_sequence_for<ExtraData...>{});
    return *this;
}
