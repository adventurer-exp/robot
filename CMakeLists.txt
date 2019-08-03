cmake_minimum_required(VERSION 3.14)
project(starter_code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(sampleTest)

add_executable(starter_code
        sampleTest/milestone2.initial
        sampleTest/milestone2.maze
        sampleTest/milestone2.pos
        sampleTest/path01.goal
        sampleTest/path01.initial
        sampleTest/path01.maze
        sampleTest/path01.path
        sampleTest/path01.pos
        PathPlanning.cpp
        PathPlanning.h
        PDList.cpp
        PDList.h
        PositionDistance.cpp
        PositionDistance.h
        Types.h
        unit_tests.cpp)
