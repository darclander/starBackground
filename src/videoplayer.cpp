#include "videoplayer.hpp"


videoPlayer::videoPlayer(SDL_Renderer *r, const std::string &filePath) {
    renderer = r;
    avformat_network_init();
    std::cout << "Opening file: " << filePath << std::endl;
    
    if (avformat_open_input(&formatContext, filePath.c_str(), nullptr, nullptr) < 0) {
        // Handle file open error
        // return 1;
    }

    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        // Handle stream info error
        // return 1;
    }

    for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
        if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            codecParameters = formatContext->streams[i]->codecpar;
            break;
        }
    }

    if (videoStreamIndex == -1 || codecParameters == nullptr) {
        // Handle video stream not found
        // return 1;
    }

    videoCodec = avcodec_find_decoder(codecParameters->codec_id);

    if (!videoCodec) {
        // Handle codec not found
        // return 1;
    }

    codecContext = avcodec_alloc_context3(videoCodec);
    if (!codecContext) {
        // Handle codec context allocation error
        // return 1;
    }

    if (avcodec_parameters_to_context(codecContext, codecParameters) < 0) {
        // Handle codec parameters error
        // return 1;
    }

    if (avcodec_open2(codecContext, videoCodec, nullptr) < 0) {
        // Handle codec open error
        // // return 1;
    }

    frame = av_frame_alloc();

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_YV12,
                                            SDL_TEXTUREACCESS_STREAMING, codecContext->width, codecContext->height);
}


void videoPlayer::update() {
    while (av_read_frame(formatContext, &packet) >= 0) {
        if (packet.stream_index == videoStreamIndex) {
            avcodec_send_packet(codecContext, &packet);
            while (avcodec_receive_frame(codecContext, frame) == 0) {
                SDL_PollEvent(&event);
                switch (event.type) {
                    case SDL_QUIT : 
                        isPlaying = false;
                        break;
                    default:
                        break;
                }
                if(!isPlaying) {
                    return;
                }
                SDL_UpdateYUVTexture(texture, nullptr, frame->data[0], frame->linesize[0],
                                        frame->data[1], frame->linesize[1], frame->data[2], frame->linesize[2]);
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture, nullptr, nullptr);
                SDL_RenderPresent(renderer);
                SDL_Delay(frameDelay); // Add frame rate limiting delay
            }
        }
        av_packet_unref(&packet);
    }

    // If we reach the end of the video stream, seek back to the beginning
    av_seek_frame(formatContext, videoStreamIndex, 0, AVSEEK_FLAG_FRAME);
}

videoPlayer::~videoPlayer() {
    av_frame_free(&frame);
    avcodec_close(codecContext);
    avformat_close_input(&formatContext);
    avformat_network_deinit();
    SDL_DestroyTexture(texture);
}