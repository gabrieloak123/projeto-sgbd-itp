cmake_minimum_required(VERSION 3.10)
project(projeto-sgbd-itp C)

# Setar a versão do C e habilitar flags de debug (-g) e desabilitar otimizações (-O0)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_BUILD_TYPE Debug)

# Incluir diretório com headers
include_directories(src/functions)

# Coletar todos os arquivos .c
file(GLOB_RECURSE SOURCES "src/functions/*.c")

# Criar a biblioteca compartilhada
add_library(my_library SHARED ${SOURCES})

# Definir o executável
add_executable(main src/main.c)

# Ligar a biblioteca ao executável
target_link_libraries(main my_library)

# Setar o tipo de build padrão para Debug
set(CMAKE_BUILD_TYPE Debug)
