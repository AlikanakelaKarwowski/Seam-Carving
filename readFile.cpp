#include "readFile.hpp"

void PGM::setCriticalValues()
{
    std::stringstream ss;
    //ignore first 2 lines or file.
    pgm.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    pgm.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    //get the x and y values from the third line
    std::getline(pgm,line);
    ss << line;
    ss >> xValue >> yValue;

    //get the grayscaleValue from the fourth line
    std::getline(pgm,line);
    ss << line;
    ss >> grayscaleValue;
}

void PGM::readPGM()
{
    while(std::getline(pgm, line))
    {
        std::stringstream ss;
        std::vector<int> gsLine;
        int tmp = 0;
        ss << line;

        while (ss >> tmp)
            gsLine.push_back(tmp);

        values.push_back(gsLine);
    }
}

void PGM::printVector()
{
    for(auto i : values)
    {
        for(auto j : i)
            std::cout << j << " ";
        std::cout << std::endl;
    }
}
