#pragma once

#include "engine-r/color.h"
#include "framebuffer.h"
#include "object.h"
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
        EngineM::mat4d modelViewMatrix;
        EngineM::mat4d perspectiveMatrix;
        EngineM::mat4d viewportMatrix;
        EngineM::mat3d normalMatrix;
        Camera camera;

        Framebuffer framebuffer;

        std::vector<Object> objects;

    public:
        Renderer(int width, int height);

    private:
        void calculateModelViewMatrix();
        void calculatePerspectiveMatrix();

        [[nodiscard]] EngineM::vec3d transform(const EngineM::vec3d &p) const;

    public:
        void addObject(const Object &object);

        void lookAt(const EngineM::vec3d &position, const EngineM::vec3d &target, const EngineM::vec3d &up);
        void setViewport(int x, int y, int w, int h);

        void setPoint(const EngineM::vec3d &p, Color color);
        void drawLine(const EngineM::vec3d &p1, const EngineM::vec3d &p2, Color color);
        void drawTriangle(const Face &face, Shader *shader);

        void render();

        [[nodiscard]] const EngineM::mat4d& getModelView() const;

        [[nodiscard]] const Framebuffer& getFramebuffer() const;
    };
}
