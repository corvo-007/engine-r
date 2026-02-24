#pragma once

#include <memory>
#include <utility>

#include "color.h"
#include "engine-m/vector/vector.h"
#include "image_formats/tga.h"

namespace EngineR {
    std::pair<EngineM::vec3d, EngineM::vec3d> get_bounding_box(const EngineM::vec3d &p1, const EngineM::vec3d &p2, const EngineM::vec3d &p3);

    double signed_triangle_area(const EngineM::vec3d &p1, const EngineM::vec3d &p2, const EngineM::vec3d &p3);

    Color sampleTexture(const EngineM::vec2d &uv, const std::shared_ptr<const TGAImage> &texture);

    EngineM::vec3d decodeTextureValue(const Color &color);
}
