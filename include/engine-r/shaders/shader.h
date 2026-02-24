#pragma once

#include <memory>
#include <utility>

#include "engine-m/vector/vector.h"
#include "engine-m/matrix/matrix.h"
#include "engine-r/color.h"
#include "engine-r/image_formats/tga.h"

namespace EngineR {
    struct ShaderUniforms {
        EngineM::mat4d modelViewMatrix;
        EngineM::mat4d perspectiveMatrix;
        EngineM::mat3d normalMatrix;
        std::shared_ptr<const TGAImage> normal_map;
    };

    struct VShaderInput {
        EngineM::vec3d normal;
        EngineM::vec2d uv_coords;
    };

    struct VShaderOutput {
        EngineM::vec4d vertex;
        EngineM::vec3d normal;
        EngineM::vec2d uv_coords;
    };

    struct FShaderInput {
        EngineM::vec3d normal;
        EngineM::vec2d uv_coords;
    };

    class Shader {
    public:
        virtual VShaderOutput vertex(EngineM::vec3d v, const VShaderInput &input, const ShaderUniforms &uniforms) = 0;
        [[nodiscard]] virtual std::pair<bool, Color> fragment(EngineM::vec3d bar, const FShaderInput &input, const ShaderUniforms &uniforms) = 0;

        virtual ~Shader() = default;
    };

    class DefaultShader : public Shader {
    public:
        Color color;

        VShaderOutput vertex(EngineM::vec3d v, const VShaderInput &input, const ShaderUniforms &uniforms) override;
        std::pair<bool, Color> fragment(EngineM::vec3d bar, const FShaderInput &input, const ShaderUniforms &uniforms) override;
    };
}
