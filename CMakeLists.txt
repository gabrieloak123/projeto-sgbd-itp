cmake_minimum_required(VERSION 3.10)
project(projeto-sgbd-itp C)

set(CMAKE_C_STANDARD 11)

include_directories(functions)

file(GLOB_RECURSE SOURCES "functions/*.c" "functions/*.h")
add_library(my_library SHARED ${SOURCES} defs.h)

add_executable(main main.c)

target_link_libraries(main my_library)