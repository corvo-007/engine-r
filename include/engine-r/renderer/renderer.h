#pragma once
#include "framebuffer.h"

namespace EngineR {
    class Renderer {
        Framebuffer framebuffer;

    public:
        Renderer(int width, int height);

        [[nodiscard]] const Framebuffer& getFramebuffer() const;
    };
}
