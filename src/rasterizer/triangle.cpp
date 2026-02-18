#include "engine-r/rasterizer/triangle.h"

#include "engine-r/utils.h"

namespace EngineR {
    void triangle(const EngineM::vec4d v[3], Shader *shader, const EngineM::mat4d &viewportMatrix, Framebuffer &framebuffer) {
        EngineM::vec4d ndc[3] = {{v[0] / v[0].w}, {v[1] / v[1].w}, {v[2] / v[2].w}};

        EngineM::vec4d t1 = viewportMatrix * ndc[0];
        EngineM::vec4d t2 = viewportMatrix * ndc[1];
        EngineM::vec4d t3 = viewportMatrix * ndc[2];

        EngineM::vec3d p1 = {t1.x, t1.y, t1.z};
        EngineM::vec3d p2 = {t2.x, t2.y, t2.z};
        EngineM::vec3d p3 = {t3.x, t3.y, t3.z};

        auto [ p_min, p_max ] = get_bounding_box(p1, p2, p3);
        const double total_signed_area = signed_triangle_area(p1, p2, p3);
        if (total_signed_area < 1) {
            return ;
        }

        int p_min_x = static_cast<int>(p_min.x);
        int p_min_y = static_cast<int>(p_min.y);
        int p_max_x = static_cast<int>(p_max.x);
        int p_max_y = static_cast<int>(p_max.y);

        FShaderInput input;

        for (int y = p_min_y; y <= p_max_y; y++) {
            for (int x = p_min_x; x <= p_max_x; x++) {
                double alpha = signed_triangle_area({x, y, 0}, p2, p3) / total_signed_area;
                double beta = signed_triangle_area(p1, {x, y, 0}, p3) / total_signed_area;
                double gamma = signed_triangle_area(p1, p2, {x, y, 0}) / total_signed_area;

                if (alpha < 0 || beta < 0 || gamma < 0) {
                    continue;
                }

                auto [discard, color] = shader -> fragment({alpha, beta, gamma}, input);

                if (discard) {
                    continue;
                }

                double z = alpha * p1.z + beta * p2.z + gamma * p3.z;
                if (framebuffer.get_z(x, y) < z) {
                    framebuffer.set_z(x, y, z);
                    framebuffer.set(x, y, color);
                }
            }
        }
    }
}
