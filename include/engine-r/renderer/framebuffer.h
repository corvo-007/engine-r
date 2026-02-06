#pragma once
#include <cstdint>
#include <vector>

namespace EngineR {
    class Framebuffer {
        std::vector<std::uint32_t> buffer;
        int w;
        int h;

    public:
        Framebuffer(int w, int h);

        [[nodiscard]] std::uint32_t get(int x, int y) const;
        void set(int x, int y, std::uint32_t color);

        [[nodiscard]] int width() const;
        [[nodiscard]] int height() const;

        [[nodiscard]] const std::uint32_t* data() const;
    };
}
