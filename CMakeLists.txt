cmake_minimum_required(VERSION 3.20)
project(cnake)

set(CMAKE_C_STANDARD 99)

include_directories("${PROJECT_SOURCE_DIR}/lib")

add_executable(cnake main.c)

file(GLOB LIBS
        lib/*.lib)

target_link_libraries(cnake ${LIBS})
message(fuck)