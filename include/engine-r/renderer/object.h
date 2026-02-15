#pragma once

#include <vector>

#include "engine-m/vector/vector.h"

namespace EngineR {
    class Object {
        std::vector<EngineM::vec3d> vertices;
        std::vector<EngineM::vec3> face_indices;

    public:
        Object(const std::vector<EngineM::vec3d> &vertices, const std::vector<EngineM::vec3> &face_indices);

        [[nodiscard]] EngineM::vec3d vertex(int i) const;
        [[nodiscard]] EngineM::vec3d vertex(int face, int v) const;

        [[nodiscard]] unsigned int n_vertices() const;
        [[nodiscard]] unsigned int n_faces() const;
    };
}
