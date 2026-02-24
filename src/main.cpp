// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <iostream>
//
// #include "engine-r/window/window.h"

#include <SDL2/SDL.h>
#include <cstdint>
#include <random>

#include "engine-r/renderer/object.h"
#include "engine-r/reader/objectreader.h"
#include "engine-r/renderer/renderer.h"
#include "engine-r/shaders/phong.h"
#include "engine-r/shaders/shader.h"

constexpr std::uint32_t WHITE = 0xffffffff;
constexpr std::uint32_t RED = 0xff000000;
constexpr std::uint32_t GREEN = 0x00ff0000;
constexpr std::uint32_t BLUE = 0x0000ff00;
constexpr std::uint32_t YELLOW = 0xffff0000;

std::vector<std::uint32_t> generate_random_numbers(size_t n, int start, int end) {
    std::vector<std::uint32_t> numbers;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::uint32_t> dist(start, end);

    for (int i = 0; i < n; i++) {
        numbers.push_back(dist(gen));
    }

    return numbers;
}

int main() {
    constexpr int WIDTH = 1080, HEIGHT = 1080;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Engine-R", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *fbTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    EngineR::Object object = EngineR::ObjectReader::read_object("/home/corvo/code/engine-r/obj/diablo3_pose/diablo3_pose.obj");

    EngineR::Renderer renderer(WIDTH, HEIGHT);
    renderer.lookAt({0, 0, 2}, {0, 0, 0}, {0, 1, 0});

    EngineM::vec4d l = renderer.getModelView() * EngineM::vec4d{1, 1, 1, 1};

    object.shader = new EngineR::PhongShader(l.xyz(), 64);

    renderer.addObject(object);

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        renderer.render();

        const uint32_t *framebuffer = renderer.getFramebuffer().data();

        SDL_UpdateTexture(fbTexture, nullptr, framebuffer, WIDTH * sizeof(uint32_t));

        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer, fbTexture, nullptr, nullptr);
        SDL_RenderPresent(sdlRenderer);
    }

    delete object.shader;

    SDL_DestroyTexture(fbTexture);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
