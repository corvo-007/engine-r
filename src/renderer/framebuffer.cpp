#include "engine-r/renderer/framebuffer.h"

namespace EngineR {
    Framebuffer::Framebuffer(const int w, const int h): buffer(w * h), w(w), h(h) {}

    std::uint32_t Framebuffer::get(const int x, const int y) const {
        if (x < 0 || x >= w || y < 0 || y >= h) {
            return 0;
        }
        return buffer[x + y * w];
    }

    void Framebuffer::set(const int x, const int y, const std::uint32_t color) {
        if (x >= 0 && x < w && y >= 0 && y < h) {
            buffer[x + y * w] = color;
        }
    }

    int Framebuffer::width() const {
        return w;
    }

    int Framebuffer::height() const {
        return h;
    }

    const std::uint32_t* Framebuffer::data() const {
        return buffer.data();
    }
}
