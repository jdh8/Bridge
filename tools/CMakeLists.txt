add_executable(generate generate.cpp)
target_link_libraries(generate PRIVATE Bridge "${DDS_LIBRARY}" LLVM)
