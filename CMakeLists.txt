cmake_minimum_required (VERSION 3.8)

#项目名称
project(demo)
set(PROJECT demo)

#使用c++11标准
add_definitions(-std=c++11)

#配置Debug或Release版本
set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_BUILD_TYPE "Release")

#引入头文件
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/app
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/include
)

#引入源文件
file(GLOB SRC_LIST "app/*.cpp")

#生成可执行文件
add_executable(${PROJECT} ${SRC_LIST})

#生成动态库
#add_library(${PROJECT} SHARED ${SRC_LIST})

#生成静态库
#add_library(${PROJECT} STATIC ${SRC_LIST})

#链接静态库和动态库
# target_link_libraries(${PROJECT} ${CMAKE_CURRENT_SOURCE_DIR}/libs/libzlog/lib/libzlog.a)

target_link_libraries(
        ${PROJECT}
        -Wl,--start-group
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/libopus.a
        -Wl,--end-group
)
