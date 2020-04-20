#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>
#include "readFile.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
        std::cout <<"Wrong format! Should be \"./seam file.pgm\"" <<std::endl;
    else
    {

        std::string filename = argv[1];
        PGM image(filename);
        image.setCriticalValues();
        image.readPGM();
        image.printVector();

    }

    return 0;
}
