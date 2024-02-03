cmake_minimum_required(VERSION 3.23)
project(print)

set(CMAKE_CXX_STANDARD 20)


add_executable(ut unittest.cpp)
target_link_libraries(ut gtest)

add_executable(print main.cpp)

add_subdirectory(./googletest)
include_directories(${PROJECT_SOURCE_DIR}/src/include ./googletest/include)
link_directories(${PROJECT_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/googletest)
target_link_libraries(${PROJECT_NAME} gtest)
