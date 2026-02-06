#pragma once

#include <cstdint>

#include "engine-m/vector/vector2d.h"
#include "engine-r/renderer/framebuffer.h"

namespace EngineR {
    void triangle(EngineM::vec2 p1, EngineM::vec2 p2, EngineM::vec2 p3, const std::uint32_t color, Framebuffer &framebuffer);
}
