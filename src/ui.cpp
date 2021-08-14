#include "headers/ui.h"


// https://stackoverflow.com/questions/56132584/draw-on-windows-10-wallpaper-in-c
// http://www.cplusplus.com/forum/windows/95608/

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    HWND p = FindWindowEx(hwnd, NULL, "SHELLDLL_DefView", NULL);
    HWND* ret = (HWND*)lParam;

    if (p) {
        // Gets the WorkerW Window after the current one.
        *ret = FindWindowEx(NULL, hwnd, "WorkerW", NULL);
        }
    return true;
}

HWND get_wallpaper_window() {
        // Fetch the Progman window
        HWND progman = FindWindow("ProgMan", NULL);
        // Send 0x052C to Progman. This message directs Progman to spawn a 
        // WorkerW behind the desktop icons. If it is already there, nothing 
        // happens.
        SendMessageTimeout(progman, 0x052C, 0, 0, SMTO_NORMAL, 1000, nullptr);
        // We enumerate all Windows, until we find one, that has the SHELLDLL_DefView 
        // as a child. 
        // If we found that window, we take its next sibling and assign it to workerw.
        HWND wallpaper_hwnd = nullptr;
        EnumWindows(EnumWindowsProc, (LPARAM)&wallpaper_hwnd);
        // Return the handle you're looking for.
        return wallpaper_hwnd;
}

// Has no current function.
UI::UI() {

}

// Used a bit like a constructor, could maybe place everything in the constructor to maintain
// Object-Oriented programming.
int UI::init(const char *title, int w, int h, int stars, bool fullscreen) {
    int flags = 0;
    this->w = w;
    this->h = h;

    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        // window = SDL_CreateWindow(
        //                             title,
        //                             SDL_WINDOWPOS_CENTERED,
        //                             SDL_WINDOWPOS_CENTERED,
        //                             w,
        //                             h,
        //                             flags
        // );
        window = SDL_CreateWindowFrom((void*)get_wallpaper_window());
        renderer = SDL_CreateRenderer(window, -1, 0);

        if(renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
    }

    srand (time(NULL));
    std::cout << stars << std::endl;
    for (int i = 0; i < stars; i++) {
        int size = rand() %  3 + 1;
        vect.push_back(Star(renderer, rand() %  w + 1, rand() %  h + 1, size, size));
    }

    return 0;
}

void UI::update(double dt) {
    int counter = 0;
    for(std::vector<Star>::iterator it = vect.begin(); it != vect.end(); ++it) {
        it->update(dt);
        it->draw();
        if (it->getX() > w) {
           // counter++;
            int size = rand() %  h + 1;
            it->move(0, size);
        }
    }

}

void UI::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}

void UI::clearRenderer() {
    SDL_RenderClear(renderer);
}

void UI::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
