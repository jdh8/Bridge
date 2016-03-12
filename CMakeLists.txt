set(CMAKE_CXX_STANDARD 11)

include_directories("include" "dds/include")

add_executable(generate src/generate.cpp)
target_link_libraries(generate dds)
