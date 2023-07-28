#include <iostream>
#include <vector>
#include <time.h>
#include <windows.h>
#include <thread>
#include <atomic>

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_video.h>

extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavutil/imgutils.h>
    #include <libswscale/swscale.h>
}

class videoPlayer {

    public:
        videoPlayer(SDL_Renderer *r, const std::string &filePath);
        ~videoPlayer();

        void update();


    private:

        void player();

        AVFrame* frame;
        AVPacket packet;
        AVCodecContext* codecContext;
        AVFormatContext* formatContext = nullptr;
        const AVCodec* videoCodec = nullptr;
        AVCodecParameters* codecParameters = nullptr;
        int videoStreamIndex = -1;
        SDL_Texture* texture;
        SDL_Renderer *renderer;
        SDL_Event event;

        bool isPlaying = true;

        const int targetFrameRate = 30; // Adjust this value to set the desired frame rate (e.g., 30 FPS)
        const int frameDelay = 1000 / targetFrameRate;


};