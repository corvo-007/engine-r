#include "engine-r/reader/objectreader.h"

#include <fstream>
#include <sstream>

#include "engine-m/vector/vector.h"


namespace EngineR {
    Object ObjectReader::read_object(const std::string &filename) {
        std::ifstream stream(filename);

        if (stream.fail()) {
            throw std::runtime_error("Failed to open file");
        }

        std::vector<EngineM::vec3d> vertices;
        std::vector<EngineM::vec3d> normals;
        std::vector<EngineM::vec3> vertex_indices;
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
            else if (line.starts_with("vn ")) {
                EngineM::vec3d n;
                iss >> trash >> trash >> n[0] >> n[1] >> n[2];
                normals.push_back(n);
            }
            else if (line.starts_with("f ")) {
                EngineM::vec3 v_indices;
                EngineM::vec3 n_indices;

                iss >> trash;
                int i = 0, f, a, n;
                while (iss >> f >> trash >> a >> trash >> n) {
                    v_indices[i] = f - 1;
                    n_indices[i++] = n - 1;
                }

                vertex_indices.push_back(v_indices);
                normal_indices.push_back(n_indices);
            }
        }

        return {vertices, normals, vertex_indices, normal_indices};
    }
}
