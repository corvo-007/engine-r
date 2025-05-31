#pragma once

#include <string>

namespace EngineR {
    class Window {
        std::string title;
        int width;
        int height;

    protected:
        Window(const std::string &title, int width, int height);

    public:
        static Window* create(const std::string& title, int width, int height);

        int getWidth() const;
        int getHeight() const;
        std::string getTitle() const;
        virtual void* getNativeWindow() const = 0;

        virtual ~Window() = default;
    };
}
