cmake_minimum_required(VERSION 3.29)
project(ProjetAllegro C)

set(CMAKE_C_STANDARD 11)

add_executable(ProjetAllegro main.c
        cold_rush.c
        cold_rush.h
        son1.c
        son1.h
        src/jeu.h
        src/jeu.c

)

target_link_libraries(ProjetAllegro -lmingw32 -lallegro-5.0.10-monolith-md-debug)

