#pragma once

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"



class Game {

    public:
        Game();


        int init(const char *title, int w, int h, bool fullscreen);

        void update();
        void render();
        void clearRenderer();
        void clean();

    private: 
        SDL_Renderer *renderer;
        SDL_Window *window;
        SDL_Event event;

};