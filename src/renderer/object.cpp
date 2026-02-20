#include "engine-r/renderer/object.h"

namespace EngineR {
    Object::Object(const std::vector<EngineM::vec3d> &vertices, const std::vector<EngineM::vec3d> &normals, const std::vector<EngineM::vec3> &v_indices, const std::vector<EngineM::vec3> &n_indices): vertices(vertices), normals(normals), v_indices(v_indices), n_indices(n_indices), shader(nullptr) {

    }

    EngineM::vec3d Object::vertex(const int i) const {
        return vertices[i];
    }

    EngineM::vec3d Object::vertex(const int face, const int v) const {
        return vertices[v_indices[face][v]];
    }

    EngineM::vec3d Object::normal(const int i) const {
        return normals[i];
    }

    EngineM::vec3d Object::normal(const int face, const int n) const {
        return normals[n_indices[face][n]];
    }

    Face Object::face(const int i) const {
        Face f;
        for (int j = 0; j < 3; j++) {
            f.vertices[j] = vertex(i, j);
            f.normals[j] = normal(i, j);
        }

        return f;
    }

    unsigned int Object::n_vertices() const {
        return vertices.size();
    }

    unsigned int Object::n_faces() const {
        return v_indices.size();
    }
}
