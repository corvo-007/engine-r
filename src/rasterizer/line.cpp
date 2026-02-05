#include "engine-r/rasterizer/line.h"

#include <cmath>

namespace EngineR {
    void line(const EngineM::vec2 &p1, const EngineM::vec2 &p2, std::uint32_t color, Framebuffer &framebuffer) {

        for (float t = 0.f; t <= 1.f; t += 0.01) {
            EngineM::vec2 p = p1 + (p2 - p1) * t;
            framebuffer.set(static_cast<int>(std::round(p.x)), static_cast<int>(std::round(p.y)), color);
        }
    }
}
