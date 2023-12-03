message(STATUS "------${LIB_NAME}-----------")
message(STATUS "------ config opencv -----------")
# OpenCV
set(OpenCV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/OpenCV-MinGW-Build)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PUBLIC ${OpenCV_DIR}/x64/mingw/bin)
#link_libraries命令是一个全局命令，它用于为整个项目中的所有目标（包括可执行文件和库）指定要链接的库
#target_link_libraries命令用于为特定目标（可执行文件或库）指定链接的库
#target_link_libraries更推荐，因为它提供了更细粒度的控制，使你能够为不同的目标指定不同的链接库，而不是全局应用相同的链接库。
link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARY_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
if (OpenCV_FOUND)
    message(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")
    message(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
#    MESSAGE(STATUS "OpenCV version: "${OpenCV_VERSION})
    MESSAGE(${PROJECT_SOURCE_DIR})
    MESSAGE(${PROJECT_BINARY_DIR})
else ()
    message(FATAL_ERROR "opencv Not Found!")
endif (OpenCV_FOUND)