#include "engine-r/renderer/object.h"

namespace EngineR {
    Object::Object(const std::vector<EngineM::vec3d> &vertices, const std::vector<EngineM::vec3> &face_indices): vertices(vertices), face_indices(face_indices) {

    }

    EngineM::vec3d Object::vertex(const int i) const {
        return vertices[i];
    }

    EngineM::vec3d Object::vertex(const int face, const int v) const {
        return vertices[face_indices[face][v]];
    }

    unsigned int Object::n_vertices() const {
        return vertices.size();
    }

    unsigned int Object::n_faces() const {
        return face_indices.size();
    }
}
