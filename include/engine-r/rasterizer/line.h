#pragma once

#include "engine-m/vector/vector.h"
#include "engine-r/color.h"
#include "engine-r/renderer/buffer.h"

namespace EngineR {
    void line(EngineM::vec3 p1, EngineM::vec3 p2, Color color, Buffer<Color> &framebuffer);
}
