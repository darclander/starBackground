#include <iostream>
#include "headers/game.h"
#include "SDL2/SDL.h"

#define FPS 60
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
    game.init("Stars", 1600, 1200, true);


    while(true) {
        startingTick = SDL_GetTicks();
        game.clearRenderer();
        game.update();
        game.render();
    }




}