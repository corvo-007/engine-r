#include "engine-r/renderer/renderer.h"

#include <cmath>

#include "engine-r/rasterizer/line.h"
#include "engine-r/rasterizer/triangle.h"

namespace EngineR {
    Renderer::Renderer(const int width, const int height) : framebuffer(width, height) {}

    EngineM::vec3 Renderer::transform(const EngineM::vec3f &p) const {
        auto t = (p + EngineM::vec3f{1, 1, 1}) / 2;
        return {static_cast<int>(t.x * framebuffer.width()), static_cast<int>(t.y * framebuffer.height()), static_cast<int>(t.z * 255)};
    }

    void Renderer::setPoint(const EngineM::vec2 &p, const std::uint32_t color) {
        framebuffer.set(static_cast<int>(std::round(p.x)), static_cast<int>(std::round(p.y)), color);
    }

    void Renderer::drawLine(const EngineM::vec2 &p1, const EngineM::vec2 &p2, const std::uint32_t color) {
        line(p1, p2, color, framebuffer);
    }

    void Renderer::drawTriangle(const EngineM::vec3 &p1, const EngineM::vec3 &p2, const EngineM::vec3 &p3, const std::uint32_t color) {
        triangle(p1, p2, p3, color, framebuffer);
    }

    const Framebuffer& Renderer::getFramebuffer() const {
        return framebuffer;
    }
}
