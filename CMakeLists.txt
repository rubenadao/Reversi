cmake_minimum_required(VERSION 3.13)
project(Reversi C)

set(CMAKE_C_STANDARD 99)

add_executable(Reversi main.c estado.c estado.h game.c game.h stack.c stack.h file_manager.c file_manager.h linkedLists.c linkedLists.h validos.c validos.h minmax.c minmax.h)