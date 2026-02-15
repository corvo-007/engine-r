#pragma once

#include <cstdint>

#include "engine-m/vector/vector.h"
#include "engine-r/renderer/framebuffer.h"

namespace EngineR {
    void triangle(const EngineM::vec3d &p1, const EngineM::vec3d &p2, const EngineM::vec3d &p3, std::uint32_t color, Framebuffer &framebuffer);
}
