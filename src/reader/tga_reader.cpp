#include "engine-r/reader/tga_reader.h"

#include <cstring>
#include <fstream>

#include "engine-r/color.h"

namespace EngineR {
    TGAImage* TGAReader::read_tga_image(const std::string &filename) {
        std::ifstream fin(filename, std::ios::binary);

        if (fin.fail()) {
            throw std::runtime_error("Failed to open TGA file");
        }

        TGAImage::Header header{};

        fin.read(reinterpret_cast<char*>(&header), sizeof(header));

        if (header.width <= 0 || header.height <= 0) {
            throw std::runtime_error("Invalid TGA file header");
        }

        uint8_t bytespp = header.pixel_depth >> 3;

        int n_image_bytes = bytespp * header.width * header.height;

        std::vector<uint8_t> image_data(n_image_bytes, 0);

        if (header.image_type == 2 || header.image_type == 3) {
            fin.read(reinterpret_cast<char*>(image_data.data()), n_image_bytes);
        }
        else if (header.image_type == 10 || header.image_type == 11) {
            read_rle_data(fin, header, image_data.data());
        }
        else {
            throw std::runtime_error("Only image_type 2, 3, 10, and 11 are supported");
        }

        return new TGAImage(image_data, header.width, header.height, bytespp, static_cast<bool>(header.image_descriptor & 0x20));
    }

    void TGAReader::read_rle_data(std::ifstream &fin, const TGAImage::Header &header, uint8_t *data) {
        fin.seekg(header.id_length, std::ios::cur);

        int pixel_count = 0;
        int total_pixels = header.width * header.height;
        uint8_t bytespp = header.pixel_depth >> 3;

        while (pixel_count < total_pixels) {
            uint8_t packet_header;
            fin.read(reinterpret_cast<char*>(&packet_header), 1);

            if (packet_header & 0x80) { // run-length packet
                packet_header = (packet_header & 0x7F) + 1;
                auto *buffer = new uint8_t[bytespp];
                fin.read(reinterpret_cast<char*>(buffer), bytespp);
                for (int i = 0; i < packet_header; i++) {
                    memcpy(data + pixel_count * bytespp, buffer, bytespp);
                    pixel_count++;
                }
                delete [] buffer;
            }
            else { // raw packet
                packet_header++;
                fin.read(reinterpret_cast<char*>(data + pixel_count * bytespp), packet_header * bytespp);
                pixel_count += packet_header;
            }
        }
    }
}
