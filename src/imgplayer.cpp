#include "imgplayer.hpp"

ImgPlayer::ImgPlayer(fileformat f, const char filepath) {
    file = f;

    switch(file) {
        case MP4:

            /*
             * In case of MP4 file, do THIS 
             */ 

            break;
        case GIF:

            /*
             * In case of GIF file, do THIS
             */ 

            break;
    }

}

// // #include "imgplayer.h"

// // Constructor: Take a list of (SDL) images and copy it to a local list
// // to avoid performance drops hopefully (only do it once).
// ImgPlayer::ImgPlayer() {


// }


// // No destructor needed since no pointer types yet?

// // Draw function, should be simple enough: Draw the current image in the 
// // list of immages. 
// void ImgPlayer::draw() {
//     SDL_RenderCopyEx(renderer, texture, NULL, &rImg, degrees, NULL, SDL_FLIP_NONE);
// }

// // Update function, should update the image / texture to the next one in the list 
// // based on a given interval. FPS etc might not match the given ones in main.cpp
// void ImgPlayer::update() {
    
//     // Add delay before or after?

//     // Update position of index in list.

    
// }