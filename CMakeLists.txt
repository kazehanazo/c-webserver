# 最低CMake版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(MyWebServer)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 指定源代码目录
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# 包含的源文件
file(GLOB_RECURSE SOURCES
    ${SRC_DIR}/*.cpp
)

# 设置头文件目录
include_directories(
    ${SRC_DIR}/buffer
    ${SRC_DIR}/config
    ${SRC_DIR}/http
    ${SRC_DIR}/log
    ${SRC_DIR}/timer
    ${SRC_DIR}/pool
    ${SRC_DIR}/server
)

# 添加主文件 main.cpp
set(MAIN_FILE ${CMAKE_SOURCE_DIR}/main.cpp)

# 将所有源文件与 main.cpp 编译为可执行文件
add_executable(MyExecutable ${MAIN_FILE} ${SOURCES})

# 手动使用 mysql_config 查找 MySQL 库和头文件
execute_process(COMMAND mysql_config --cflags OUTPUT_VARIABLE MYSQL_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND mysql_config --libs OUTPUT_VARIABLE MYSQL_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)

# 移除多余的库
string(REPLACE "-lmysql_sys" "" MYSQL_LIBS "${MYSQL_LIBS}")
string(REPLACE "-lmysql_strings" "" MYSQL_LIBS "${MYSQL_LIBS}")

# 包含 MySQL 头文件目录
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MYSQL_CFLAGS}")
# 链接 MySQL 库
target_link_libraries(MyExecutable PRIVATE ${MYSQL_LIBS})

# 添加 pthread 库
find_package(Threads REQUIRED)
target_link_libraries(MyExecutable PRIVATE Threads::Threads)

# 为可执行文件指定输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
