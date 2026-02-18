#pragma once

#include "engine-r/shaders/shader.h"

namespace EngineR {
    class PhongShader : public Shader {
    public:
        EngineM::vec3d vertices[3];
        EngineM::vec3d light;
        int shininess;
        int i;

        PhongShader(const EngineM::vec3d &light, int shininess);

        EngineM::vec4d vertex(EngineM::vec3d v, const VShaderInput &input) override;
        std::pair<bool, uint32_t> fragment(EngineM::vec3d bar, const FShaderInput &input) override;
    };
}
