#include "engine-r/renderer/framebuffer.h"

#include <limits>

namespace EngineR {
    Framebuffer::Framebuffer(const int w, const int h): buffer(w * h), zbuffer(w * h, std::numeric_limits<double>::lowest()), w(w), h(h) {}

    Color Framebuffer::get(const int x, const int y) const {
        if (x < 0 || x >= w || y < 0 || y >= h) {
            return {};
        }
        return buffer[x + (h - 1 - y) * w];
    }

    void Framebuffer::set(const int x, const int y, const Color color) {
        if (x >= 0 && x < w && y >= 0 && y < h) {
            buffer[x + (h - 1 - y) * w] = color;
        }
    }

    double Framebuffer::get_z(const int x, const int y) const {
        if (x < 0 || x >= w || y < 0 || y >= h) {
            return 0;
        }
        return zbuffer[x + (h - 1 - y) * w];
    }

    void Framebuffer::set_z(const int x, const int y, const double z) {
        if (x >= 0 && x < w && y >= 0 && y < h) {
            zbuffer[x + (h - 1 - y) * w] = z;
        }
    }

    int Framebuffer::width() const {
        return w;
    }

    int Framebuffer::height() const {
        return h;
    }

    const std::uint32_t* Framebuffer::data() const {
        return reinterpret_cast<const uint32_t*>(buffer.data());
    }

    const double* Framebuffer::z_data() const {
        return zbuffer.data();
    }
}
