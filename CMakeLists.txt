cmake_minimum_required (VERSION 3.12+)

project(tarikh LANGUAGES C)

set(CMAKE_CXX_STANDARD 99)

add_executable(tarikh main.c)

install(TARGETS tarikh DESTINATION bin)
