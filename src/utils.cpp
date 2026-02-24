#include "engine-r/utils.h"

#include <algorithm>

namespace EngineR {

    std::pair<EngineM::vec3d, EngineM::vec3d> get_bounding_box(const EngineM::vec3d &p1, const EngineM::vec3d &p2, const EngineM::vec3d &p3) {
        auto [ xmin, xmax ] = std::minmax({p1.x, p2.x, p3.x});
        auto [ ymin, ymax ] = std::minmax({p1.y, p2.y, p3.y});
        auto [ zmin, zmax ] = std::minmax({p1.z, p2.z, p3.z});

        return {{ xmin, ymin, zmin }, { xmax, ymax, zmax }};
    }

    double signed_triangle_area(const EngineM::vec3d &p1, const EngineM::vec3d &p2, const EngineM::vec3d &p3) {
        return 0.5 * (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
    }

    Color sampleTexture(const EngineM::vec2d &uv, const std::shared_ptr<const TGAImage> &texture) {
        return texture -> get(static_cast<int>(uv.x * texture -> getWidth()), static_cast<int>(uv.y * texture -> getHeight()));
    }

    EngineM::vec3d decodeTextureValue(const Color &color) {
        EngineM::vec3d v = {static_cast<double>(color.r), static_cast<double>(color.g), static_cast<double>(color.b)};
        return v / 255 * 2 - EngineM::vec3d{1, 1, 1};
    }
}
