cmake_minimum_required(VERSION 3.16)

project(Bridge)

set(CMAKE_CXX_STANDARD 20)
set(DDS_SRC_DIR "" CACHE PATH "Built source directory of DDS")

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_library(DDS_LIBRARY dds "${DDS_SRC_DIR}/src" REQUIRED)
find_package(Boost REQUIRED container)
find_package(Eigen3 REQUIRED NO_MODULE)

include_directories(
  "include"
  "${DDS_SRC_DIR}/include"
)

add_subdirectory(lib)
add_subdirectory(tools)
