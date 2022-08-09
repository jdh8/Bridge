cmake_minimum_required(VERSION 3.16)

project(Bridge)

set(CMAKE_CXX_STANDARD 14)
set(DDS_SRC_DIR "" CACHE PATH "Built source directory of DDS")

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_library(DDS_LIBRARY dds "${DDS_SRC_DIR}/src" REQUIRED)

include_directories(
  "include"
  "${DDS_SRC_DIR}/include"
)

add_subdirectory(lib)
add_subdirectory(tools)
