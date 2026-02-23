#pragma once

#include <string>

#include "engine-r/image_formats/tga.h"

namespace EngineR {
    class TGAReader {
    public:
        static TGAImage* read_tga_image(const std::string &filename);
        static void read_rle_data(std::ifstream &fin, const TGAImage::Header &header, uint8_t *data);
    };
}
