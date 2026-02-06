#include "engine-r/reader/objectreader.h"

#include <fstream>
#include <sstream>

#include "engine-m/vector/vector3d.h"


namespace EngineR {
    Object ObjectReader::read_object(const std::string &filename) {
        std::ifstream stream(filename);

        if (stream.fail()) {
            return {{}, {}};
        }

        std::vector<EngineM::vec3f> vertices;
        std::vector<EngineM::vec3> face_indices;

        std::string line;
        while (std::getline(stream, line)) {
            std::istringstream iss(line);
            char trash;
            if (line.starts_with("v ")) {
                EngineM::vec3f v;
                iss >> trash >> v[0] >> v[1] >> v[2];
                vertices.push_back(v);
            }
            if (line.starts_with("f ")) {
                EngineM::vec3 f_indices;

                iss >> trash;
                int i = 0, f, a, b;
                while (iss >> f >> trash >> a >> trash >> b) {
                    f_indices[i++] = f - 1;
                }

                face_indices.push_back(f_indices);
            }
        }

        return {vertices, face_indices};
    }
}
