cmake_minimum_required(VERSION 2.8)
project(chat)
# 配置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


#头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/model)
include_directories(${PROJECT_SOURCE_DIR}/include/server/redis)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)

#指定子目录
add_subdirectory(src)