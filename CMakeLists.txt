
cmake_minimum_required(VERSION 2.8)
project(countdots)
find_package(OpenCV REQUIRED)
add_executable(countdots countDots.cpp)
target_link_libraries(countdots ${OpenCV_LIBS})
