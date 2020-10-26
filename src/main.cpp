#include <iostream>
#include "headers/game.h"
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

    Game game = Game();
    game.init("Stars", 30000, 1080, false);

    SDL_Event event;
    bool isRunning = true;
    while(isRunning) {
        startingTick = SDL_GetTicks();
        
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT : 
                isRunning = false;
                break;
            default:
                break;
        }

        game.clearRenderer();
        game.update();
        game.render();

        fpsCap(startingTick);
    }


    game.clean();

    return 0;
}