#include "engine-r/rasterizer/line.h"

#include <cmath>

namespace EngineR {
    void line(EngineM::vec3 p1, EngineM::vec3 p2, const Color color, Framebuffer &framebuffer) {
        const bool steep = std::abs(p2.y - p1.y) > std::abs(p2.x - p1.x);

        if (steep) {
            std::swap(p1.x, p1.y);
            std::swap(p2.x, p2.y);
        }

        if (p1.x > p2.x) {
            std::swap(p1, p2);
        }

        int y = p1.y;
        int ierror = 0;

        for (int x = p1.x; x <= p2.x; x++) {
            if (steep) {
                framebuffer.set(y, x, color);
            }
            else {
                framebuffer.set(x, y, color);
            }

            ierror += 2 * std::abs(p2.y - p1.y);

            if (ierror > p2.x - p1.x) {
                y += p2.y > p1.y ? 1 : -1;
                ierror -= 2 * (p2.x - p1.x);
            }
        }
    }
}
