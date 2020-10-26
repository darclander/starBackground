#include <iostream> 
#include <windows.h>

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
    {
    HWND p = FindWindowEx(hwnd, NULL, "SHELLDLL_DefView", NULL);
    HWND* ret = (HWND*)lParam;

    if (p)
        {
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

int main() {
    std::cout << get_wallpaper_window();
    return 0;
}
