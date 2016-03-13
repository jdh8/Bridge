cmake_minimum_required(VERSION 2.4)

set(CMAKE_CXX_STANDARD 11)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${OpenMP_CXX_FLAGS} /Oi /Oy /GL /EHs /Wall")
else()
    set(CMAKE_CXX_FLAGS "${OpenMP_CXX_FLAGS} -flto -march=native -pipe -Wall -Wextra -Wpedantic")
endif()

include_directories("include" "dds/include")

add_library(dds STATIC
    dds/src/dds.cpp
    dds/src/ABsearch.cpp
    dds/src/ABstats.cpp
    dds/src/CalcTables.cpp
    dds/src/DealerPar.cpp
    dds/src/Init.cpp
    dds/src/LaterTricks.cpp
    dds/src/Moves.cpp
    dds/src/Par.cpp
    dds/src/PlayAnalyser.cpp
    dds/src/PBN.cpp
    dds/src/QuickTricks.cpp
    dds/src/Scheduler.cpp
    dds/src/SolveBoard.cpp
    dds/src/SolverIF.cpp
    dds/src/Stats.cpp
    dds/src/Timer.cpp
    dds/src/TransTable.cpp
)

add_executable(generate src/generate.cpp)
target_link_libraries(generate dds)
