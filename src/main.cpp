#include <iostream>
#include <stdlib.h>
#include "headers/ui.h"
#include "SDL2/SDL.h"

#define FPS 30
#define frameDelay = 1000 / FPS

void fpsCap(Uint32 starting_tick) {
    if ((1000 / FPS) > SDL_GetTicks() - starting_tick) {
        SDL_Delay(1000 / FPS - (SDL_GetTicks() - starting_tick));
    }
}

int main(int argc, char *argv[]) {

    // Ticks for fpsCap
    uint32_t startingTick;
    int endTick;

    UI ui = UI();

    if (argc == 1) {
        ui.init("Stars", 1920, 1080, 300, false);
    } else if (argc == 4) {
        ui.init("Stars", atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), false);
    } else {
        std::cout << "INVALID ARGUMENT, INPUT IS: \nWIDTH(px) HEIGHT(px) STARS(amount)" << std::endl;
        return -1;
    }

 

    SDL_Event event;
    bool isRunning = true;
    while(isRunning) {
        startingTick = SDL_GetTicks();
        
        // SDL_PollEvent(&event);
        // switch (event.type) {
        //     case SDL_QUIT : 
        //         isRunning = false;
        //         break;
        //     default:
        //         break;
        // }

        ui.clearRenderer();
        ui.update();
        ui.render();

        fpsCap(startingTick);
    }


    ui.clean();

    return 0;
}