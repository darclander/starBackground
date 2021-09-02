# starBackground

This project is a very basic implementation of a wallpaper engine and is currently in production. The only current function is to make a star looking animation which can be seen below.

![Alt text](documents/screenshots/bg.gif?raw=true "Gif")

[This youtube video](https://www.youtube.com/watch?v=vhugQU01Dso) will go through how it works and what the next steps are.

The project is made in C++ and SDL.

People who want to contribute can now also make edits to the [ideas file](https://github.com/darclander/starBackground/blob/main/documents/new_ideas.txt) if they have any ideas for updates.

# Installation for 64-bit windows

This project is based on [SDL2](https://www.libsdl.org/index.php) + [MinGW](http://mingw-w64.org/doku.php) and therefore requires the following: 
- [MinGW](https://sourceforge.net/projects/mingw/) 
- [SDL2](https://www.libsdl.org/release/SDL2-devel-2.0.14-mingw.tar.gz)

**Libs for future development, not needed for normal compilation**
- [SDL Image](https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-mingw.tar.gz)

When MinGW is installed, make sure to install the mingw32-make package. If you can run `mingw32-make` in your terminal, extract from the SDL image zip the map called i686-w64-mingw32 to a place of your choice. After you have extracted the map, open the SDL 2 zip and merge the contents of the i686-w64-mingw32 (4 folders) from that zip with the folders in your first i686-w64-mingw32 folder. If you open the makefile you can see that I am linking the include and lib folder to my `D:\programming`. Change that path to wherever you extracted the i686-w64-mingw32 folder. Comments should exist in the makefile.

![Alt text](documents/screenshots/makefile1.png?raw=true "Makefile1")

When everything is setup you should be able to run `mingw32-make` in the root folder and after compilation you can run starbg.exe in the debug folder.
**NOTE:** You may require `SDL2.dll` and `SDL2_image.dll`. Those can be found in your `SDL\i686-w64-mingw32\bin` folder. 
