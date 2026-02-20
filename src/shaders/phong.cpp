#include "engine-r/shaders/phong.h"

#include <algorithm>
#include <cmath>

namespace EngineR {
    PhongShader::PhongShader(const EngineM::vec3d &light, int shininess): vertices{}, light(light), shininess(shininess), i{} {
        this -> light.normalise();
    }

    VShaderOutput PhongShader::vertex(EngineM::vec3d v, const VShaderInput &input) {
        EngineM::vec4d vertex = input.modelViewMatrix * EngineM::vec4d{v, 1};

        vertices[i] = vertex.xyz();
        i = (i + 1) % 3;

        VShaderOutput output;
        output.vertex = input.perspectiveMatrix * vertex;
        output.normal = input.normalMatrix * input.normal;

        return output;
    }

    std::pair<bool, Color> PhongShader::fragment(EngineM::vec3d bar, const FShaderInput &input) {

        double ln = light * input.normal;

        EngineM::vec3d reflected = input.normal * ln * 2 - light;
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
