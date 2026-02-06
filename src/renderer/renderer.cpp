#include "engine-r/renderer/renderer.h"

#include <cmath>

#include "engine-r/rasterizer/line.h"
#include "engine-r/rasterizer/triangle.h"

namespace EngineR {
    Renderer::Renderer(const int width, const int height) : framebuffer(width, height) {}

    void Renderer::setPoint(const EngineM::vec2 &p, const std::uint32_t color) {
        framebuffer.set(static_cast<int>(std::round(p.x)), static_cast<int>(std::round(p.y)), color);
    }

    void Renderer::drawLine(const EngineM::vec2 &p1, const EngineM::vec2 &p2, const std::uint32_t color) {
        line(p1, p2, color, framebuffer);
    }

    void Renderer::drawTriangle(const EngineM::vec2 &p1, const EngineM::vec2 &p2, const EngineM::vec2 &p3, const std::uint32_t color) {
        triangle(p1, p2, p3, color, framebuffer);
    }

    const Framebuffer& Renderer::getFramebuffer() const {
        return framebuffer;
    }
}
