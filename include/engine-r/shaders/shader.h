#pragma once

#include <utility>

#include "engine-m/vector/vector.h"
#include "engine-m/matrix/matrix.h"

namespace EngineR {
    class Shader {
    public:
        virtual EngineM::vec4d vertex(EngineM::vec3d v, const EngineM::mat4d &mvp) = 0;
        [[nodiscard]] virtual std::pair<bool, uint32_t> fragment(EngineM::vec3d bar) = 0;

        virtual ~Shader() = default;
    };

    class DefaultShader : public Shader {
    public:
        uint32_t color;

        EngineM::vec4d vertex(EngineM::vec3d v, const EngineM::mat4d &mvp) override;
        std::pair<bool, uint32_t> fragment(EngineM::vec3d bar) override;
    };
}
