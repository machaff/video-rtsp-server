#include <iostream>
#include <gst/gst.h>

int main(int argc, char *argv[]) {

    gst_init(&argc, &argv);

    std::cout << "Hello gstreamer" << std::endl;
    return 0;
}