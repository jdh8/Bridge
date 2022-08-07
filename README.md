Bridge
======
Bridge library and utility in clean C++11.

## Dependency ##
[DDS][dds], the double-dummy solver, as a submodule.

## Build ##
[CMake][cmake] is used to automate build.  The building instruction is similar
to other CMake-automated projects.

```sh
mkdir build
cd build
cmake ..
make -j8
```

The executables are built then.

[cmake]: https://cmake.org/
[dds]: https://github.com/dds-bridge/dds
