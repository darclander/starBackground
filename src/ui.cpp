#include "headers/ui.hpp"
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

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
void hello()
{
    std::cout << "Hello world, I'm a thread!" << std::endl;
}

int main(int argc, char* argv[])
{
    boost::thread thrd(&hello);
    thrd.join();
    return 0;
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

/**
 * Method to update the UI. Current use is to update the stars. This means that this method moves the stars forward.
 *
 * @param None
 * @return No return value.
 */

void thread() {
    std::cout << "test" << std::endl;
}

void UI::update() {
    // std::cout << &vect[0] << std::endl;
    // int counter = 0;
    for(std::vector<Star>::iterator it = vect.begin(); it != vect.end(); ++it) {
        it->update();
        it->draw();
        if (it->getX() > w) {
           // counter++;
            int size = rand() %  h + 1;
            it->move(0, size);
        }
    }



    // #pragma omp parallel for num_threads(4)
    // for(int i = 0; i < 300; i++) {
    //     std::cout << omp_get_thread_num() << std::endl;
    //     vect[i].update();
    //     vect[i].draw();
    //     if (vect[i].getX() > w) {
    //        // counter++;
    //         int size = rand() %  h + 1;
    //         vect[i].move(0, size);
    //     }
    // }


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
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
