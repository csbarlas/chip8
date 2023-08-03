#pragma once

#include <SDL2/SDL.h>

class Display {
    public:
        Display();
        void init();
        void test();
        void teardown();
        void drawPixel(int x, int y);
        void clear();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};