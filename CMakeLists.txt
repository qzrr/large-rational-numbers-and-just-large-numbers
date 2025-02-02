cmake_minimum_required(VERSION 3.30)
project(coursework1)

set(CMAKE_CXX_STANDARD 20)

add_executable(coursework1 main.cpp
        List.cpp
        List.h
        BigNumber.cpp
        BigNumber.h
        BigRacNumber.cpp
        BigRacNumber.h)
