#pragma once

#include <iostream>
#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_Image.h"

class ImgPlayer {


    public:
        ImgPlayer(SDL_Renderer *r);
        void draw();
        void update();

    private:
        int degrees = 0;
        int index = 0;
        
        SDL_Rect rImg;
        SDL_Renderer *renderer;
        SDL_Texture *textures[10]; // Amount of pictures? Maybe array is a bad idea

};