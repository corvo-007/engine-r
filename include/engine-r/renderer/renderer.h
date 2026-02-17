#pragma once
#include "framebuffer.h"
#include "engine-r/shaders/shader.h"
#include "engine-m/matrix/matrix.h"

#include "engine-m/vector/vector.h"

namespace EngineR {
    struct Camera {
        EngineM::vec3d position;
        EngineM::vec3d target;
        EngineM::vec3d up;

        Camera() = default;
        Camera(EngineM::vec3d position, EngineM::vec3d target, EngineM::vec3d up);
    };

    class Renderer {
        Framebuffer framebuffer;

        Camera camera;
        EngineM::mat4d modelViewMatrix;
        EngineM::mat4d perspectiveMatrix;
        EngineM::mat4d viewportMatrix;
        EngineM::mat4d mvp;

    public:
        Renderer(int width, int height);

    private:
        void calculateModelViewMatrix();
        void calculatePerspectiveMatrix();

        [[nodiscard]] EngineM::vec3d transform(const EngineM::vec3d &p) const;

    public:
        void lookAt(const EngineM::vec3d &position, const EngineM::vec3d &target, const EngineM::vec3d &up);
        void setViewport(int x, int y, int w, int h);

        void setPoint(const EngineM::vec3d &p, std::uint32_t color);
        void drawLine(const EngineM::vec3d &p1, const EngineM::vec3d &p2, std::uint32_t color);
        void drawTriangle(const EngineM::vec3d &p1, const EngineM::vec3d &p2, const EngineM::vec3d &p3, Shader *shader);

        [[nodiscard]] const Framebuffer& getFramebuffer() const;
    };
}
