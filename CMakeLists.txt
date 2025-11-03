cmake_minimum_required(VERSION 4.0)
project(TFinal C)

set(CMAKE_C_STANDARD 23)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/app
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/modules
        ${CMAKE_CURRENT_SOURCE_DIR}/generics
)


# Agrupamento de arquivos por tipo
set(APP_SOURCES
        app.c
        app/bd.c
        app/login.c
)

set(LIB_SOURCES
        lib/visual.c
)

set(GENERICS_SOURCES
        generics/lista_dupla.c
)

set(MODULES_SOURCES
        modules/cadastros.c
        modules/cargas.c
        modules/entregas.c
)

# Cria o executável incluindo todos os arquivos na ordem correta
add_executable(TFinal
        ${APP_SOURCES}
        ${LIB_SOURCES}
        ${GENERICS_SOURCES}
        ${MODULES_SOURCES}
        ${MISC_SOURCES}
)


# (Opcional) mensagens para debug do CMake
message(STATUS "Arquivos APP: ${APP_SOURCES}")
message(STATUS "Arquivos LIB: ${LIB_SOURCES}")
message(STATUS "Arquivos GENERICS: ${GENERICS_SOURCES}")
message(STATUS "Arquivos MODULES: ${MODULES_SOURCES}")
message(STATUS "Arquivos MISC: ${MISC_SOURCES}")