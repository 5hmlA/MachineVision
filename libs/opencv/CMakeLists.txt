
set(MY_OPENCV "MyOpenCV")
message(STATUS "----------------- config start ${MY_OPENCV}-----------------")
# BUILD_SHARED_LIBS 是一个 CMake 变量，用于控制生成共享库（shared library）还是静态库（static library）。默认情况下，CMake 会生成静态库，但是通过设置 BUILD_SHARED_LIBS 为 ON，可以指示 CMake 生成共享库
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
message(STATUS "----------------- BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS}-----------------")

message(STATUS "XXXXXX ${CMAKE_SOURCE_DIR}")
message(STATUS "XXXXXX ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "XXXXXX ${LIBRARY_OUTPUT_PATH}")
message(STATUS "XXXXXX ${PROJECT_BINARY_DIR}")

#把src目录中的所有源文件都储存在var变量中
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_MAIN)
add_library(${MY_OPENCV} src/opencv_first.cpp)
#add_library(${MY_OPENCV} ${SRC_MAIN})
#修改库生成所在的路径，生成的库放到lib下
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../lib)
#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(OPENCV_WHO ${MY_OPENCV})
message(STATUS "----------------- dependencies ${PROJECT_NAME}-----------------")
include(../../depend-OpenCv-config.cmake)
message(STATUS "----------------- config end ${MY_OPENCV}-----------------")