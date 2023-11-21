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
# 指定可执行文件存放目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

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

# include  指定头文件搜索路径
message(STATUS "----------------- include -----------------")
include_directories(${OpenCV_INCLUDE_DIRS})


# depend library
message(STATUS "----------------- dependencies -----------------")
include(${CMAKE_CURRENT_SOURCE_DIR}/depend-OpenCv-config.cmake)


# 指定引用的外部库的搜索路径
#LINK_DIRECTORIES(${ROOT_DIR}/3rdlib)
#TARGET_LINK_LIBRARIES(sample7 libmath.a)
#指定要连接的静态库，必须要有，第二个参数也可以换成math，那么将自动去搜索libmath.a或者libmath.so或者libmath.dyld动态库


# 指定头文件搜索路径
#INCLUDE_DIRECTORIES(${ROOT_DIR}/3rdlib)
#
## 以导入外部库的方式(不会重新编译)重新构建一个静态库libMath
#add_library(libMath STATIC IMPORTED)
## 设置要导入的外部静态库的路径
#set_target_properties(libMath PROPERTIES IMPORTED_LOCATION ${ROOT_DIR}/3rdlib/libmath.a)
#
## 指定可执行文件存放目录
#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#
## 构建可执行程序
#ADD_EXECUTABLE(sample7 main.cpp)
## 注意这里连接的库名为新构建的库名libMath而外部库libmath
#TARGET_LINK_LIBRARIES(sample7 libMath)



#1、引入静态库时，静态库在连接阶段会被连接到最终目标中(比如可执行执行程序中)，缺点就是同一份静态库如果被不同的程序引用，那么内存中会存在这个静态库函数的多份拷贝
#2、引入动态库时，连接阶段不会被拷贝最终目标中，程序运行时将按照指定的规则(上一步提到的规则，并非编译时的动态库路径)去搜索这个动态库，搜索到了之后才加载到内存中。所以多个程序就算引用了同一个动态库，内存中也只是存在一份动态库函数的拷贝

