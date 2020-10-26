#pragma once

#include <iostream>
#include "SDL2/SDL.h"

class Star {

    public:
        Star(SDL_Renderer *r, int x, int y, float speed, int size);

        void update();
        void draw();

        int getX();

    private:
        float speed;
        
        SDL_Renderer *renderer;
        SDL_Rect starRect;

};