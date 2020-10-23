find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB REQUIRED glib-2.0)

include_directories(
  ${GLIB_INCLUDE_DIRS}
)

link_directories(
  ${GLIB_LIBRARY_DIRS}
)

set(GSTREAMER_MINIMUM_VERSION 1.0.5)

pkg_check_modules(GST1_TEST gstreamer-1.0)
if ( GST1_TEST_FOUND AND NOT ${GST1_TEST_VERSION} VERSION_LESS ${GSTREAMER_MINIMUM_VERSION} )
    pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
    pkg_check_modules(GSTREAMER-AUDIO REQUIRED gstreamer-audio-1.0)
    pkg_check_modules(GSTREAMER-PBUTILS REQUIRED gstreamer-pbutils-1.0)
    pkg_check_modules(GSTREAMER-RTSP REQUIRED gstreamer-rtsp-1.0)
    pkg_check_modules(GSTREAMER-RTSP-SERVER gstreamer-rtsp-server-1.0)
    add_definitions(-DGST_API_VERSION_1=1)
else()
    # fallback to gstreamer-0.10
    unset(GSTREAMER_MINIMUM_VERSION)
    pkg_check_modules(GSTREAMER REQUIRED gstreamer-0.10)
    pkg_check_modules(GSTREAMER-AUDIO REQUIRED gstreamer-audio-0.10)
    set_source_files_properties(main.cpp PROPERTIES COMPILE_DEFINITIONS "GLIB_DISABLE_DEPRECATION_WARNINGS=1")
endif()

include_directories(
  ${GSTREAMER_INCLUDE_DIRS}
  ${GSTREAMER-AUDIO_INCLUDE_DIRS}
  ${GSTREAMER-PBUTILS_INCLUDE_DIRS}
  ${GSTREAMER-RTSP_INCLUDE_DIRS}
  ${GSTREAMER-RTSP-SERVER_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

link_directories(
  ${GSTREAMER_LIBRARY_DIRS}
  ${GSTREAMER-AUDIO_LIBRARY_DIRS}
  ${GSTREAMER-PBUTILS_LIBRARY_DIRS}
  ${GSTREAMER-RTSP_LIBRARY_DIRS}
  ${GSTREAMER-RTSP-SERVER_LIBRARY_DIRS}
)

set(video-rtsp-server_SOURCES main.cpp RtspServer.cpp)

set(video-rtsp-server_LIBRARIES
  ${GSTREAMER_LIBRARIES}
  ${GSTREAMER-AUDIO_LIBRARIES}
  ${GSTREAMER-PBUTILS_LIBRARIES}
  ${GSTREAMER-RTSP_LIBRARIES}
  ${GSTREAMER-RTSP-SERVER_LIBRARIES}
    
  pthread
  ${GLIB_LIBRARIES}
  ${GLIB_GIO_LIBRARIES}
  ${GLIB_GOBJECT_LIBRARIES}
)

add_executable(video-rtsp-server ${video-rtsp-server_SOURCES})
target_link_libraries(video-rtsp-server ${video-rtsp-server_LIBRARIES})