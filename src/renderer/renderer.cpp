#include "engine-r/renderer/renderer.h"

namespace EngineR {
    Renderer::Renderer(const int width, const int height) : framebuffer(width, height) {}

    const Framebuffer& Renderer::getFramebuffer() const {
        return framebuffer;
    }
}
