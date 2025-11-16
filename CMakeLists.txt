cmake_minimum_required(VERSION 3.16)
project(TFinal C)

set(CMAKE_C_STANDARD 23)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/app
        ${CMAKE_CURRENT_SOURCE_DIR}/lite
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/modules
        ${CMAKE_CURRENT_SOURCE_DIR}/generics
)

# Fontes da pasta app/
set(APP_SOURCES
        app/bd.c
        app/login.c
        app/demo.c
)

set(LITE_SOURCES
        lite/main_lite.c
)

# Fontes da pasta lib/
set(LIB_SOURCES
        lib/calendario.c
        lib/data.c
        lib/visual.c
)

# Fontes da pasta generics/
set(GENERICS_SOURCES
        generics/arvore.c
        generics/fila.c
        generics/lista_dupla.c
        generics/pilha.c
)

# Fontes da pasta modules/
set(MODULES_SOURCES
        modules/cadastros.c
        modules/cargas.c
        modules/entregas.c
)

# Executável final
add_executable(TFinal
        main.c
        ${APP_SOURCES}
        ${LIB_SOURCES}
        ${GENERICS_SOURCES}
        ${MODULES_SOURCES}
)

# Debug helpers
message(STATUS "Arquivos APP: ${APP_SOURCES}")
message(STATUS "Arquivos LIB: ${LIB_SOURCES}")
message(STATUS "Arquivos GENERICS: ${GENERICS_SOURCES}")
message(STATUS "Arquivos MODULES: ${MODULES_SOURCES}")
