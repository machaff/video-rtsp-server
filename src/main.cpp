#include <iostream>
#include <gst/gst.h>
#include <thread>
#include "RtspServer.h"

int main(int argc, char *argv[]) {
    auto *server = new RtspServer("../../../Videos/sample-video.mp4");
    server->create_rtsp();

    return 0;
}