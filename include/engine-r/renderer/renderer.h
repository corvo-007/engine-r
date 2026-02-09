#pragma once
#include "framebuffer.h"

#include "engine-m/vector/vector.h"

namespace EngineR {
    class Renderer {
        EngineM::vec3f camera;
        Framebuffer framebuffer;

    public:
        Renderer(int width, int height);

    private:
        [[nodiscard]] EngineM::vec3 transform(const EngineM::vec3f &p) const;
        [[nodiscard]] EngineM::vec3f perspective(const EngineM::vec3f &p) const;

    public:
        void setCamera(const EngineM::vec3f &camera);

        void setPoint(const EngineM::vec3f &p, std::uint32_t color);
        void drawLine(const EngineM::vec3f &p1, const EngineM::vec3f &p2, std::uint32_t color);
        void drawTriangle(const EngineM::vec3f &p1, const EngineM::vec3f &p2, const EngineM::vec3f &p3, std::uint32_t color);

        [[nodiscard]] const Framebuffer& getFramebuffer() const;
    };
}
