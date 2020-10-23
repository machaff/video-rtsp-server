#ifndef RTSP_SERVER_H
#define RTSP_SERVER_H

#include <string>
#include <iostream>

class RtspServer {
    private:
        std::string video_path;

    public:
        RtspServer(const std::string _video_path);
        const std::string& get_video_path() const;
        void set_video_path(const std::string &_video_path);
        void create_rtsp();
};

#endif