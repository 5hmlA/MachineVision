project(TestFFmpeg)

# 注意：要确保：CMAKE_RUNTIME_OUTPUT_DIRECTORY和EXECUTABLE_OUTPUT_PATH目录保持一致
#设置整个项目的 动态库输出目录, 建议定义在exe项目的CMakeLists中,library项目中的CMakeLists中不要修改
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
#设置整个项目的 静态库输出目录, 建议定义在exe项目的CMakeLists中,library项目中的CMakeLists中不要修改
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
#设置整个项目的 可执行文件输出目录, 建议定义在exe项目的CMakeLists中,library项目中的CMakeLists中不要修改
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

#修改库library生成.dill或者.a所在的路径， 必须要和.exe在同一路径否则无法找到运行库, 建议定义在exe项目中
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})

aux_source_directory(src/. SRC_TEST)
# 添加可执行源文件
add_executable(${PROJECT_NAME} ${SRC_TEST})
# 定义测试视频文件常量
target_compile_definitions(${PROJECT_NAME} PRIVATE TEST_VIDEO="${CMAKE_CURRENT_SOURCE_DIR}/chutian.mp4")

if (WIN32)
    set(FFMPEG_DIR "${CMAKE_SOURCE_DIR}/dependencies/ffmpeg-win64-gpl-shared")
elseif (APPLE)
#    安装 opencv
#    brew install opencv
#    查看 opencv 的安装路径
#    brew info opencv
    set(FFMPEG_DIR "/usr/local/Cellar/ffmpeg/6.1.1_2")
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(STATUS "linux")
endif ()

message(STATUS ${FFMPEG_DIR})
message(STATUS ${CMAKE_SOURCE_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC ${FFMPEG_DIR}/include)
# 动态库文件必须添加到运行时的path路径
# 设置连接路径只对编译有用，运行没用，需要添加到环境变量或者dill文件和exe文件在一个目录，或者把动态库所在目录配置到工作目录，或者环境变量
target_link_directories(${PROJECT_NAME} PUBLIC ${FFMPEG_DIR}/lib)
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