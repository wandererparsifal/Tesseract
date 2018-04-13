cmake_minimum_required(VERSION 3.9)
project(cv_test)

set(CMAKE_CXX_STANDARD 11)

include_directories(${OpenCV_INCLUDE_DIRS})

find_package(OpenCV REQUIRED)

add_executable(cv_test main.cpp)

target_link_libraries(cv_test ${OpenCV_LIBS} -lhdf5 ${GTK_LIBRARIES} tesseract)