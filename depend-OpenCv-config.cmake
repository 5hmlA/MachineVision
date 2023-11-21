message(STATUS "------${LIB_NAME}-----------")
message(STATUS "------ config opencv -----------")
# OpenCV
set(OpenCV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/OpenCV-MinGW-Build)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PUBLIC ${OpenCV_DIR}/x64/mingw/bin)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARY_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
if (OpenCV_FOUND)
    message(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")
    message(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
else ()
    message(FATAL_ERROR "opencv Not Found!")
endif (OpenCV_FOUND)