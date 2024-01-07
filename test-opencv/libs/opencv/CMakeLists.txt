
set(MY_OPENCV "MyOpenCV")
message(STATUS "----------------- config start ${MY_OPENCV}-----------------")
# BUILD_SHARED_LIBS 是一个 CMake 变量，用于控制生成共享库（shared library）还是静态库（static library）。默认情况下，CMake 会生成静态库，但是通过设置 BUILD_SHARED_LIBS 为 ON，可以指示 CMake 生成共享库
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
message(STATUS "----------------- BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS}-----------------")

message(STATUS "LIBS CMAKE_SOURCE_DIR---- ${CMAKE_SOURCE_DIR}")
message(STATUS "LIBS CMAKE_CURRENT_SOURCE_DIR---- ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "LIBS LIBRARY_OUTPUT_PATH---- ${LIBRARY_OUTPUT_PATH}")
message(STATUS "LIBS PROJECT_BINARY_DIR --- ${PROJECT_BINARY_DIR}")

#把src目录中的所有源文件都储存在var变量中
aux_source_directory(src SRC_MAIN)
add_library(${MY_OPENCV} src/opencv_first.cpp)

#最佳实践：不要在library中修改LIBRARY_OUTPUT_PATH，在exe project中统一设置CMAKE_RUNTIME_OUTPUT_DIRECTORY确保其和EXECUTABLE_OUTPUT_PATH路径保持一致
#LIBRARY_OUTPUT_PATH 修改库.dll和.dll.a生成所在的路径， 需要主义的是必须要和.exe在同一路径否则exe无法找到运行库
#CMAKE_RUNTIME_OUTPUT_DIRECTORY这个被设置了LIBRARY_OUTPUT_PATH就无效
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})

set(OPENCV_WHO ${MY_OPENCV})
message(STATUS "----------------- dependencies ${PROJECT_NAME}-----------------")
include(../../../depend-OpenCv-config.cmake)
message(STATUS "----------------- config end ${MY_OPENCV}-----------------")