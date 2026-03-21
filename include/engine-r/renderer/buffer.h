#pragma once
#include <vector>

#include "engine-r/color.h"

namespace EngineR {

    template <typename T>
    class Buffer {
        std::vector<T> buffer;
        int w;
        int h;

    public:
        Buffer(int w, int h): buffer(w * h), w(w), h(h) {

        }

        Buffer(int w, int h, T value): buffer(w * h, value), w(w), h(h) {

        }

        [[nodiscard]] T get(int x, int y) const {
            if (x < 0 || x >= w || y < 0 || y >= h) {
                return T{};
            }
            return buffer[x + (h - 1 - y) * w];
        }

        void set(int x, int y, T value) {
            if (x >= 0 && x < w && y >= 0 && y < h) {
                buffer[x + (h - 1 - y) * w] = value;
            }
        }

        void clear(const T &value) {
            std::fill(buffer.begin(), buffer.end(), value);
        }

        [[nodiscard]] int width() const {
            return w;
        }

        [[nodiscard]] int height() const {
            return h;
        }

        [[nodiscard]] const T* data() const {
            return buffer.data();
        }
    };
}
