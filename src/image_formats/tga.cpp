#include "engine-r/image_formats/tga.h"

#include <cstring>
#include <stdexcept>
#include <string>

namespace EngineR {
    TGAImage::TGAImage(int width, int height, int bytes_per_pixel, bool top_to_bottom): image_data(width * height * bytes_per_pixel, 0), width(width), height(height), bytes_per_pixel(bytes_per_pixel), top_to_bottom(top_to_bottom) {}

    TGAImage::TGAImage(const std::vector<uint8_t> &image_data, int width, int height, int bytes_per_pixel, bool top_to_bottom): image_data(image_data), width(width), height(height), bytes_per_pixel(bytes_per_pixel), top_to_bottom(top_to_bottom) {}

    Color TGAImage::get(int x, int y) const {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            throw std::out_of_range("x = " + std::to_string(x));
        }

        if (!top_to_bottom) {
            y = height - 1 - y;
        }

        if (bytes_per_pixel == 1) {
            uint8_t gray = image_data[x + y * width];
            return { gray, gray, gray, 1 };
        }

        uint8_t buffer[4];
        memcpy(buffer, image_data.data() + (x + y * width) * bytes_per_pixel, bytes_per_pixel);
        return { buffer[2], buffer[1], buffer[0], bytes_per_pixel == 4 ? buffer[3] : static_cast<uint8_t>(255) };
    }

    void TGAImage::set(int x, int y, const Color &color) {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            throw std::out_of_range("x = " + std::to_string(x));
        }

        if (!top_to_bottom) {
            y = height - 1 - y;
        }

        if (bytes_per_pixel == 1) {
            image_data[x + y * height] = color.r;
            return;
        }
        uint8_t *ptr = image_data.data() + x + y * width;

        for (int i = 0; i < bytes_per_pixel; i++) {
            ptr[i] = color.rgba[(i + 1) % 4];
        }
    }

    int TGAImage::getWidth() const {
        return width;
    }

    int TGAImage::getHeight() const {
        return height;
    }

    const uint32_t* TGAImage::data() const {
        size_t size = width * height;
        auto *d = new Color[size];

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                d[x + y * width] = get(x, y);
            }
        }

        return reinterpret_cast<uint32_t*>(d);
    }
}
