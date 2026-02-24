#include "engine-r/renderer/object.h"

namespace EngineR {
    Object::Object(const std::vector<EngineM::vec3d> &vertices, const std::vector<EngineM::vec2d> &uv_coords, const std::vector<EngineM::vec3d> &normals, const std::vector<EngineM::vec3> &v_indices, const std::vector<EngineM::vec3> &uv_indices, const std::vector<EngineM::vec3> &n_indices): vertices(vertices), uv_coords(uv_coords), normals(normals), v_indices(v_indices), uv_indices(uv_indices), n_indices(n_indices), normal_map(nullptr), shader(nullptr) {

    }

    EngineM::vec3d Object::vertex(const int face, const int v) const {
        return vertices[v_indices[face][v]];
    }

    EngineM::vec2d Object::uv_coord(const int face, const int i) const {
        return uv_coords[uv_indices[face][i]];
    }

    EngineM::vec3d Object::normal(const int face, const int n) const {
        return normals[n_indices[face][n]];
    }

    Face Object::face(const int i) const {
        Face f;
        for (int j = 0; j < 3; j++) {
            f.vertices[j] = vertex(i, j);
            f.normals[j] = normal(i, j);
            f.uv_coords[j] = uv_coord(i, j);
        }

        return f;
    }

     std::shared_ptr<const TGAImage> Object::get_normal_map() const {
        return normal_map;
    }

    void Object::set_normal_map(std::shared_ptr<TGAImage> normal_map) {
        this -> normal_map = normal_map;
    }

    std::shared_ptr<const TGAImage> Object::get_diffuse_map() const {
        return diffuse_map;
    }

    void Object::set_diffuse_map(std::shared_ptr<TGAImage> diffuse_map) {
        this -> diffuse_map = diffuse_map;
    }

    std::shared_ptr<const TGAImage> Object::get_specular_map() const {
        return specular_map;
    }

    void Object::set_specular_map(std::shared_ptr<TGAImage> specular_map) {
        this -> specular_map = specular_map;
    }

    unsigned int Object::n_vertices() const {
        return vertices.size();
    }

    unsigned int Object::n_faces() const {
        return v_indices.size();
    }
}
