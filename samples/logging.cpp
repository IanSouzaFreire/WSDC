#include "WSDC/Text/Log.hpp"

int main(int argc, char** argv) {
    using namespace WSDC;
    using namespace Colors;
    namespace Styles = Log::Styles;
    
    if (argc < 5) {
        Log::print({ rgb(RED), nullptr, Styles::bold }, "PLEASE");
        Log::println(" use: {size} {d1} {d2} {d3}");
        return 0;
    }

    Log::clear();

    const Core::rgb_t sz = std::stoi(argv[1]),
                      d1 = std::stoi(argv[2]),
                      d2 = std::stoi(argv[3]),
                      d3 = std::stoi(argv[4]);
    
    for (int32_t y = 0; y < sz / sz + 2 / 12; y++) {
        for (int32_t x = 0; x < sz; x++) {
            const Core::rgb_t r = (x * y * d1) % 256,
                              g = (x * y * d2) % 256,
                              b = (x * y * d3) % 256;
            Log::print({ nullptr, rgb(r, g, b), Styles::none }, " ");
        }

        Log::println("");
    }

    return 0;
};
