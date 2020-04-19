.PHONY: all
all : seam

seam : seam.o
	g++ seam.o -o seam

seam.o : seam.cpp
	g++ -std=c++17 -c seam.cpp

.PHONY: clean
clean :
	@rm -f seam.o seam
