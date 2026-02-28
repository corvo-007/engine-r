#include "engine-r/renderer/renderer.h"

#include <cmath>
#include <stdexcept>

#include "engine-r/rasterizer/line.h"
#include "engine-r/rasterizer/triangle.h"

namespace EngineR {
    Camera::Camera(EngineM::vec3d position, EngineM::vec3d target, EngineM::vec3d up): position(position), target(target), up(up) {}

    Renderer::Renderer(const int width, const int height) : framebuffer(width, height) {
        setViewport(0, 0, width, height);
    }

    void Renderer::calculateModelViewMatrix() {
        EngineM::vec3d n = (camera.position - camera.target).normalise();
        EngineM::vec3d l = (camera.up ^ n).normalise();
        EngineM::vec3d m = (n ^ l).normalise();

        modelViewMatrix = EngineM::mat4d{{l.x, l.y, l.z, 0, m.x, m.y, m.z, 0, n.x, n.y, n.z, 0, 0, 0, 0, 1}} * EngineM::mat4d{{1, 0, 0, -camera.target.x, 0, 1, 0, -camera.target.y, 0, 0, 1, -camera.target.z, 0, 0, 0, 1}};
        normalMatrix = EngineM::mat3d{{l.x, l.y, l.z, m.x, m.y, m.z, n.x, n.y, n.z}};
        normalMatrix.inverse();
        normalMatrix.transpose();
    }

    void Renderer::calculatePerspectiveMatrix() {
        const double f = (camera.position - camera.target).magnitude();
        perspectiveMatrix = EngineM::mat4d{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, -1 / f, 1};
    }

    EngineM::vec3d Renderer::transform(const EngineM::vec3d &p) const {
        EngineM::vec4d t = perspectiveMatrix * modelViewMatrix * EngineM::vec4d{p, 1.0};
        t /= t.w;

        t = viewportMatrix * t;

        return t.xyz();
    }

    void Renderer::addObject(const Object &object) {
        objects.push_back(object);
    }

    void Renderer::lookAt(const EngineM::vec3d &position, const EngineM::vec3d &target, const EngineM::vec3d &up) {
        camera.position = position;
        camera.target = target;
        camera.up = up;

        calculateModelViewMatrix();
        calculatePerspectiveMatrix();
    }

    void Renderer::setViewport(const int x, const int y, const int w, const int h) {
        viewportMatrix = EngineM::mat4d({w / 2., 0, 0, x + w / 2., 0, h / 2., 0, y + h / 2., 0, 0, 1, 0, 0, 0, 0, 1});
    }

    void Renderer::setPoint(const EngineM::vec3d &p, const Color color) {
        const auto t = transform(p);
        framebuffer.set(t.x, t.y, color);
    }

    void Renderer::drawLine(const EngineM::vec3d &p1, const EngineM::vec3d &p2, const Color color) {
        const auto t1 = transform(p1);
        const auto t2 = transform(p2);

        const EngineM::vec3 t3 = {static_cast<int>(t1.x), static_cast<int>(t1.y), static_cast<int>(t1.z)};
        const EngineM::vec3 t4 = {static_cast<int>(t2.x), static_cast<int>(t2.y), static_cast<int>(t2.z)};
        line(t3, t4, color, framebuffer);
    }

    void Renderer::drawTriangle(const Face &face, Shader *shader, const ShaderUniforms &uniforms) {
        VShaderOutput output[3];

        for (int i = 0; i < 3; i++) {
            VShaderInput input(face.normals[i], face.uv_coords[i]);
            output[i] = shader -> vertex(face.vertices[i], input, uniforms);
        }

        triangle(output, shader, uniforms, viewportMatrix, framebuffer);
    }

    void Renderer::render() {
        for (Object &object : objects) {
            if (!object.shader) {
                throw std::runtime_error("Renderer::render() called when no shader is set");
            }
            ShaderUniforms uniforms(modelViewMatrix, perspectiveMatrix, normalMatrix, object.get_normal_map(), object.get_diffuse_map(), object.get_specular_map());
            for (int i = 0; i < object.n_faces(); i++) {
                Face f = object.face(i);

                drawTriangle(f, object.shader, uniforms);
            }
        }
    }

    const EngineM::mat4d& Renderer::getModelView() const {
        return modelViewMatrix;
    }

    const Framebuffer& Renderer::getFramebuffer() const {
        return framebuffer;
    }
}
