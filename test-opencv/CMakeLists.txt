project(TestOpenCV)

# param by cmd
# -Dparam
if (NOT DEFINED param)
    set(param "PARAM default")
    message(STATUS "No PARAM, defaulting")
else ()
    message(STATUS "PARAM, set by cmd ${param}")
endif ()
# 指定可执行文件存放目录
# 注意：要确保：CMAKE_RUNTIME_OUTPUT_DIRECTORY和EXECUTABLE_OUTPUT_PATH目录保持一致
#设置整个项目的 动态库输出目录, 建议定义在exe项目的CMakeLists中,library项目中的CMakeLists中不要修改
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/build)
#设置整个项目的 静态库输出目录, 建议定义在exe项目的CMakeLists中,library项目中的CMakeLists中不要修改
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/build)
#设置整个项目的 可执行文件输出目录, 建议定义在exe项目的CMakeLists中,library项目中的CMakeLists中不要修改
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/build)

#修改库library生成.dill或者.a所在的路径， 必须要和.exe在同一路径否则无法找到运行库, 建议定义在exe项目中
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})


add_subdirectory(libs/opencv)
# dependencies\OpenCV-MinGW-Build\x64\mingw\bin  需要此目录绝对路径配置到工作目录，否则运行失败

message(STATUS "CMAKE_CURRENT_SOURCE_DIR---- ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "EXECUTABLE_OUTPUT_PATH---- ${EXECUTABLE_OUTPUT_PATH}")
message(STATUS "PROJECT_BINARY_DIR --- ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY --- ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "CMAKE_LIBRARY_PATH --- ${CMAKE_LIBRARY_PATH}")

aux_source_directory(. SRC_TEST)
# 添加可执行源文件
add_executable(${PROJECT_NAME} ${SRC_TEST})

#target_link_directories 设置连接路径只对编译有用，运行没用，需要添加到环境变量或者dill文件和exe文件在一个目录
#target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR})
#target_link_directories(${PROJECT_NAME} PRIVATE D:/000/OpenCV-MinGW/x64/mingw/bin)
# project include
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/opencv)

target_link_libraries(${PROJECT_NAME} PUBLIC MyOpenCV)
#引入多个头文件目录
#include_directories(./src_lib1 ./src_lib2)

#https://blog.csdn.net/hezhongla0811/article/details/109769789
#target_link_directories 设置连接路径只对编译有用，运行没用，需要添加到环境变量或者dill文件和exe文件在一个目录
#target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/opencv/src)

# library
set(LIB_STATIC ON)
#set(LIB_STATIC OFF)
if (LIB_STATIC)
    message(STATUS "library to be STATIC")
else ()
    message(STATUS "library to be SHARED")
endif ()

# depend library
#message(STATUS "----------------- dependencies -----------------")
#set(OPENCV_WHO ${LIB_NAME})
#include(${CMAKE_CURRENT_SOURCE_DIR}/depend-OpenCv-config.cmake)


# 指定引用的外部库的搜索路径
#LINK_DIRECTORIES(${ROOT_DIR}/3rdlib)
#TARGET_LINK_LIBRARIES(target_name libmath.a)
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
#在libs目录下查找lib_name的库，以LIB_FIND变量保存这个库
#find_library(LIB_FIND lib_name ${PROJECT_SOURCE_DIR}/libs)
#将变量LIB_FIND对应的库连接到项目
#target_link_libraries(${PROJECT_NAME} ${LIB_FIND})


#find_library(var lib_name lib_path1 lib_path2)
# 函数作用：查找库，并把库的绝对路径和名称存储到第一个参数里
# 参数var：用于存储查找到的库
# 参数lib_name：想要查找的库的名称，默认是查找动态库，想要指定查找动态库或静态库
#       可以加后缀，例如 funcname.so 或 funcname.a
# 参数lib_path：想要从哪个路径下查找库，可以指定多个路径

#add_subdirectory 指明本项目包含一个子目录 math，这样 math 目录下的 CMakeLists.txt 文件和源代码也会被处理
#target_link_libraries 指定可执行文件需要使用的库文件
#target_include_directories 指定可执行文件需要使用的库的头文件路径

#add_subdirectory 和 include 的区别
#add_subdirectory 用于将另一个目录中的 CMakeLists.txt 文件包含到当前的 CMake 构建中。
#当使用 add_subdirectory 时，CMake 会进入指定的目录，并在那里执行另一个 CMakeLists.txt 文件，构建并添加其中定义的目标或变量到当前的构建系统中。
#这个指令允许你将其他项目或目录作为子项目集成到当前的项目中，以便在构建时将它们一并编译或链接到你的项目中
#include 指令用于在当前的 CMakeLists.txt 文件中包含另一个 CMake 脚本文件
#当你在 CMakeLists.txt 中使用 include 时，它会直接包含指定文件的内容，就好像这些内容原本就在当前文件中一样。
#这个指令通常用于包含一些辅助函数或宏，或者将常用的代码段放在单独的文件中以便重复使用。

#查找外部库，在指定路径lib_path下查找lib_name这个库，（找到的库的路径）存放到var变量中
#find_library(var lib_name PATHS ${CMAKE_SOURCE_DIR}/lib_path)

#find_library: 直接在 CMake 中调用，通过指定库的名称和路径等参数来查找库文件。它不依赖于外部提供的配置文件，而是直接执行库的查找
#find_package: 通常需要软件包提供的 Find<Package>.cmake 模块或配置文件的支持。这些文件由软件包维护者提供，并定义了如何查找和使用软件包。当使用 find_package 时，CMake 会调用这些模块或配置文件来定位软件包。
#在使用 find_package 时，它会依赖于相应软件包提供的 Find<Package>.cmake
#模块或是包的配置文件（<Package>Config.cmake 或 <lower-case-package>-config.cmake）。
#这些文件中包含了关于软件包的信息，包括头文件路径(VAR_INCLUDE_DIR)和库文件路径(VAR_LIBRARIES_DIR)。
#(VAR_FOUND)是否被找到 ，(VAR_VERSION)版本号
