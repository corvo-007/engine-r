#pragma once

#include <cstdint>
#include <vector>

#include "engine-r/color.h"

namespace EngineR {
    class TGAImage {
    public:
#pragma pack(push, 1)
        struct Header {
            uint8_t id_length;
            uint8_t color_map_type;
            uint8_t image_type;
            uint16_t first_entry_index;
            uint16_t color_map_length;
            uint8_t color_map_entry_size;
            uint16_t x_origin;
            uint16_t y_origin;
            uint16_t width;
            uint16_t height;
            uint8_t pixel_depth;
            uint8_t image_descriptor;
        };
#pragma pack(pop)

    private:
        std::vector<uint8_t> image_data;
        int width;
        int height;
        int bytes_per_pixel;
        bool top_to_bottom;

    public:
        TGAImage(int width, int height, int pixel_depth, bool top_to_bottom);
        TGAImage(const std::vector<uint8_t> &image_data, int width, int height, int bytes_per_pixel, bool top_to_bottom);

        [[nodiscard]] Color get(int x, int y) const;
        void set(int x, int y, const Color &color);

        [[nodiscard]] int getWidth() const;
        [[nodiscard]] int getHeight() const;

        [[nodiscard]] const uint32_t* data() const;
    };
}
