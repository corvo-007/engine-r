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
        i = (i + 1) % 3;

        VShaderOutput output;
        output.vertex = uniforms.perspectiveMatrix * vertex;
        output.normal = uniforms.normalMatrix * input.normal;
        output.uv_coords = input.uv_coords;

        return output;
    }

    std::pair<bool, Color> PhongShader::fragment(EngineM::vec3d bar, const FShaderInput &input, const ShaderUniforms &uniforms) {
        EngineM::vec2 normal_xy = uv_to_xy(input.uv_coords, uniforms.normal_map -> getWidth(), uniforms.normal_map -> getHeight());

        Color normal_c = uniforms.normal_map -> get(normal_xy.x, normal_xy.y);
        EngineM::vec3d normal = {static_cast<double>(normal_c.r), static_cast<double>(normal_c.g), static_cast<double>(normal_c.b)};

        normal /= 255;
        normal *= 2;
        normal -= {1, 1, 1};

        normal = uniforms.normalMatrix * normal;
        normal.normalise();

        double ln = light * normal;

        EngineM::vec3d reflected = normal * ln * 2 - light;
        reflected.normalise();

        Color color = {255, 255, 255, 255};

        double ambient = .3;
        double diffuse = .4 * std::max(0., ln);
        double specular = .9 * std::pow(std::max(0., reflected.z), shininess);

        color.r *= std::min(1., ambient + diffuse + specular);
        color.g *= std::min(1., ambient + diffuse + specular);
        color.b *= std::min(1., ambient + diffuse + specular);

        return {false, color};

    }
}
