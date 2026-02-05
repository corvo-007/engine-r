#pragma once
#include "framebuffer.h"

#include "engine-m/vector/vector2d.h"

namespace EngineR {
    class Renderer {
        Framebuffer framebuffer;

    public:
        Renderer(int width, int height);

        void setPoint(const EngineM::vec2 &p, std::uint32_t color);

        [[nodiscard]] const Framebuffer& getFramebuffer() const;
    };
}
