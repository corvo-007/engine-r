// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <iostream>
//
// #include "engine-r/window/window.h"

#include <SDL2/SDL.h>
#include <cstdint>

#include "engine-r/renderer/renderer.h"

int main() {
    constexpr int WIDTH = 800, HEIGHT = 600;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "Engine-R",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        0
    );

    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    SDL_Texture *fbTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    EngineR::Renderer renderer(WIDTH, HEIGHT);

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

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
