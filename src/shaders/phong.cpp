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
        Color normal_c = sampleTexture(input.uv_coords, uniforms.normal_map);
        EngineM::vec3d normal = decodeTextureValue(normal_c);

        normal = (uniforms.normalMatrix * normal).normalise();

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
