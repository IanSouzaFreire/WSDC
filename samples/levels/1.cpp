#include "WSDC.hpp"

using namespace WSDC;
using namespace WSDC::Geo;
using namespace WSDC::Display;
using namespace WSDC::Core;
using namespace WSDC::Managers;
using namespace WSDC::Draw;

int main(void) {
    Window main_win;
    Events events;
    
    main_win.size(Ratio::r16_9, 70)
            .build()
            .setTitle("Hello world!");
    
    Image IMG("image.png");
    float ratio = main_win.raw.size.w / 16.f / 100.f;
    Rect<float> imgp{ .x=  30 * ratio,
                      .y=  30 * ratio,
                      .w= 100 * ratio,
                      .h= 100 * ratio };
    
    auto texture = IMG.getTexture(main_win.raw.renderer);

    while (!events.update().isInTypes(SDL_EVENT_QUIT)) {
        main_win.drawRaw(SDL_RenderClear, Colors::WHITE_SMOKE)
                .renderRaw(SDL_RenderTexture, &texture, nullptr, &imgp.get<SDL_FRect>())
                .update();
    }

    return 0;
}
