#pragma once

#include <GLFW/glfw3.h>
#include "engine-r/window/window.h"

namespace EngineR {
    class LinuxWindow : public Window {
        GLFWwindow *window;

    public:
        static bool glfwInitialized;
        static int glfwWindowCount;

        LinuxWindow(const std::string &title, int width, int height);

        [[nodiscard]] void* getNativeWindow() const override;

        ~LinuxWindow() override;
    };
}