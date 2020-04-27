#ifndef INCLUDE_READFILE_HPP
#define INCLUDE_READFILE_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <iterator>

class PGM
{
public:
    PGM(std::string file, int vert, int hor);
    void printVector(int i);
    void setCriticalValues();
    void readPGM();
    void energyMatrix();
    void vCumEnergy();
    void removeVSeams();
    void carveVSeams(int minValue, int yValue);
    void write();

private:
    int xValue = 0, yValue = 0, grayscaleValue = 0, xCounter = 0, vertCount = 0, horCount = 0;
    std::string line, pValue, filename;
    std::fstream pgm;
    std::vector<std::vector<int>> values, eMatrix, cMatrix, vMatrix, hMatrix;

    void transpose();
};

#endif
