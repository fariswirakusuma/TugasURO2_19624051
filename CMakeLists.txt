cmake_minimum_required(VERSION 3.10)

project(opencvproj)

find_package(OpenCV REQUIRED)  # This should find all necessary OpenCV modules

add_executable(opencvproj main.cpp)

target_link_libraries(opencvproj ${OpenCV_LIBS})  # Link against OpenCV libraries
