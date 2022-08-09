add_library(Bridge STATIC
  DDS.cpp
  Deal.cpp
)

target_link_libraries(Bridge PUBLIC
  "${DDS_LIBRARY}"
  Eigen3::Eigen
)
