#pragma once
#include "framebuffer.h"

#include "engine-m/vector/vector2d.h"
#include "engine-m/vector/vector3d.h"

namespace EngineR {
    class Renderer {
        Framebuffer framebuffer;

    public:
        Renderer(int width, int height);

        [[nodiscard]] EngineM::vec3 transform(const EngineM::vec3f &p) const;

        void setPoint(const EngineM::vec2 &p, std::uint32_t color);
        void drawLine(const EngineM::vec2 &p1, const EngineM::vec2 &p2, std::uint32_t color);
        void drawTriangle(const EngineM::vec3 &p1, const EngineM::vec3 &p2, const EngineM::vec3 &p3, std::uint32_t color);

        [[nodiscard]] const Framebuffer& getFramebuffer() const;
    };
}
