#include "Display.hpp"

Display::Display() {

}

void Display::init() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("chip8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64 * 10, 32 * 10, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetScale(renderer, 10.0, 10.0);
}

void Display::test() {
    SDL_RenderDrawPoint(renderer, 0, 0);
    SDL_RenderDrawPoint(renderer, 63, 31);
    SDL_RenderPresent(renderer);
}

void Display::teardown() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Display::drawPixelToBuffer(int x, int y) {
    std::pair<int, int> tempPair(x, y);
    points.push_back(tempPair);
}

void Display::renderBuffer() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (auto point : points) {
        SDL_RenderDrawPoint(renderer, point.first, point.second);    
    }
    SDL_RenderPresent(renderer);
}

void Display::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    points.clear();
}