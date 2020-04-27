#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>
#include "readFile.hpp"

int main(int argc, char *argv[])
{
    if (argc != 4)
        std::cout <<"Wrong format! Should be \"./seam file.pgm vSeams hSeams\"" <<std::endl;
    else
    {

        std::string filename = argv[1], vert = argv[2], hor = argv[3];
        int iVert = std::stoi(vert), iHor = std::stoi(hor);
        PGM image(filename, iVert, iHor);
        image.setCriticalValues();
        image.readPGM();
        image.removeVSeams();
        image.write();
    }

    return 0;
}
