#pragma once

#include <iostream>


enum fileformat {MP4, GIF};

class ImgPlayer {

    public:
        ImgPlayer(fileformat f, const char filepath);

    private:
        fileformat file;

};