cmake_minimum_required(VERSION 3.10)
project(projeto-sgbd-itp C)

set(CMAKE_C_STANDARD 11)

include_directories(functions)

file(GLOB_RECURSE SOURCES "functions/*.c" "functions/*.h")
add_library(my_library SHARED ${SOURCES} defs.h)

add_library(my_test_library SHARED functions/fileOp.c functions/funcs.h defs.h)

add_executable(main main.c)
add_executable(test test.c)

target_link_libraries(main my_library)
target_link_libraries(test my_library)