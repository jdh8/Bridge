generate.exe: dds *.hpp generate.cpp
	c++ -std=c++11 -Idds/include -Ldds/src -ldds -o generate.exe generate.cpp

dds:
	make -C dds/src
