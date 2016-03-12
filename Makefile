generate: dds include src/generate.cpp
	c++ -std=c++11 -Iinclude -Idds/include -Ldds/src -ldds -Wall -Wpedantic -o generate src/generate.cpp
generate.exe: generate

dds:
	make -C dds/src
