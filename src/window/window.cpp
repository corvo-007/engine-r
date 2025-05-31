#include "engine-r/window/window.h"
#include "engine-r/window/linuxWindow.h"

namespace EngineR {
    Window::Window(const std::string &title, const int width, const int height): title(title), width(width), height(height) {

    }

    std::string Window::getTitle() const {
        return title;
    }

    int Window::getWidth() const {
        return width;
    }

    int Window::getHeight() const {
        return height;
    }

    Window* Window::create(const std::string &title, int width, int height) {
#if defined(__linux__)
        return new LinuxWindow(title, width, height);
#endif
    }

}
