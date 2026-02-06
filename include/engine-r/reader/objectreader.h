#pragma once

#include <string>

#include "engine-r/renderer/object.h"

namespace EngineR {
    class ObjectReader {
    public:
        static Object read_object(const std::string &filename);
    };
}
