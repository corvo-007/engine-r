#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "engine-r/window/window.h"

int main() {
    const EngineR::Window *window = EngineR::Window::create("test", 800, 600);
    auto *glfwWindow = static_cast<GLFWwindow *>(window->getNativeWindow());

    glfwMakeContextCurrent(glfwWindow);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    while (!glfwWindowShouldClose(glfwWindow)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(0.0f,  0.5f);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    delete window;
    return 0;
}
