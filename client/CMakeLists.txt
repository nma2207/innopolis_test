cmake_minimum_required(VERSION 3.0.0)
project(client VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(client main.cpp
    src/client.cpp
    src/tcp_client.cpp
    src/udp_client.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
target_include_directories(client PRIVATE ${PROJECT_SOURCE_DIR}/include)
