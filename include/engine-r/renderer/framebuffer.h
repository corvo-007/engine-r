#pragma once
#include <vector>

#include "engine-r/color.h"

namespace EngineR {
    class Framebuffer {
        std::vector<Color> buffer;
        std::vector<double> zbuffer;
        int w;
        int h;

    public:
        Framebuffer(int w, int h);

        [[nodiscard]] Color get(int x, int y) const;
        void set(int x, int y, Color color);

        [[nodiscard]] double get_z(int x, int y) const;
        void set_z(int x, int y, double z);

        [[nodiscard]] int width() const;
        [[nodiscard]] int height() const;

        [[nodiscard]] const std::uint32_t* data() const;
        [[nodiscard]] const double* z_data() const;
    };
}
