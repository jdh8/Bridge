Bridge
======
Bridge library and utility in clean C++20.

## Dependencies ##
- [DDS][dds], the double-dummy solver
- [Eigen][eigen], for efficient statistics

## Building ##
[CMake][cmake] is used to automate build.  The building instruction is similar
to other CMake-automated projects.

```sh
mkdir build
cd build
cmake ..
make -j8
```

[cmake]: https://cmake.org/
[dds]: https://github.com/dds-bridge/dds
[eigen]: https://gitlab.com/libeigen/eigen
