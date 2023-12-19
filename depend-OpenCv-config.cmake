message(STATUS "============================ config opencv for ${OPENCV_WHO} ${PROJECT_NAME}============================")
# OpenCV
set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/dependencies/OpenCV-MinGW-Build)

find_package(OpenCV REQUIRED)

message(STATUS "OpenCV_INCLUDE_DIRS:${OpenCV_INCLUDE_DIRS}")
target_include_directories(${OPENCV_WHO} PUBLIC ${OpenCV_INCLUDE_DIRS})

set(OpenCV_LIBRARY_DIRS ${OpenCV_DIR}//x64/mingw/lib)
message(STATUS "OpenCV_LIBRARY_DIRS:${OpenCV_LIBRARY_DIRS}")
target_link_directories(${OPENCV_WHO} PUBLIC ${OpenCV_LIBRARY_DIRS})
message(STATUS "OpenCV_LIBS:${OpenCV_LIBS}")
target_link_libraries(${OPENCV_WHO} PUBLIC ${OpenCV_LIBS})

if (OpenCV_FOUND)
    message(STATUS "OpenCV_LIBS:${OpenCV_LIBS}")
    message(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
else ()
    message(FATAL_ERROR "opencv Not Found!")
endif (OpenCV_FOUND)