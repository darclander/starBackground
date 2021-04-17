#include "imgplayer.h"

// Constructor: Take a list of (SDL) images and copy it to a local list
// to avoid performance drops hopefully (only do it once).
ImgPlayer::ImgPlayer(SDL_Renderer *r) {

    renderer = r;
    rImg.x = rImg.y = rImg.w = rImg.h = 100;

    SDL_Surface *tempSurface = IMG_Load("./duk.png");

    if (!tempSurface) {
        std::cout << "Failed to load picture: " << IMG_GetError();
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(r, tempSurface);
	SDL_FreeSurface(tempSurface);

    textures[0] = tex;
    


}


// No destructor needed since no pointer types yet?

// Draw function, should be simple enough: Draw the current image in the 
// list of images. 
void ImgPlayer::draw() {
    SDL_RenderCopyEx(renderer, textures[index], NULL, &rImg, degrees, NULL, SDL_FLIP_NONE);
}

// Update function, should update the image / texture to the next one in the list 
// based on a given interval. FPS etc might not match the given ones in main.cpp
void ImgPlayer::update() {
    
    // Add delay before or after?

    // Update position of index in list.

    
}