
cmake_minimum_required (VERSION 3.8)
project("tinyxml")

#设置静态库输出的路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../../../3rd_lib/${PROJECT_NAME})

# 查找当前目录下的所有源文件
# 并将名称保存到变量
aux_source_directory(. DIR_TINYXML_SRCS)

# 生成链接库
add_library (${PROJECT_NAME} STATIC ${DIR_TINYXML_SRCS})

#target_compile_options(${PROJECT_NAME} PRIVATE "-fPIC") #在Linux下需要加上-fPIC


