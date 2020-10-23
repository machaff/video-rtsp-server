#include "RtspServer.h"
#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>

std::string generate_pipeline(std::string file_path);

RtspServer::RtspServer(const std::string _video_path) : video_path(_video_path) {
    gst_init(NULL, NULL);
}

const std::string &RtspServer::get_video_path() const {
    return this->video_path;
}

void RtspServer::set_video_path(const std::string &_video_path) {
    this->video_path = _video_path;
}

void RtspServer::create_rtsp() {
    GMainLoop *loop;
    GstRTSPServer *server;
    GstRTSPMountPoints *mounts;
    GstRTSPMediaFactory *factory;

    loop = g_main_loop_new(NULL, FALSE);

    server = gst_rtsp_server_new();

    mounts = gst_rtsp_server_get_mount_points(server);
    gst_rtsp_server_set_service(server, SERVER_PORT);

    factory = gst_rtsp_media_factory_new();
    std::cout << generate_pipeline(get_video_path()) << std::endl;
    gst_rtsp_media_factory_set_launch(factory, generate_pipeline(get_video_path()).c_str());

    gst_rtsp_media_factory_set_shared(factory, TRUE);

    gst_rtsp_mount_points_add_factory (mounts, "/test", factory);
    g_object_unref (mounts);

    gst_rtsp_server_attach (server, NULL);
    g_print ("stream ready at rtsp://127.0.0.1:2323/test\n");
    g_main_loop_run (loop);
}

std::string generate_pipeline(std::string file_path) {
    return "filesrc location=\"" + file_path + "\" ! qtdemux ! video/x-h264 ! rtph264pay name=pay0";
}