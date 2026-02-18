#pragma once

#include <utility>

#include "engine-m/vector/vector.h"
#include "engine-m/matrix/matrix.h"
#include "engine-r/color.h"

namespace EngineR {
    struct VShaderInput {
        EngineM::mat4d modelViewMatrix;
        EngineM::mat4d perspectiveMatrix;
    };

    struct FShaderInput {

    };

    class Shader {
    public:
        virtual EngineM::vec4d vertex(EngineM::vec3d v, const VShaderInput &input) = 0;
        [[nodiscard]] virtual std::pair<bool, Color> fragment(EngineM::vec3d bar, const FShaderInput &input) = 0;

        virtual ~Shader() = default;
    };

    class DefaultShader : public Shader {
    public:
        Color color;

        EngineM::vec4d vertex(EngineM::vec3d v, const VShaderInput &input) override;
        std::pair<bool, Color> fragment(EngineM::vec3d bar, const FShaderInput &input) override;
    };
}
