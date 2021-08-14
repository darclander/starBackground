#pragma once

#include <iostream>
#include "SDL2/SDL.h"

class Star {

    public:
        Star();
        Star(SDL_Renderer *r, int x, int y, int speed, int size);

        void update(double dt);
        void draw();

        int getX();
        void move(int x, int y);

    private:
        double speed;
        
        SDL_Renderer *renderer;
        SDL_Rect starRect;

};