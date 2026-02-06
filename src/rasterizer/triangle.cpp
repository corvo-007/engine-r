#include "engine-r/rasterizer/triangle.h"

#include "engine-r/utils.h"

namespace EngineR {
    void triangle(EngineM::vec2 p1, EngineM::vec2 p2, EngineM::vec2 p3, const std::uint32_t color, Framebuffer &framebuffer) {
        auto [ p_min, p_max ] = get_bounding_box(p1, p2, p3);
        double total_signed_area = signed_triangle_area(p1, p2, p3);

        for (int y = p_min.y; y <= p_max.y; y++) {
            for (int x = p_min.x; x <= p_max.x; x++) {
                double alpha = signed_triangle_area({x, y}, p2, p3) / total_signed_area;
                double beta = signed_triangle_area(p1, {x, y}, p3) / total_signed_area;
                double gamma = signed_triangle_area(p1, p2, {x, y}) / total_signed_area;

                if (alpha >= 0 && beta >= 0 && gamma >= 0) {
                    framebuffer.set(x, y, color);
                }
            }
        }
    }
}
