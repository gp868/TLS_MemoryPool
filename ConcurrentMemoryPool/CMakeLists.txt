
CMAKE_MINIMUM_REQUIRED(VERSION 3.0 FATAL_ERROR)
PROJECT(HELLO_WORLD)



#设置C++相关编译属性
SET(CMAKE_CXX_COMPILER "g++") #设置编译Cpp时默认使用g++编译器
SET(CMAKE_BUILD_TYPE Debug CACHE STRING "set build type to debug")#设置编译时使用Debug模式

if(CMAKE_COMPILER_IS_GNUCXX)#如果是GNU系列编译器
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -std=c++11 -pthread")#DEBUG模式选项: 允许c++11标准、O0优化、多线程 
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -std=c++11 -march=native  -pthread")#REALEASE模式选项: 允许c++11标准、O3优化、多线程。match选项可避免一些cpu上的问题
    set(CMAKE_CXX_STANDARD 11) #设置编译选项中加入c++11支持 CMake 3.1或者更高版本
    #set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")#设置编译选项中加入c++11支持 CMake 3.1更低版本
endif(CMAKE_COMPILER_IS_GNUCXX)




#设置要包含的库文件目录
#设置要包含的package目录
#设置要包含的头文件目录 这样在代码中#include的时候就会以此为相对地址
#设置要包含的源文件目录 以及输出的中间编译文件的生成地址

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/baselib)
FIND_PACKAGE(Threads REQUIRED)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/baselib)
ADD_SUBDIRECTORY(./baselib)
ADD_SUBDIRECTORY(./src)

#设置输出的可执行文件的存放目录
#设置输出的库文件的存放目录

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/baselib)


