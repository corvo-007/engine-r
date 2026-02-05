#pragma once
#include <cstdint>

#include "engine-m/vector/vector2d.h"
#include "engine-r/renderer/framebuffer.h"

namespace EngineR {
    void line(EngineM::vec2 p1, EngineM::vec2 p2, std::uint32_t color, Framebuffer &framebuffer);
}
