#include "engine-r/shaders/phong.h"

#include <algorithm>
#include <cmath>

namespace EngineR {
    PhongShader::PhongShader(const EngineM::vec3d &light, int shininess): vertices{}, light(light), shininess(shininess), i{} {
        this -> light.normalise();
    }

    EngineM::vec4d PhongShader::vertex(EngineM::vec3d v, const VShaderInput &input) {
        EngineM::vec4d result = input.modelViewMatrix * EngineM::vec4d{v.x, v.y, v.z, 1};

        vertices[i] = {result.x, result.y, result.z};
        i = (i + 1) % 3;
        return input.perspectiveMatrix * result;
    }

    std::pair<bool, Color> PhongShader::fragment(EngineM::vec3d bar, const FShaderInput &input) {
        EngineM::vec3d edge1 = vertices[1] - vertices[0];
        EngineM::vec3d edge2 = vertices[2] - vertices[0];

        EngineM::vec3d n = edge1 ^ edge2;
        n.normalise();

        double ln = light * n;

        EngineM::vec3d reflected = n * ln * 2 - light;
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
