#include "engine-r/rasterizer/triangle.h"

#include "engine-r/utils.h"

namespace EngineR {
    void triangle(const VShaderOutput vertex_output[3], Shader *shader, const EngineM::mat4d &viewportMatrix, Framebuffer &framebuffer) {
        EngineM::vec4d v[3];
        v[0] = vertex_output[0].vertex;
        v[1] = vertex_output[1].vertex;
        v[2] = vertex_output[2].vertex;

        EngineM::vec3d n[3];
        n[0] = vertex_output[0].normal;
        n[1] = vertex_output[1].normal;
        n[2] = vertex_output[2].normal;

        EngineM::vec4d ndc[3] = {{v[0] / v[0].w}, {v[1] / v[1].w}, {v[2] / v[2].w}};

        EngineM::vec3d p1 = (viewportMatrix * ndc[0]).xyz();
        EngineM::vec3d p2 = (viewportMatrix * ndc[1]).xyz();
        EngineM::vec3d p3 = (viewportMatrix * ndc[2]).xyz();

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

                input.normal = n[0] * alpha + n[1] * beta + n[2] * gamma;
                input.normal.normalise();

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
