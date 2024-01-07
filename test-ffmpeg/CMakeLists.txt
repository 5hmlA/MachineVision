project(TestFFmpeg)

# 指定可执行文件存放目录
# 注意：要确保：CMAKE_RUNTIME_OUTPUT_DIRECTORY和EXECUTABLE_OUTPUT_PATH目录保持一致
#设置整个项目的 动态库输出目录
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/build)
#设置整个项目的 静态库输出目录
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/build)
#设置整个项目的 可执行文件输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/build)

aux_source_directory(. SRC_TEST)
# 添加可执行源文件
add_executable(${PROJECT_NAME} ${SRC_TEST})

set(FFMPEG_DIR "${CMAKE_SOURCE_DIR}/dependencies/ffmpeg-win64-gpl-shared")
message(STATUS ${FFMPEG_DIR})
message(STATUS ${CMAKE_SOURCE_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC ${FFMPEG_DIR}/include)
# 设置连接路径只对编译有用，运行没用，需要添加到环境变量或者dill文件和exe文件在一个目录，或者把动态库所在目录配置到工作目录，或者环境变量
target_link_directories(${PROJECT_NAME} PUBLIC ${FFMPEG_DIR}/lib ${FFMPEG_DIR}/bin)
#多个库必须换行
target_link_libraries(${PROJECT_NAME} PUBLIC avcodec
        avdevice
        avfilter
        avformat
        avutil
        postproc
        swresample
        swscale)


#https://github.com/Javernaut/FFmpegExamples/blob/master/CMakeLists.txt