// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <iostream>
//
// #include "engine-r/window/window.h"

#include <SDL2/SDL.h>
#include <cstdint>

#include "engine-r/renderer/renderer.h"

constexpr std::uint32_t WHITE = 0xffffffff;
constexpr std::uint32_t RED = 0xff000000;
constexpr std::uint32_t GREEN = 0x00ff0000;
constexpr std::uint32_t BLUE = 0x0000ff00;
constexpr std::uint32_t YELLOW = 0xffff0000;

int main() {
    constexpr int WIDTH = 640, HEIGHT = 640;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Engine-R", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *fbTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    EngineR::Renderer renderer(WIDTH, HEIGHT);

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        EngineM::vec2 p1 = EngineM::vec2{7, 3} * 10;
        EngineM::vec2 p2 = EngineM::vec2{12, 37} * 10;
        EngineM::vec2 p3 = EngineM::vec2{62, 53} * 10;

        renderer.drawLine(p1, p2, BLUE);
        renderer.drawLine(p3, p2, GREEN);
        renderer.drawLine(p3, p1, YELLOW);
        renderer.drawLine(p1, p3, RED);

        const uint32_t *framebuffer = renderer.getFramebuffer().data();

        SDL_UpdateTexture(fbTexture, nullptr, framebuffer, WIDTH * sizeof(uint32_t));

        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer, fbTexture, nullptr, nullptr);
        SDL_RenderPresent(sdlRenderer);
    }

    SDL_DestroyTexture(fbTexture);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
