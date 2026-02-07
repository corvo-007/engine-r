#pragma once
#include <cstdint>
#include <vector>

namespace EngineR {
    class Framebuffer {
        std::vector<std::uint32_t> buffer;
        std::vector<std::uint32_t> zbuffer;
        int w;
        int h;

    public:
        Framebuffer(int w, int h);

        [[nodiscard]] std::uint32_t get(int x, int y) const;
        void set(int x, int y, std::uint32_t color);

        [[nodiscard]] std::uint32_t get_z(int x, int y) const;
        void set_z(int x, int y, std::uint32_t z);

        [[nodiscard]] int width() const;
        [[nodiscard]] int height() const;

        [[nodiscard]] const std::uint32_t* data() const;
        [[nodiscard]] const std::uint32_t* z_data() const;
    };
}
