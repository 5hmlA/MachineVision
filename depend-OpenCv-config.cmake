message(STATUS "============================ config opencv for ${OPENCV_WHO} ${PROJECT_NAME}============================")

# OpenCV
if (WIN32)
    set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/dependencies/OpenCV-MinGW-Build)
elseif (APPLE)
#    安装 opencv
#    brew install opencv
#    查看 opencv 的安装路径
#    brew info opencv
    set(OpenCV_DIR "/usr/local/Cellar/opencv/4.9.0_1")
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
#    安装 opencv
#    sudo apt install opencv
#    查看 opencv 的安装路径
#    which opencv
    message(STATUS "linux")
endif ()

find_package(OpenCV REQUIRED)

if (OpenCV_FOUND)
    message(STATUS "OpenCV_INCLUDE_DIRS:${OpenCV_INCLUDE_DIRS}")
    target_include_directories(${OPENCV_WHO} PUBLIC ${OpenCV_INCLUDE_DIRS})

    set(OpenCV_LIBRARY_DIRS ${OpenCV_DIR}/x64/mingw/lib ${OpenCV_DIR}/x64/mingw/bin)
    message(STATUS "OpenCV_LIBRARY_DIRS:${OpenCV_LIBRARY_DIRS}")
#    告诉 CMake 在链接目标时去哪里寻找库文件。这在处理共享库或静态库时很有用，因为编译器需要知道在哪里找到库文件的位置。
    target_link_directories(${OPENCV_WHO} PUBLIC ${OpenCV_LIBRARY_DIRS})
    message(STATUS "OpenCV_LIBS:${OpenCV_LIBS}")
    target_link_libraries(${OPENCV_WHO} PUBLIC ${OpenCV_LIBS})
else ()
    message(FATAL_ERROR "opencv Not Found!")
endif (OpenCV_FOUND)