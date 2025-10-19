cmake_minimum_required(VERSION 4.0)
project(HelloOpenMP C)

set(CMAKE_C_STANDARD 11)

find_package(OpenMP REQUIRED)

add_executable(HelloOpenMP main.c)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_C)
