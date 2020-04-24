#include "readFile.hpp"

void PGM::setCriticalValues()
{
    std::stringstream ss;

    std::getline(pgm, pValue);
    if(line[0] == '#')
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
    std::vector<int> gsLine;
    while(std::getline(pgm, line))
    {
        int tmp;
        if(line[0] !='#')
        {
            std::stringstream ss(line);
            while (ss >> tmp)
            {
                gsLine.push_back(tmp);
                ++xCounter;
                if(xCounter == xValue)
                {
                    xCounter = 0;
                    values.push_back(gsLine);
                    gsLine.clear();
                }
            }

        }
    }
}

void PGM::printVector()
{
    std::cout << pValue << std::endl;
    std::cout << xValue << " " << yValue<< std::endl;
    std::cout << grayscaleValue << std::endl;
    for(auto i : values)
    {
        for(auto j : i)
            std::cout << j << " ";
        std::cout << std::endl;
    }
}
