#include "headers/ui.hpp"


// https://stackoverflow.com/questions/56132584/draw-on-windows-10-wallpaper-in-c
// http://www.cplusplus.com/forum/windows/95608/

/**
 * An application-defined callback function used with the EnumWindows or EnumDesktopWindows function. 
 * It receives top-level window handles. The WNDENUMPROC type defines a pointer to this callback function. 
 * EnumWindowsProc is a placeholder for the application-defined function name.
 *
 * @param HWND - A handle to a top-level window. @param LPARAM - The application-defined value given in EnumWindows() or EnumDesktopWindows().
 * @return To continue enumeration, the callback function must return TRUE; to stop enumeration, it must return FALSE.
 */
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    HWND p = FindWindowEx(hwnd, NULL, "SHELLDLL_DefView", NULL);
    HWND* ret = (HWND*)lParam;

    if (p) {
        // Gets the WorkerW Window after the current one.
        *ret = FindWindowEx(NULL, hwnd, "WorkerW", NULL);
    }
    return true;
}

/**
 * Method used to retrieve a 'HWND' to the current wallpaper window (in windows). Currently there is an issue for some windows
 * installations. For more information look at: https://github.com/darclander/starBackground/issues/7
 * 
 * @param None
 * @return Returns a `HWND` to the wallpaper window.
 */
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

// Has no current functionality... Replace init with this?
/**
 * Creates the UI, initialization is in UI::init
 *
 * @param None
 * @return None
 */
UI::UI() {

}

// Used a bit like a constructor, could maybe place everything in the constructor to maintain
// Object-Oriented programming.
/**
 * Method to initialize the UI. This is what will run in the background instead of the 'normal' windows background.
 * 
 * @param title name of the window @param w width of the window @param h height of the window @param stars amount of stars 
 * @param fullscreen a boolean for fullscreen or not
 * @return No return value.
 */
int UI::init(const char *title, int w, int h, int stars, bool fullscreen) {
    int flags = 0;
    this->w = w;
    this->h = h;

    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
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

/**
 * Initializes the UI, TODO: could be moved to UI::UI()...?
 * 
 * @param title `const char *` name of the window @param w width of the window @param h height of the window 
 * @param filePath `std::string&` for video to be played @param fullscreen `bool` for fullscreen or not
 * @return No return value.
 */
int UI::init(const char *title, int w, int h, std::string &filePath, bool fullscreen) {
    int flags = 0;
    video = true;
    this->w = w;
    this->h = h;

    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        // window = SDL_CreateWindow(
        //                             title,
        //                             SDL_WINDOWPOS_CENTERED,
        //                             SDL_WINDOWPOS_CENTERED,
        //                             w,
        //                             h,
        //                             flags
        // );
        window = SDL_CreateWindowFrom((void*)get_wallpaper_window());
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if(renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
    }

    vp = new videoPlayer(renderer, filePath);
    vp->decodeVideo();

    return 0;
}


/**
 * Method to update the UI. Current use is to update the stars. This means that this method moves the stars forward.
 *
 * @param None
 * @return No return value.
 */
void UI::update() {
    if (video) {
        vp->update();
    } else {
        int counter = 0;
        for(std::vector<Star>::iterator it = vect.begin(); it != vect.end(); ++it) {
            it->update();
            it->draw();
            if (it->getX() > w) {
            // counter++;
                int size = rand() %  h + 1;
                it->move(0, size);
            }
        }
    }

}

/**
 * Renders the UI.
 *
 * @param None
 * @return No return value.
 */
void UI::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}

/**
 * Clears the renderer.
 *
 * @param None
 * @return No return value.
 */
void UI::clearRenderer() {
    SDL_RenderClear(renderer);
}

/**
 * This method destroys the window and renderer in order to prevent memory leaks.
 *
 * @param None
 * @return No return value.
 */
void UI::clean() {
    delete vp;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
