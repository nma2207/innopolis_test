cmake_minimum_required(VERSION 3.0.0)
project(server VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(server main.cpp
    src/server.cpp
    src/tcp_server.cpp
    src/udp_server.cpp
    src/numbersprocessor.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
target_include_directories(server PRIVATE ${PROJECT_SOURCE_DIR}/include)