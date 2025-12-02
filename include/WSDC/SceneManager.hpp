#pragma once

#include <map>
#include <string>
#include <stdexcept>
#include <tuple>

#include "SceneManager/Scene.hpp"

template <class Key=std::string, class... ExtraData>
class SceneManager {
    using sig_function_t = std::function<void(Window&, ExtraData&...)>;
    using SceneW = Scene<ExtraData&...>;
    using ExtraDataTuple = std::tuple<ExtraData*...>;

    std::map<Key, SceneW> scenes;
    std::map<Key, sig_function_t> on_change;

    SceneW* current_scene;
    Window* current_window;
    Events* current_events;
    ExtraDataTuple current_outdata;

public:
    SceneManager() : current_scene(nullptr), current_window(nullptr), 
                     current_events(nullptr), current_outdata() {}
    ~SceneManager() {}

    SceneW& createScene(const Key&, const bool&);
    SceneW& scene(const Key&);
    SceneW& createSceneWithSignal(const Key&, const bool&, const sig_function_t&);
    SceneW& sceneWithSignal(const Key&, const bool&, const sig_function_t&);
    
    SceneManager<Key, ExtraData...>& extra(ExtraData&...);
    SceneManager<Key, ExtraData...>& window(Window&);
    SceneManager<Key, ExtraData...>& events(Events&);
    
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

template <class Key, class... ExtraData>
Scene<ExtraData&...>& SceneManager<Key, ExtraData...>::createScene(const Key& key, const bool& _default) {
    if (scenes.find(key) != scenes.end()) {
        throw std::runtime_error("Scene already defined");
    }

    scenes[key] = SceneW();

    if (_default) this->changeTo(key);

    return scenes[key];
}

template <class Key, class... ExtraData>
Scene<ExtraData&...>& SceneManager<Key, ExtraData...>::scene(const Key& key) {
    if (scenes.find(key) == scenes.end()) {
        throw std::runtime_error("Scene not found");
    }
    
    return scenes[key];
}

template <class Key, class... ExtraData>
Scene<ExtraData&...>& SceneManager<Key, ExtraData...>::createSceneWithSignal(const Key& key, const bool& _default, const sig_function_t& fn) {
    this->createScene(key, false);
    this->onChangeTo(key) = fn;

    if (_default) this->changeTo(key);

    return this->scene(key);
}

template <class Key, class... ExtraData>
Scene<ExtraData&...>& SceneManager<Key, ExtraData...>::sceneWithSignal(const Key& key, const bool& _default, const sig_function_t& fn) {
    this->onChangeTo(key) = fn;

    if (_default) this->changeTo(key);

    return this->scene(key);
}

template <class Key, class... ExtraData>
SceneManager<Key, ExtraData...>& SceneManager<Key, ExtraData...>::extra(ExtraData&... data) {
    current_outdata = std::make_tuple(&data...);

    return *this;
}

template <class Key, class... ExtraData>
SceneManager<Key, ExtraData...>& SceneManager<Key, ExtraData...>::window(Window& win) {
    current_window = &win;

    return *this;
}

template <class Key, class... ExtraData>
SceneManager<Key, ExtraData...>& SceneManager<Key, ExtraData...>::events(Events& eve) {
    current_events = &eve;

    return *this;
}

template <class Key, class... ExtraData>
void SceneManager<Key, ExtraData...>::changeTo(const Key& key) {
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
std::function<void(Window&, ExtraData&...)>& SceneManager<Key, ExtraData...>::onChangeTo(const Key& key) {
    if (scenes.find(key) == scenes.end()) {
        throw std::runtime_error("Scene not defined");
    }

    return on_change[key];
}

template <class Key, class... ExtraData>
SceneManager<Key, ExtraData...>& SceneManager<Key, ExtraData...>::run() {
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