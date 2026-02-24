#pragma once

#include <memory>
#include <vector>

#include "engine-r/shaders/shader.h"
#include "engine-m/vector/vector.h"
#include "engine-r/image_formats/tga.h"

namespace EngineR {
    class Face {
    public:
        EngineM::vec3d vertices[3];
        EngineM::vec3d normals[3];
        EngineM::vec2d uv_coords[3];
    };

    class Object {
        std::vector<EngineM::vec3d> vertices;
        std::vector<EngineM::vec2d> uv_coords;
        std::vector<EngineM::vec3d> normals;
        std::vector<EngineM::vec3> v_indices;
        std::vector<EngineM::vec3> uv_indices;
        std::vector<EngineM::vec3> n_indices;

        std::shared_ptr<TGAImage> normal_map;
        std::shared_ptr<TGAImage> diffuse_map;
        std::shared_ptr<TGAImage> specular_map;

    public:
        Shader *shader;

        Object(const std::vector<EngineM::vec3d> &vertices, const std::vector<EngineM::vec2d> &uv_coords, const std::vector<EngineM::vec3d> &normals, const std::vector<EngineM::vec3> &v_indices, const std::vector<EngineM::vec3> &uv_indices, const std::vector<EngineM::vec3> &n_indices);

        [[nodiscard]] EngineM::vec3d vertex(int face, int v) const;
        [[nodiscard]] EngineM::vec2d uv_coord(int face, int i) const;
        [[nodiscard]] EngineM::vec3d normal(int face, int n) const;

        [[nodiscard]] Face face(int i) const;

        [[nodiscard]] std::shared_ptr<const TGAImage> get_normal_map() const;
        void set_normal_map(std::shared_ptr<TGAImage> normal_map);

        [[nodiscard]] std::shared_ptr<const TGAImage> get_diffuse_map() const;
        void set_diffuse_map(std::shared_ptr<TGAImage> diffuse_map);

        [[nodiscard]] std::shared_ptr<const TGAImage> get_specular_map() const;
        void set_specular_map(std::shared_ptr<TGAImage> specular_map);

        [[nodiscard]] unsigned int n_vertices() const;
        [[nodiscard]] unsigned int n_faces() const;
    };
}
