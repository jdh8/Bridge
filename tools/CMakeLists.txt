add_executable(check-nltc check-nltc.cpp)
target_link_libraries(check-nltc PRIVATE Bridge Boost::program_options)
