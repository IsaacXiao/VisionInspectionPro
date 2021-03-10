 

cmake_minimum_required (VERSION 3.8)

project("main")

SET(CMAKE_BUILD_TYPE "Debug") # 这里Type配置为Debug
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -g -ggdb")  # Debug模式下的编译指令
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -Wall")         # Release模式下的编译指令

if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif (CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif (CMAKE_HOST_UNIX)
    set(LINUX 1)
endif ()

if (WINDOWS)
    aux_source_directory(Include/PlatForm/Windows PLATFORM_SRC)
    message("windows head included")
elseif (LINUX)
    aux_source_directory(Include/PlatForm/Linux PLATFORM_SRC) 
    message("linux head included")
endif ()

#设置包含目录
include_directories(Include)

#添加其他依赖项的目录
add_subdirectory(Include/Configure/TinyXml)

# Include sub-projects.
#递归添加所有模块的子目录得研究下教程，上网查下
#https://blog.csdn.net/yunxinyi91/article/details/107485257
#就不用每次手动添加每行了
add_subdirectory (CameraGrabber/DalsaCamera)
add_subdirectory (PlcAgent/ModbusPlc)
add_subdirectory (Export/DbExport)

# 查找当前目录下的所有源文件
# 并将名称保存到变量
aux_source_directory(./Facade DIR_FACADE_SRCS)

#指定生成的是可执行文件
add_executable (${PROJECT_NAME} ${PLATFORM_SRC} ${DIR_FACADE_SRCS} main.cpp)


# 添加链接库
target_link_libraries(${PROJECT_NAME} tinyxml)

