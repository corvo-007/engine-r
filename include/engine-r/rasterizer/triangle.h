#pragma once

#include "engine-m/vector/vector.h"
#include "engine-r/renderer/framebuffer.h"
#include "engine-r/shaders/shader.h"

namespace EngineR {
    void triangle(const EngineM::vec4d v[3], Shader *shader, const EngineM::mat4d &viewportMatrix, Framebuffer &framebuffer);
}
