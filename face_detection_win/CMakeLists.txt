cmake_minimum_required(VERSION 3.5)
project(face_detection)

set(CMAKE_CXX_FLAGES "${CMAKE_CXX_FLAGS} -std=c++")

#set(OpenCV_DIR "/home/rui/Downloads/opencv-3.3.0/build/")
if(WIN32)
    set(OpenCV_DIR "C:\\opencv\\build\\x64\\vc15\\lib")
elseif(LINUX)
    set(OpenCV_DIR "/home/rui/Downloads/opencv-3.3.0/build/")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#find_package(OpenCV REQUIRED PATHS "/home/rui/Downloads/opencv-3.3.0/")
if(WIN32)
    find_package(OpenCV REQUIRED PATHS "C:\\opencv\\sources")
elseif(LINUX)
    find_package(OpenCV REQUIRED PATHS "/home/rui/Downloads/opencv-3.3.0/")
endif()

set(OpenCV_FOUND 1)
include_directories(${OpenCV_INCLUDE_DIRS})
if(WIN32)
    include(C:\\dlib-19.9\\dlib\\cmake)
elseif(LINUX)
    include(/home/rui/Downloads/dlib-19.1/dlib/cmake)
endif()

#set(CMAKE_CXX_STANDARD 11)

add_executable(face_detection main.cpp eyeLike.cpp findEyeCenter.h findEyeCenter.cpp findEyeCorner.h findEyeCorner.cpp constants.h helpers.cpp helpers.h eyeLike.h)

#set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)
target_link_libraries(face_detection ${OpenCV_LIBS})
target_link_libraries(face_detection dlib)