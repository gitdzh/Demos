cmake_minimum_required(VERSION 3.6)
project(getAllFiles)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# 寻找OpenCV库
FIND_PACKAGE( OpenCV REQUIRED )
# 添加头文件
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )
MESSAGE(STATUS "OpenCV library status:")
MESSAGE(STATUS "    version: ${OpenCV_VERSION}")
MESSAGE(STATUS "    libraries: ${OpenCV_LIBS}")
MESSAGE(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

set(SOURCE_FILES main.cpp getAllFiles.cpp getAllFiles.h)
add_executable(getAllFiles ${SOURCE_FILES})

# 链接OpenCV库
TARGET_LINK_LIBRARIES( getAllFiles ${OpenCV_LIBS} )