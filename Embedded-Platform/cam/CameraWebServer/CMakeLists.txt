cmake_minimum_required(VERSION 3.26)
project(CameraWebServer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CameraWebServer
        app_httpd.cpp
        camera_index.h
        camera_pins.h
        CameraWebServer.ino)
