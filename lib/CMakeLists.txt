add_library(Bridge STATIC
  DDS.cpp
  Deal.cpp
)

target_link_libraries(Bridge PUBLIC
  "${DDS_LIBRARY}"
  Boost::container
  Eigen3::Eigen
)
