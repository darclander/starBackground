#include <iostream>
#include <vector>
#include <time.h>
#include <windows.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_video.h>


extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavutil/imgutils.h>
    #include <libswscale/swscale.h>
}

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

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        // Handle initialization error
        return 1;
    }

    // Initialize FFmpeg

    avformat_network_init();

    AVFormatContext* formatContext = nullptr;
    if (avformat_open_input(&formatContext, "./vid2.mp4", nullptr, nullptr) < 0) {
        // Handle file open error
        return 1;
    }

    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        // Handle stream info error
        return 1;
    }

    int videoStreamIndex = -1;
    AVCodecParameters* codecParameters = nullptr;

    for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
        if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            codecParameters = formatContext->streams[i]->codecpar;
            break;
        }
    }

    if (videoStreamIndex == -1 || codecParameters == nullptr) {
        // Handle video stream not found
        return 1;
    }

    const AVCodec* videoCodec = nullptr;
    videoCodec = avcodec_find_decoder(codecParameters->codec_id);

    if (!videoCodec) {
        // Handle codec not found
        return 1;
    }

    AVCodecContext* codecContext = avcodec_alloc_context3(videoCodec);
    if (!codecContext) {
        // Handle codec context allocation error
        return 1;
    }

    if (avcodec_parameters_to_context(codecContext, codecParameters) < 0) {
        // Handle codec parameters error
        return 1;
    }

    if (avcodec_open2(codecContext, videoCodec, nullptr) < 0) {
        // Handle codec open error
        return 1;
    }
    // SDL_Window* window = SDL_CreateWindowFrom((void*)get_wallpaper_window());
    SDL_Window* window = SDL_CreateWindow("Video Player", SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED, 500,
                                     500, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_YV12,
                                            SDL_TEXTUREACCESS_STREAMING, codecContext->width, codecContext->height);

    AVFrame* frame = av_frame_alloc();
    AVPacket packet;
    SDL_Event event;
    bool isRunning = true;

    const int targetFrameRate = 30; // Adjust this value to set the desired frame rate (e.g., 30 FPS)
    const int frameDelay = 1000 / targetFrameRate;

    SDL_Rect destinationRect;
    destinationRect.x = 0;    // X-coordinate of the top-left corner
    destinationRect.y = 0;    // Y-coordinate of the top-left corner
    destinationRect.w = 1920;    // Width of the destination area
    destinationRect.h = 1080;    // Height of the destination area
    
    while (isRunning) {

        // Loop to play the video until the end of the stream
        while (av_read_frame(formatContext, &packet) >= 0) {
            SDL_PollEvent(&event);
            switch (event.type) {
                case SDL_QUIT : 
                    isRunning = false;
                    break;
                default:
                    break;
            }
            if (packet.stream_index == videoStreamIndex) {
                avcodec_send_packet(codecContext, &packet);
                while (avcodec_receive_frame(codecContext, frame) == 0) {
                    SDL_UpdateYUVTexture(texture, nullptr, frame->data[0], frame->linesize[0],
                                        frame->data[1], frame->linesize[1], frame->data[2], frame->linesize[2]);
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, nullptr, &destinationRect);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(frameDelay); // Add frame rate limiting delay
                }
            }
            av_packet_unref(&packet);
        }

        // If we reach the end of the video stream, seek back to the beginning
        av_seek_frame(formatContext, videoStreamIndex, 0, AVSEEK_FLAG_FRAME);
    }

    av_frame_free(&frame);
    avcodec_close(codecContext);
    avformat_close_input(&formatContext);
    avformat_network_deinit();
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}