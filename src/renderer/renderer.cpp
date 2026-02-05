#include "engine-r/renderer/renderer.h"

#include <cmath>

namespace EngineR {
    Renderer::Renderer(const int width, const int height) : framebuffer(width, height) {}

    void Renderer::setPoint(const EngineM::vec2 &p, const std::uint32_t color) {
        framebuffer.set(static_cast<int>(std::round(p.x)), framebuffer.height() - static_cast<int>(std::round(p.y)), color);
    }

    const Framebuffer& Renderer::getFramebuffer() const {
        return framebuffer;
    }
}
