#include "headers/star.hpp"

Star::Star() {
    
}

Star::Star(SDL_Renderer *r, int x, int y, int speed, int size) {
    this->speed = speed;
    starRect.w = size = starRect.h = size;
    starRect.x = x; 
    starRect.y = y;
    renderer = r;
}

void Star::draw() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &starRect);
    SDL_RenderFillRect(renderer, &starRect);
}

void Star::update() {
    starRect.x += speed;
}

/**
 * Get X position :)
 *
 * @param None
 * @return The X position of star.
 */
int Star::getX() {
    return starRect.x;
}

void Star::move(int x, int y) {
    starRect.x = x;
    starRect.y = y;
}