cmake_minimum_required(VERSION 3.0.0)
project(test_server)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(test_server
    main.cpp 
    ../src/numbersprocessor.cpp)
target_link_libraries(test_server  ${GTEST_LIBRARIES} pthread )
target_include_directories(test_server PRIVATE ${PROJECT_SOURCE_DIR}/../include)