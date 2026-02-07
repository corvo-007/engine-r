#include "engine-r/utils.h"

#include <algorithm>

namespace EngineR {

    std::pair<EngineM::vec3, EngineM::vec3> get_bounding_box(const EngineM::vec3 &p1, const EngineM::vec3 &p2, const EngineM::vec3 &p3) {
        int xmin = std::min(p1.x, std::min(p2.x, p3.x));
        int ymin = std::min(p1.y, std::min(p2.y, p3.y));
        int zmin = std::min(p1.z, std::min(p2.z, p3.z));
        int xmax = std::max(p1.x, std::max(p2.x, p3.x));
        int ymax = std::max(p1.y, std::max(p2.y, p3.y));
        int zmax = std::max(p1.z, std::max(p2.z, p3.z));
        return {{ xmin, ymin, zmin }, { xmax, ymax, zmax }};
    }

    double signed_triangle_area(const EngineM::vec3 &p1, const EngineM::vec3 &p2, const EngineM::vec3 &p3) {
        return 0.5 * (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
    }
}
