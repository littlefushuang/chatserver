aux_source_directory(. SRC_LIST)

#设置可执行文件存储路径

add_executable(server ${SRC_LIST})
#依赖库文件
target_link_libraries(muduo_server muduo_net muduo_base pthread)