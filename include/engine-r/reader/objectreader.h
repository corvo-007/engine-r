#pragma once

#include <string>

#include "engine-r/image_formats/tga.h"
#include "engine-r/renderer/object.h"

namespace EngineR {
    class ObjectReader {
    public:
        static Object read_object(const std::string &filename);
        static TGAImage* load_texture(const std::string &filename);
    };
}
