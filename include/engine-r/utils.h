#pragma once

#include <utility>

#include "engine-m/vector/vector.h"

namespace EngineR {
    std::pair<EngineM::vec3d, EngineM::vec3d> get_bounding_box(const EngineM::vec3d &p1, const EngineM::vec3d &p2, const EngineM::vec3d &p3);

    double signed_triangle_area(const EngineM::vec3d &p1, const EngineM::vec3d &p2, const EngineM::vec3d &p3);
}
