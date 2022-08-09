Bridge
======
Bridge library and utility in clean C++14.

## Dependencies ##
- [DDS][dds], the double-dummy solver
- [LLVM][llvm], for the command-line interface
- [Eigen 3][eigen], for the experiment to justify NLTC

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
[llvm]: https://github.com/llvm/llvm-project
[eigen]: https://gitlab.com/libeigen/eigen
