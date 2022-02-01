#pragma once

#include <iostream>
#include "SDL.h"

class Star {

    public:
        Star();
        Star(SDL_Renderer *r, int x, int y, int speed, int size);

        void update();
        void draw();

        int getX();
        void move(int x, int y);

    private:
        int speed;
        
        SDL_Renderer *renderer;
        SDL_Rect starRect;

};