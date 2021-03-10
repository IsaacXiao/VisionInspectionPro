
cmake_minimum_required (VERSION 3.8)

project("DalsaCamera")

SET(CMAKE_BUILD_TYPE "Debug") # 这里Type配置为Debug
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -g -ggdb")  # Debug模式下的编译指令
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -Wall")         # Release模式下的编译指令

#设置动态库输出的路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../../build/CameraGrabber/${PROJECT_NAME})

#指定要生成的是动态库
add_library (${PROJECT_NAME} SHARED DalsaCamera.cpp DalsaDll.cpp)

# 添加链接库
target_link_libraries(${PROJECT_NAME} tinyxml)
