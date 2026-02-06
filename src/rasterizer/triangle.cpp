#include "engine-r/rasterizer/triangle.h"

namespace EngineR {
    void triangle(EngineM::vec2 p1, EngineM::vec2 p2, EngineM::vec2 p3, const std::uint32_t color, Framebuffer &framebuffer) {
        if (p1.y > p2.y) {
            std::swap(p1, p2);
        }
        if (p1.y > p3.y) {
            std::swap(p1, p3);
        }
        if (p2.y > p3.y) {
            std::swap(p2, p3);
        }

        for (int y = p1.y; y < p2.y; y++) {
            int x1 = p1.x + static_cast<float>(p2.x - p1.x) / (p2.y - p1.y) * (y - p1.y);
            int x2 = p1.x + static_cast<float>(p3.x - p1.x) / (p3.y - p1.y) * (y - p1.y);

            for (int x = std::min(x1, x2); x <= std::max(x1, x2); x++) {
                framebuffer.set(x, y, color);
            }
        }

        for (int y = p2.y; y < p3.y; y++) {
            int x1 = p2.x + static_cast<float>(p3.x - p2.x) / (p3.y - p2.y) * (y - p2.y);
            int x2 = p1.x + static_cast<float>(p3.x - p1.x) / (p3.y - p1.y) * (y - p1.y);

            for (int x = std::min(x1, x2); x <= std::max(x1, x2); x++) {
                framebuffer.set(x, y, color);
            }
        }
    }
}
