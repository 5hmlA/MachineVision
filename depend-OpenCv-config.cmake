message(STATUS "============================ config opencv for ${OPENCV_WHO} ${PROJECT_NAME}============================")
# OpenCV
set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/dependencies/OpenCV-MinGW-Build)

find_package(OpenCV REQUIRED)

if (OpenCV_FOUND)
    message(STATUS "OpenCV_INCLUDE_DIRS:${OpenCV_INCLUDE_DIRS}")
    target_include_directories(${OPENCV_WHO} PUBLIC ${OpenCV_INCLUDE_DIRS})

    set(OpenCV_LIBRARY_DIRS ${OpenCV_DIR}//x64/mingw/lib)
    message(STATUS "OpenCV_LIBRARY_DIRS:${OpenCV_LIBRARY_DIRS}")
#    告诉 CMake 在链接目标时去哪里寻找库文件。这在处理共享库或静态库时很有用，因为编译器需要知道在哪里找到库文件的位置。
    target_link_directories(${OPENCV_WHO} PUBLIC ${OpenCV_LIBRARY_DIRS})
    message(STATUS "OpenCV_LIBS:${OpenCV_LIBS}")
    target_link_libraries(${OPENCV_WHO} PUBLIC ${OpenCV_LIBS})
else ()
    message(FATAL_ERROR "opencv Not Found!")
endif (OpenCV_FOUND)