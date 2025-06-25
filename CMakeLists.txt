cmake_minimum_required(VERSION 3.31)
project(dylan_game_engine)

set(CMAKE_CXX_STANDARD 23)

add_executable(dylan_game_engine engine/src/main.cpp
        engine/src/main.cpp
        engine/src/core/Application.cpp
        engine/src/core/Application.h
)
