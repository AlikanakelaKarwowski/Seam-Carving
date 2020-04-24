#ifndef INCLUDE_READFILE_HPP
#define INCLUDE_READFILE_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>

class PGM
{
public:
    PGM(std::string file) {pgm.open(file);};

    void setCriticalValues();
    void readPGM();
    int getX() {return xValue;};
    int getY() {return yValue;};
    int getG() {return grayscaleValue;};
    void printVector();
private:
    int xValue = 0, yValue = 0, grayscaleValue = 0, xCounter = 0;
    std::string line, pValue;
    std::fstream pgm;
    std::vector<std::vector<int>> values;
};

#endif
