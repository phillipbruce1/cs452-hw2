cmake_minimum_required(VERSION 3.16)
project(cs452_hw2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cs452_hw2
        lawn.c
        lawn.h
        lawnimp.cc
        lawnimp.h
        linkage.h
        main.c
        mole.c
        mole.h)
