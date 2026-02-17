#include "engine-r/shaders/shader.h"

namespace EngineR {
    EngineM::vec4d DefaultShader::vertex(const EngineM::vec3d v, const EngineM::mat4d &mvp) {
        return mvp * EngineM::vec4d{v.x, v.y, v.z, 1.0};
    }

    std::pair<bool, uint32_t> DefaultShader::fragment(EngineM::vec3d bar) {
        return {false, color};
    }
}
