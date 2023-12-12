cmake_minimum_required(VERSION 3.10)
project(projeto-sgbd-itp C)

set(CMAKE_C_STANDARD 11)

add_library(my_library SHARED
    ./functions/menu.c
    ./functions/table.c
    ./functions/auxfuncs.c
    ./functions/fileOp.c
)

add_executable(main main.c)

target_link_libraries(main my_library)
