.PHONY: all
all : seam

seam : seam.o readFile.o
	g++ -std=c++17 seam.o readFile.o -o seam

seam.o : seam.cpp readFile.hpp
	g++ -std=c++17 -c seam.cpp

readFile.o : readFile.cpp
	g++ -std=c++17 -c readFile.cpp
.PHONY: clean
clean :
	@rm -f seam *.o
