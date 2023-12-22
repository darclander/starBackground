#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include "headers/ui.hpp"
#include "SDL2/SDL.h"

#ifdef _WIN32
   #include <io.h> 
   #define access    _access
#else
   #include <unistd.h>
#endif

extern "C" {
    #include "libavformat/avformat.h"
    #include "libavcodec/avcodec.h"
    #include "libswscale/swscale.h"
}

#define FPS 30
#define frameDelay = 1000 / FPS

/**
 * Limits update frequency rate. Bad implementation since it creates flickering due to
 * not basing updating on a time but to wait for X.
 *
 * @param starting_tick The tick which is retrieved every while-loop.
 * @return No return value.
 */
void fpsCap(Uint32 starting_tick) {
    // '1000 / FPS' is meant to be replaced with 'frameDelay'
    if ((1000 / FPS) > SDL_GetTicks() - starting_tick) {
        SDL_Delay(1000 / FPS - (SDL_GetTicks() - starting_tick));
    }
}

/**
 * Examines if a file exists. Support has been added for both linux and windows
 * in case of cross-platform-development.
 *
 * @param None
 * @return Returns true if file could be accessed, false otherwise.
 */
bool fileExists(const std::string &filePath) {
    return access( filePath.c_str(), 0 ) == 0;
}

int main(int argc, char **argv) {
    avformat_network_init();
    // Ticks for fpsCap
    uint32_t startingTick;
    int endTick;

    UI ui = UI();

    const std::vector<std::string> args(argv+1, argv + argc);

    int width = 1920; // "Default" value for width.
    int height = 1080; // "Default" value for height.
    int stars = 300;

    bool video = false;
    std::string filePath = "";

    for(auto it = args.begin(), end = args.end(); it != end; ++it) {
        if (*it == "-h" || *it == "--height") {
            height = std::stoi(*(it + 1));
        } else if (*it == "-w" || *it == "--width"){
            width = std::stoi(*(it + 1));
        } else if (*it == "--stars"){
            stars = std::stoi(*(it + 1));
        } else if (*it == "--video") {
            video = true;
            filePath = *(it + 1);
        }
    }

    if(video && !fileExists(filePath)) {
        std::cout << "Could not find file!" << std::endl;
        return 1;
    }

    if (argc == 1 && !video) {
        ui.init("Stars", 1920, 1080, 300, false);
    } else if (video) {
        ui.init("Stars", width, height, filePath, false);
    } else {
        ui.init("Stars", width, height, stars, false);
    }


    SDL_Event event;
    bool isRunning = true;
    while(isRunning) {
        // Get the number of milliseconds since the SDL library initialization.
        startingTick = SDL_GetTicks();
        

        // --- USE THIS WHEN: You have an application window and want to be able to close it.
        
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT : 
                isRunning = false;
                break;
            default:
                break;
        }

        ui.clearRenderer();
        ui.update();
        ui.render();

        // See method-description
        fpsCap(startingTick);
    }


    ui.clean();

    return 0;
}


// Could implement this?
/*
@  https://www.reddit.com/user/larso0/

Let me give you an example:

float time_seconds = SDL_GetTicks() / 1000.f;
while(1){
    float new_time = SDL_GetTicks() / 1000.f;
    float delta = new_time - time_seconds;
    time_seconds = new_time;
    updateGamePhysics(delta);
    SDL_RenderClear(renderer);
    renderGamebjects();
    SDL_RenderPresent(renderer); //Will wait here
}

So the game loop won't continue to the next iteration before SDL_RenderPresent is done presenting. 
So if VSync is enabled, SDL_RenderPresent will wait the correct amount of time for the framerate 
to stay at the monitors refreshrate. So what I recommend using the delta variable for is 
calculating the physics of your game. so if you have an object that should move on the x axis, 
instead of calculating it like x += xPerFrame; you should do x += delta*xSpeedPerSecond. 
That way your objects will move at the same rate, no matter what the frame rate is.

*/