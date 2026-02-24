#include "engine-r/reader/objectreader.h"

#include <filesystem>
#include <fstream>
#include <sstream>

#include "engine-m/vector/vector.h"
#include "engine-r/reader/tga_reader.h"


namespace EngineR {
    Object ObjectReader::read_object(const std::string &filename) {
        std::ifstream stream(filename);

        if (stream.fail()) {
            throw std::runtime_error("Failed to open file");
        }

        std::vector<EngineM::vec3d> vertices;
        std::vector<EngineM::vec2d> uv_coords;
        std::vector<EngineM::vec3d> normals;
        std::vector<EngineM::vec3> vertex_indices;
        std::vector<EngineM::vec3> uv_indices;
        std::vector<EngineM::vec3> normal_indices;

        std::string line;
        while (std::getline(stream, line)) {
            std::istringstream iss(line);
            char trash;
            if (line.starts_with("v ")) {
                EngineM::vec3d v;
                iss >> trash >> v[0] >> v[1] >> v[2];
                vertices.push_back(v);
            }
            else if (line.starts_with("vt ")) {
                EngineM::vec2d uv;
                iss >> trash >> trash >> uv[0] >> uv[1];
                uv_coords.push_back(uv);
            }
            else if (line.starts_with("vn ")) {
                EngineM::vec3d n;
                iss >> trash >> trash >> n[0] >> n[1] >> n[2];
                normals.push_back(n);
            }
            else if (line.starts_with("f ")) {
                EngineM::vec3 v_indices;
                EngineM::vec3 uv_i;
                EngineM::vec3 n_indices;

                iss >> trash;
                int i = 0, f, uv, n;
                while (iss >> f >> trash >> uv >> trash >> n) {
                    v_indices[i] = f - 1;
                    uv_i[i] = uv - 1;
                    n_indices[i] = n - 1;
                    i++;
                }

                vertex_indices.push_back(v_indices);
                uv_indices.push_back(uv_i);
                normal_indices.push_back(n_indices);
            }
        }

        Object obj(vertices, uv_coords, normals, vertex_indices, uv_indices, normal_indices);

        std::string normal_map_filename = filename.substr(0, filename.find_last_of('.')) + "_nm.tga";
        if (std::filesystem::exists(normal_map_filename)) {
            obj.set_normal_map(std::shared_ptr<TGAImage>(load_texture(normal_map_filename)));
        }

        return obj;
    }

    TGAImage* ObjectReader::load_texture(const std::string &filename) {
        return TGAReader::read_tga_image(filename);
    }
}
