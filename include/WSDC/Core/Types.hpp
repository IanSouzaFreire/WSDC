#pragma once

#include <cstdint>

#include "Size.hpp"
#include "Position.hpp"
#include "Color.hpp"

namespace WSDC {

namespace Types {


using Size = WSDC::Core::Size<int>;
using Position = WSDC::Core::Position<int>;
using Color = WSDC::Core::Color;
using index_t = uint64_t;


} // Types
    
} // WSDC
