generate: dds *.hpp generate.cpp
	c++ -std=c++11 -Idds/include -Ldds/src -ldds -o generate generate.cpp
generate.exe: generate

dds:
	make -C dds/src
