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

    struct VShaderOutput {
        EngineM::vec4d vertex;
    };

    struct FShaderInput {

    };

    class Shader {
    public:
        virtual VShaderOutput vertex(EngineM::vec3d v, const VShaderInput &input) = 0;
        [[nodiscard]] virtual std::pair<bool, Color> fragment(EngineM::vec3d bar, const FShaderInput &input) = 0;

        virtual ~Shader() = default;
    };

    class DefaultShader : public Shader {
    public:
        Color color;

        VShaderOutput vertex(EngineM::vec3d v, const VShaderInput &input) override;
        std::pair<bool, Color> fragment(EngineM::vec3d bar, const FShaderInput &input) override;
    };
}
