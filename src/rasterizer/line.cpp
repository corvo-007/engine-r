#include "engine-r/rasterizer/line.h"

#include <cmath>

namespace EngineR {
    void line(EngineM::vec2 p1, EngineM::vec2 p2, std::uint32_t color, Framebuffer &framebuffer) {
        bool steep = std::abs(p2.y - p1.y) > std::abs(p2.x - p1.x);

        if (steep) {
            std::swap(p1.x, p1.y);
            std::swap(p2.x, p2.y);
        }

        if (p1.x > p2.x) {
            std::swap(p1, p2);
        }

        for (int x = p1.x; x <= p2.x; x++) {
            int y = static_cast<int>(std::round(p1.y + static_cast<float>(p2.y - p1.y) / (p2.x - p1.x) * (x - p1.x)));
            if (steep) {
                framebuffer.set(y, x, color);
            }
            else {
                framebuffer.set(x, y, color);
            }
        }
    }
}
