#pragma once

#include <utility>

#include "engine-m/vector/vector2d.h"

namespace EngineR {
    std::pair<EngineM::vec2, EngineM::vec2> get_bounding_box(const EngineM::vec2 &p1, const EngineM::vec2 &p2, const EngineM::vec2 &p3);

    double signed_triangle_area(const EngineM::vec2 &p1, const EngineM::vec2 &p2, const EngineM::vec2 &p3);
}
