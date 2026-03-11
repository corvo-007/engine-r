#pragma once

#include "engine-r/renderer/buffer.h"
#include "engine-r/shaders/shader.h"

namespace EngineR {
    void triangle(const VShaderOutput vertex_output[3], Shader *shader, const ShaderUniforms &uniforms, const EngineM::mat4d &viewportMatrix, Buffer<Color> &framebuffer, Buffer<double> &zbuffer);
}
