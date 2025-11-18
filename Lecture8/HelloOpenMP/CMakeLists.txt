cmake_minimum_required(VERSION 3.25)
project(HelloOpenMP C)

# ЯВНО ВКАЗУЄМО GCC-15 (інакше CLion візьме AppleClang)
set(CMAKE_C_COMPILER "/opt/homebrew/bin/gcc-15")
set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/g++-15")

set(CMAKE_C_STANDARD 11)

find_package(OpenMP REQUIRED)

add_executable(HelloOpenMP
        main.c
)

target_link_libraries(HelloOpenMP PRIVATE OpenMP::OpenMP_C)
