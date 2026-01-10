#define WSDC_IMPLEMENT
#include "WSDC.hpp"

using namespace WSDC;
using namespace WSDC::Geo;
using namespace WSDC::Display;
using namespace WSDC::Core;
using namespace WSDC::Managers;
using namespace WSDC::Draw;

enum class SCENES {
    MAIN,
};

class Game : public Engine<SCENES, float, Image> {
    float ratio;
    Image IMG;

public:
    Game() {
        display.size(Ratio::r16_9, 70)
               .highPixelDensity(true)
               .resizeable(false)
               .build()
               .setTitle("Hello world!");
        
        ratio = display.raw.size.w / 16.f / 100.f;
        IMG.load("image.png");

        set_extra(ratio, IMG); // set data to point to

        manager.createScene(SCENES::MAIN, true) = [] (Window& win, Events&, SubWindows&, TextRenderer&, float& ratio, Image& IMG) {
            // "ratio" and "IMG" are pointed data
            win.drawRaw(SDL_RenderClear, Colors["White"]);

            SDL_FRect pp;
                pp.x = 30 * ratio;
                pp.y = 30 * ratio;
                pp.w = IMG.getWidth()  * ratio;
                pp.h = IMG.getHeight() * ratio;
            
            auto texture = IMG.getTexture(win.raw.renderer);
            win.renderRaw(SDL_RenderTexture, &texture, nullptr, &pp);
        };

        isRunning(true); // set as ready to run
    }
};

int main(void) {
    Game game;
    game.run_block();
    return 0;
}