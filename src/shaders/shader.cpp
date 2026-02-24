#include "engine-r/shaders/shader.h"

namespace EngineR {
    VShaderOutput DefaultShader::vertex(const EngineM::vec3d v, const VShaderInput &input, const ShaderUniforms &uniforms) {
        VShaderOutput output;
        output.vertex = uniforms.perspectiveMatrix * uniforms.modelViewMatrix * EngineM::vec4d{v, 1.0};
        return output;
    }

    std::pair<bool, Color> DefaultShader::fragment(EngineM::vec3d bar, const FShaderInput &input, const ShaderUniforms &uniforms) {
        return {false, color};
    }
}
