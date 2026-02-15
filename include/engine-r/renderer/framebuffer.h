#pragma once
#include <cstdint>
#include <vector>

namespace EngineR {
    class Framebuffer {
        std::vector<std::uint32_t> buffer;
        std::vector<double> zbuffer;
        int w;
        int h;

    public:
        Framebuffer(int w, int h);

        [[nodiscard]] std::uint32_t get(int x, int y) const;
        void set(int x, int y, std::uint32_t color);

        [[nodiscard]] double get_z(int x, int y) const;
        void set_z(int x, int y, double z);

        [[nodiscard]] int width() const;
        [[nodiscard]] int height() const;

        [[nodiscard]] const std::uint32_t* data() const;
        [[nodiscard]] const double* z_data() const;
    };
}
