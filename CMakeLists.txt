cmake_minimum_required(VERSION 3.26)
project(MachineVision)

set(CMAKE_CXX_STANDARD 17)

# param by cmd
# -Dparam
if (NOT DEFINED param)
    set(param "PARAM default")
    message(STATUS "No PARAM, defaulting")
else ()
    message(STATUS "PARAM, set by cmd ${param}")
endif ()

# project include
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# source
file(GLOB TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)
set(TEST_COMPILE_CODE ${TEST_SRC})
file(GLOB LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(LIB_COMPILE_CODE ${LIB_SRC})

# executable entry
add_executable(${PROJECT_NAME} ${TEST_COMPILE_CODE})

# library
set(LIB_STATIC ON)
#set(LIB_STATIC OFF)
if (LIB_STATIC)
    message(STATUS "library to be STATIC")
else ()
    message(STATUS "library to be SHARED")
endif ()

set(LIB_NAME "MachineVisionLib")
#自己的库源码
add_library(${LIB_NAME} SHARED ${LIB_COMPILE_CODE})

# include 头文件
message(STATUS "----------------- include -----------------")
include_directories(${OpenCV_INCLUDE_DIRS})

# depend library
message(STATUS "----------------- dependencies -----------------")
include(${CMAKE_CURRENT_SOURCE_DIR}/depend-OpenCv-config.cmake)
