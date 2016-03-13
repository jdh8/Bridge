cmake_minimum_required(VERSION 2.9)

set(CMAKE_CXX_STANDARD 11)

include_directories("include" "dds/include")
link_directories("dds/src")

add_executable(generate src/generate.cpp)
target_link_libraries(generate dds)
