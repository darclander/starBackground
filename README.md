# starBackground

This project is a very basic implementation of a wallpaper engine and is currently in development. The only current functionality is to make a star looking animation which can be seen below or to *load* your own video files (see more details below).

![Alt text](documents/screenshots/bg.gif?raw=true "Gif")

[This youtube video](https://www.youtube.com/watch?v=vhugQU01Dso) will go through how it works and what the next steps are (currently a bit outdated).

The project is made in C++ using SDL2 and ffmpeg.

People who want to contribute can now also make edits to the [ideas file](https://github.com/darclander/starBackground/blob/main/documents/new_ideas.txt) if they have any ideas for updates or open an [issue](https://github.com/darclander/starBackground/issues)

# Usage
Assuming all required DLLs are available the program now has updated functionality. You can run the program with default settings or by additional command lines (UI and monitor "detection" is still in progress). 

`-w, --width`: specifies the width of the window. default is 1920 \
`-h, --height`: specifies the height of the window. default is 1080 \
`--stars`: specifies the number of stars. default is 300 \
`--mp4`: specfies file path to a video file. (**NOTE:** if video is used this overrides the "star" setting). 

Example: 
`./starBG.exe -w 1920 -h 1080 --mp4 ./video.mp4` \
`./starBG.exe -w 1920 -h 1080 --stars 1000` \
`./starBG.exe` 

# Compilation
To simplify development on windows, [MSYS2](https://www.msys2.org/) has been used in order to compile this project. The following are required:
- [MSYS2](https://www.msys2.org/)
- [MinGW64](https://www.mingw-w64.org/) `pacman -S mingw-w64-x86_64-toolchain`
- [SDL2](https://www.libsdl.org/) `pacman -S mingw-w64-x86_64-SDL2` (`pacman -S mingw-w64-x86_64-SDL2_image`)
- [FFMPEG](https://www.ffmpeg.org/) `pacman -S mingw-w64-x86_64-ffmpeg`
- [make](https://packages.msys2.org/package/make) `pacman -S make`

When all dependencies have been installed, run `make` in the root folder. The executable should then be in the `debug` folder. I have not yet found required DLLs so make sure that the mingw64 bin folder is part of your environment path.

<!--- ***OUTDATED***
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
--->
