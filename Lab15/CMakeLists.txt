cmake_minimum_required(VERSION 4.0)
project(Lab15 C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab15 main.c)

find_package(OpenMP REQUIRED)
if(OpenMP_C_FOUND)
    target_link_libraries(Lab15 PUBLIC OpenMP::OpenMP_C)
endif()
