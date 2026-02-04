#include "engine-r/window/linuxWindow.h"

#include <stdexcept>

namespace EngineR {
    bool LinuxWindow::glfwInitialized = false;
    int LinuxWindow::glfwWindowCount = 0;

    LinuxWindow::LinuxWindow(const std::string &title, int width, int height): Window(title, width, height) {
        if (!glfwInitialized) {
            if (!glfwInit()) {
                throw std::runtime_error("Failed to initialize GLFW");
            }
            glfwInitialized = true;
        }

        glfwWindowCount++;
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    }

    void* LinuxWindow::getNativeWindow() const {
        return window;
    }

    LinuxWindow::~LinuxWindow() {
        if (window) {
            glfwDestroyWindow(window);
        }
        if (--glfwWindowCount == 0) {
            glfwTerminate();
        }
    }
}
