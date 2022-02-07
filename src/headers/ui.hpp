#pragma once

#include <iostream>
#include <vector>
#include <time.h>
#include <windows.h>
#include <omp.h>
// #include <future> 
// #include <pthread.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"


#include "star.hpp"
// #include "parallel.hpp"




class UI {

    public:
        UI();


        int init(const char *title, int w, int h, int stars, bool fullscreen);

        void update();
        void render();
        void clearRenderer();
        void clean();

        struct thread_info {
            std::vector<Star> v;
            int i;
        };

    private: 
        SDL_Renderer *renderer;
        SDL_Window *window;
        SDL_Event event;

        std::vector<Star> vect; // to add projectiles

        int w, h;



};