cmake_minimum_required(VERSION 3.10)
project(TugasURO2)

find_package(OpenCV REQUIRED)

# Define your executable target
add_executable(TugasURO2 main.cpp)  # Replace main.cpp with your main file

# Link OpenCV libraries to your target
target_link_libraries(TugasURO2 ${OpenCV_LIBS})
