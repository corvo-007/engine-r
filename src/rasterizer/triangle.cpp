#include "engine-r/rasterizer/triangle.h"

#include "engine-r/utils.h"

namespace EngineR {
    void triangle(const VShaderOutput vertex_output[3], Shader *shader, const ShaderUniforms &uniforms, const EngineM::mat4d &viewportMatrix, Framebuffer &framebuffer) {
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

        int frame_x_start = std::max(0, static_cast<int>(p_min.x));
        int frame_y_start = std::max(0, static_cast<int>(p_min.y));
        int frame_x_end = std::min(static_cast<int>(p_max.x), framebuffer.width());
        int frame_y_end = std::min(static_cast<int>(p_max.y), framebuffer.height());

        FShaderInput input;

        for (int y = frame_y_start; y <= frame_y_end; y++) {
            for (int x = frame_x_start; x <= frame_x_end; x++) {
                double alpha = signed_triangle_area({x, y, 0}, p2, p3) / total_signed_area;
                double beta = signed_triangle_area(p1, {x, y, 0}, p3) / total_signed_area;
                double gamma = signed_triangle_area(p1, p2, {x, y, 0}) / total_signed_area;

                if (alpha < 0 || beta < 0 || gamma < 0) {
                    continue;
                }

                EngineM::vec3d bc = {alpha / v[0].w, beta / v[1].w, gamma / v[2].w};
                bc /= bc[0] + bc[1] + bc[2];

                input.normal = (n[0] * bc[0] + n[1] * bc[1] + n[2] * bc[2]).normalise();

                input.uv_coords = vertex_output[0].uv_coords * bc[0] + vertex_output[1].uv_coords * bc[1] + vertex_output[2].uv_coords * bc[2];

                input.TB = vertex_output[2].TB;

                auto [discard, color] = shader -> fragment(bc, input, uniforms);

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
