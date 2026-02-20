#pragma once

#include "engine-r/renderer/framebuffer.h"
#include "engine-r/shaders/shader.h"

namespace EngineR {
    void triangle(const VShaderOutput vertex_output[3], Shader *shader, const EngineM::mat4d &viewportMatrix, Framebuffer &framebuffer);
}
