cmake_minimum_required(VERSION 3.16)

project(Bridge)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenMP)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} /Oi /Oy /GL /EHs /Wall")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -flto -march=native -pipe -Wall -Wextra -Wpedantic")
endif()

include_directories("include" "dds/include")

add_library(dds SHARED
    dds/src/ABsearch.cpp
    dds/src/ABstats.cpp
    dds/src/CalcTables.cpp
    dds/src/DealerPar.cpp
    dds/src/File.cpp
    dds/src/Init.cpp
    dds/src/LaterTricks.cpp
    dds/src/Memory.cpp
    dds/src/Moves.cpp
    dds/src/Par.cpp
    dds/src/PBN.cpp
    dds/src/PlayAnalyser.cpp
    dds/src/QuickTricks.cpp
    dds/src/Scheduler.cpp
    dds/src/SolveBoard.cpp
    dds/src/SolverIF.cpp
    dds/src/System.cpp
    dds/src/ThreadMgr.cpp
    dds/src/Timer.cpp
    dds/src/TimerGroup.cpp
    dds/src/TimerList.cpp
    dds/src/TimeStat.cpp
    dds/src/TimeStatList.cpp
    dds/src/TransTableL.cpp
    dds/src/TransTableS.cpp
    dds/src/dds.cpp
    dds/src/dump.cpp
)

add_executable(generate src/generate.cpp)
target_link_libraries(generate dds)
