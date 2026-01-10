#pragma once

#include <stdexcept>
#include <SDL3/SDL.h>

#include "../Definitions.hpp"

void WSDC::Draw::clearScreen(SDL_Renderer*& ren, const WSDC::Core::Color& c) {
    if (ren == nullptr) {
        throw std::runtime_error("[Draw::clearScreen] renderer non-acceptable.");
    }

    SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, c.a);
    SDL_RenderClear(ren);
}

void WSDC::Draw::clearScreen(SDL_Window*& win, const WSDC::Core::Color& c) {
    if (win == nullptr) {
        throw std::runtime_error("[Draw::clearScreen] window non-acceptable.");
    }

    SDL_Renderer* ren = SDL_GetRenderer(win);

    if (ren == nullptr) {
        throw std::runtime_error("[Draw::clearScreen] renderer non-acceptable.");
    }

    SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, c.a);
    SDL_RenderClear(ren);
}
