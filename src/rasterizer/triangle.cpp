#include "engine-r/rasterizer/triangle.h"

#include "engine-r/utils.h"

namespace EngineR {
    void triangle(const EngineM::vec3 &p1, const EngineM::vec3 &p2, const EngineM::vec3 &p3, const std::uint32_t color, Framebuffer &framebuffer) {
        auto [ p_min, p_max ] = get_bounding_box(p1, p2, p3);
        const double total_signed_area = signed_triangle_area(p1, p2, p3);
        if (total_signed_area < 1) {
            return ;
        }

        for (int y = p_min.y; y <= p_max.y; y++) {
            for (int x = p_min.x; x <= p_max.x; x++) {
                double alpha = signed_triangle_area({x, y, 0}, p2, p3) / total_signed_area;
                double beta = signed_triangle_area(p1, {x, y, 0}, p3) / total_signed_area;
                double gamma = signed_triangle_area(p1, p2, {x, y, 0}) / total_signed_area;

                if (alpha < 0 || beta < 0 || gamma < 0) {
                    continue;
                }

                int z = alpha * p1.z + beta * p2.z + gamma * p3.z;
                z = (z << 24) | (z << 16) | (z << 8) | z;
                if (framebuffer.get_z(x, y) < z) {
                    framebuffer.set_z(x, y, z);
                    framebuffer.set(x, y, color);
                }
            }
        }
    }
}
