Bridge
======
Bridge library and utility in clean C++11.

## Dependency ##
[*The* double-dummy solver][dds] as a submodule.

## Build ##
[CMake][cmake] is used to automate build.  The building instruction is similar
to other CMake-automated projects.

First, choose a directory to build binaries e.g. `/path/to/build`.  I suggest
`/path/to/build` out of this repo (`/path/to/source`).  This eases updates as
git sees no generated files.

Next, <abbr title="change directory"><code>cd</code></abbr> to
`/path/to/build`; then execute

	cmake /path/to/source
	make

The executables are built then.

[cmake]: https://cmake.org/
[dds]: https://github.com/dds-bridge/dds
