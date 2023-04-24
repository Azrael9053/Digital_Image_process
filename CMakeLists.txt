cmake_minimum_required(VERSION 3.25)
project(Digital_Image_process)

set(CMAKE_CXX_STANDARD 17)

add_executable(Digital_Image_process main.cpp bmp.h bmp.cpp img_process.h img_process.cpp)
