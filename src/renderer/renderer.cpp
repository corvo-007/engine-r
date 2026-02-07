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

    EngineM::vec3f Renderer::perspective(const EngineM::vec3f &p) const {
        return p / (1 - p.z / camera.z);
    }

    void Renderer::setCamera(const EngineM::vec3f &camera) {
        this -> camera = camera;
    }

    void Renderer::setPoint(const EngineM::vec3f &p, const std::uint32_t color) {
        const auto t = transform(p);
        framebuffer.set(t.x, t.y, color);
    }

    void Renderer::drawLine(const EngineM::vec3f &p1, const EngineM::vec3f &p2, const std::uint32_t color) {
        const auto t1 = transform(p1);
        const auto t2 = transform(p2);
        line(t1, t2, color, framebuffer);
    }

    void Renderer::drawTriangle(const EngineM::vec3f &p1, const EngineM::vec3f &p2, const EngineM::vec3f &p3, const std::uint32_t color) {
        const auto t1 = transform(perspective(p1));
        const auto t2 = transform(perspective(p2));
        const auto t3 = transform(perspective(p3));

        triangle(t1, t2, t3, color, framebuffer);
    }

    const Framebuffer& Renderer::getFramebuffer() const {
        return framebuffer;
    }
}
