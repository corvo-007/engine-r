#pragma once

#include "engine-r/shaders/shader.h"

namespace EngineR {
    class PhongShader : public Shader {
    public:
        EngineM::vec3d vertices[3];
        EngineM::vec2d uv_coords[3];
        int shininess;
        int i;

        PhongShader(int shininess);

        VShaderOutput vertex(EngineM::vec3d v, const VShaderInput &input, const ShaderUniforms &uniforms) override;
        std::pair<bool, Color> fragment(EngineM::vec3d bar, const FShaderInput &input, const ShaderUniforms &uniforms) override;
    };
}
