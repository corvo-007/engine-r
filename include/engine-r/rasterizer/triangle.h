#pragma once

#include <cstdint>

#include "engine-m/vector/vector3d.h"
#include "engine-r/renderer/framebuffer.h"

namespace EngineR {
    void triangle(const EngineM::vec3 &p1, const EngineM::vec3 &p2, const EngineM::vec3 &p3, const std::uint32_t color, Framebuffer &framebuffer);
}
