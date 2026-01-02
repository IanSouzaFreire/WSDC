#include "WSDC.hpp"

using namespace WSDC;
using namespace WSDC::Geo;
using namespace WSDC::Display;
using namespace WSDC::Core;
using namespace WSDC::Managers;
using namespace WSDC::Draw;

int main(void) {
    Window main_window;
    Events events;
    SceneManager<std::string, Image, float> manager;
    
    main_window.size(Ratio::r16_9, 70)
               .highPixelDensity(true)
               .resizeable(false)
               .build()
               .setTitle("Hello world!");
    
    float ratio = main_window.raw.size.w / 16.f / 100.f;
    Image IMG("image.png");
    
    manager.window(main_window)
           .events(events)
           .extra(IMG, ratio);

    manager.createScene("MAIN", true) = [] (Window& win, Events& ev, Image& IMG, float& r) {
        win.drawRaw(SDL_RenderClear, Colors::WHITE);

        SDL_FRect pp{ .x=30*r, .y=30*r, .w=100*r, .h=100*r };
        auto texture = IMG.getTexture(win.raw.renderer);

        win.renderRaw(SDL_RenderTexture, &texture, nullptr, &pp);
    };

    while (true) {
        events.update();
        if (events.isInTypes(SDL_EVENT_QUIT)) break;

        manager.run();
        main_window.update();
    }

    return 0;
}
