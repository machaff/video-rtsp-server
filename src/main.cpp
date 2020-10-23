#include <iostream>
#include <gst/gst.h>
#include "RtspServer.h"

int main(int argc, char *argv[]) {
    auto *server = new RtspServer(" ");
    server->create_rtsp();

    return 0;
}