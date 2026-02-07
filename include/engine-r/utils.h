#pragma once

#include <utility>

#include "engine-m/vector/vector3d.h"

namespace EngineR {
    std::pair<EngineM::vec3, EngineM::vec3> get_bounding_box(const EngineM::vec3 &p1, const EngineM::vec3 &p2, const EngineM::vec3 &p3);

    double signed_triangle_area(const EngineM::vec3 &p1, const EngineM::vec3 &p2, const EngineM::vec3 &p3);
}
