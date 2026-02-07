#pragma once
#include <cstdint>

#include "engine-m/vector/vector3d.h"
#include "engine-r/renderer/framebuffer.h"

namespace EngineR {
    void line(EngineM::vec3 p1, EngineM::vec3 p2, std::uint32_t color, Framebuffer &framebuffer);
}
