add_library(Bridge STATIC
  DDS.cpp
  Deal.cpp
)

target_link_libraries(Bridge INTERFACE
  "${DDS_LIBRARY}"
  LLVM
)
