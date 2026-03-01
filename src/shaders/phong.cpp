#include "engine-r/shaders/phong.h"

#include <algorithm>
#include <cmath>

#include "engine-r/utils.h"

namespace EngineR {
    PhongShader::PhongShader(const EngineM::vec3d &light, int shininess): vertices{}, light(light), shininess(shininess), i{} {
        this -> light.normalise();
    }

    VShaderOutput PhongShader::vertex(EngineM::vec3d v, const VShaderInput &input, const ShaderUniforms &uniforms) {
        EngineM::vec4d vertex = uniforms.modelViewMatrix * EngineM::vec4d{v, 1};

        vertices[i] = vertex.xyz();
        uv_coords[i] = input.uv_coords;

        EngineM::mat3x2d TB;

        if (i == 2) {
            EngineM::vec3d edge1 = vertices[1] - vertices[0];
            EngineM::vec3d edge2 = vertices[2] - vertices[0];

            EngineM::vec2d u1 = uv_coords[1] - uv_coords[0];
            EngineM::vec2d u2 = uv_coords[2] - uv_coords[0];

            EngineM::Matrix<double, 3, 2> E{{edge1.x, edge2.x, edge1.y, edge2.y, edge1.z, edge2.z}};
            EngineM::mat2d U{{u1.x, u2.x, u1.y, u2.y}};

            U.inverse();

            TB = E * U;
        }

        i = (i + 1) % 3;

        VShaderOutput output;
        output.vertex = uniforms.perspectiveMatrix * vertex;
        output.normal = uniforms.normalMatrix * input.normal;
        output.uv_coords = input.uv_coords;
        output.TB = TB;

        return output;
    }

    std::pair<bool, Color> PhongShader::fragment(EngineM::vec3d bar, const FShaderInput &input, const ShaderUniforms &uniforms) {
        EngineM::mat3d basis{{input.TB[0][0], input.TB[0][1], input.normal.x, input.TB[1][0], input.TB[1][1], input.normal.y, input.TB[2][0], input.TB[2][1], input.normal.z}};

        EngineM::vec3d T = {input.TB[0][0], input.TB[1][0], input.TB[2][0]};
        T = (T - input.normal * (T * input.normal)).normalise(); // Gram-Schmidt process, re-orthogonalize
        EngineM::vec3d B = input.normal ^ T;

        basis[0][0] = T.x;
        basis[1][0] = T.y;
        basis[2][0] = T.z;
        basis[0][1] = B.x;
        basis[1][1] = B.y;
        basis[2][1] = B.z;

        Color normal_c = sampleTexture(input.uv_coords, uniforms.normal_map);
        EngineM::vec3d normal = decodeTextureValue(normal_c);

        normal = (basis * normal).normalise();

        double ln = light * normal;

        EngineM::vec3d reflected = (normal * ln * 2 - light).normalise();

        Color color = sampleTexture(input.uv_coords, uniforms.diffuse_map);
        Color specular_c = sampleTexture(input.uv_coords, uniforms.specular_map);

        double ambient = .3;
        double diffuse = std::max(0., ln);
        double specular = specular_c.r / 255. * std::pow(std::max(0., reflected.z), shininess);

        color.r = std::min<int>(255, color.r * (ambient + diffuse) + 255. * specular);
        color.g = std::min<int>(255, color.g * (ambient + diffuse) + 255. * specular);
        color.b = std::min<int>(255, color.b * (ambient + diffuse) + 255. * specular);

        return {false, color};

    }
}
