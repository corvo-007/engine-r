#include "engine-r/shaders/shader.h"

namespace EngineR {
    EngineM::vec4d DefaultShader::vertex(const EngineM::vec3d v, const VShaderInput &input) {
        return input.perspectiveMatrix * input.modelViewMatrix * EngineM::vec4d{v, 1.0};
    }

    std::pair<bool, Color> DefaultShader::fragment(EngineM::vec3d bar, const FShaderInput &input) {
        return {false, color};
    }
}
