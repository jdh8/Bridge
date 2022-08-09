find_package(Eigen3 REQUIRED NO_MODULE)

add_executable(check-nltc check-nltc.cpp)
target_link_libraries(check-nltc PRIVATE Bridge Eigen3::Eigen)
