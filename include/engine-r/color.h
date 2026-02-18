#pragma once
#include <cstdint>

namespace EngineR {
    struct Color {
        union {
            uint8_t rgba[4];
            struct {
                uint8_t a, b, g, r;
            };
        };

        Color(): rgba{0, 0, 0, 0} {}

        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a): a(a), b(b), g(g), r(r) {}
    };
}
