#pragma once

#include <SDL2/SDL.h>
#include <vector>

class Display {
    public:
        Display();
        void init();
        void test();
        void teardown();
        void drawPixelToBuffer(int x, int y);
        void clear();
        void renderBuffer();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        std::vector<std::pair<int, int>> points;
};