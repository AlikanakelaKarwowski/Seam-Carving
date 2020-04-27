#include "readFile.hpp"

PGM::PGM(std::string file, int vert, int hor)
{
    pgm.open(file);
    vertCount = vert;
    horCount = hor;
}

void PGM::setCriticalValues()
{
    std::stringstream ss;

    std::getline(pgm, pValue);

    std::getline(pgm, line);

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

void PGM::printVector(int i)
{
    if(i == 0)
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
    else if(i ==1)
    {
        for(auto i : eMatrix)
        {
            for(auto j : i)
                std::cout << j << " ";
            std::cout << std::endl;
        }
    }
    else if(i == 2)
    {
        for(auto i : cMatrix)
        {
            for(auto j : i)
                std::cout << j << " ";
            std::cout << std::endl;
        }
    }
}

void PGM::energyMatrix()
{
    eMatrix.clear();
    for(int row = 0; row < yValue; ++row)
    {
        std::vector<int> energyRow;
        for(int col = 0; col < xValue; ++col)
        {
            int energy = 0;

            //top left case
            if(row == 0 && col == 0)
                energy = abs(values[row][col] - values[row][col + 1]) + abs(values[row][col] - values[row + 1][col]);
            //top right case
            else if(row == 0 && col + 1 == xValue)
                energy = abs(values[row][col] - values[row+1][col]) + abs(values[row][col] - values[row][col-1]);
            //bot left case
            else if(row + 1 == yValue && col == 0)
                energy = abs(values[row][col] - values[row - 1][col]) + abs(values[row][col] - values[row][col + 1]);
            //bot right case
            else if(row + 1 == yValue && col + 1 == xValue)
                energy = abs(values[row][col] - values[row][col - 1]) + abs(values[row][col] - values[row - 1][col]);
            //left boundary case
            else if(col == 0)
                energy = abs(values[row][col] - values[row - 1][col]) + abs(values[row][col] - values[row + 1][col]) +
                    abs(values[row][col] - values[row][col + 1]);
            //right boundary case
            else if(col + 1 == xValue)
                energy = abs(values[row][col] - values[row][col - 1]) + abs(values[row][col] - values[row - 1][col]) +
                    abs(values[row][col] - values[row + 1][col]);
            //top boundary case
            else if(row == 0)
                energy = abs(values[row][col] - values[row][col - 1]) + abs(values[row][col] - values[row + 1][col]) +
                    abs(values[row][col] - values[row][col + 1]);
            //bot boundary case
            else if(row + 1 == yValue)
                energy = abs(values[row][col] - values[row][col - 1]) + abs(values[row][col] - values[row - 1][col]) +
                    abs(values[row][col] - values[row][col + 1]);
            //not a case
            else
                energy = abs(values[row][col] - values[row][col - 1]) + abs(values[row][col] - values[row + 1][col]) +
                    abs(values[row][col] - values[row][col + 1]) + abs(values[row][col] - values[row - 1][col]);

            energyRow.push_back(energy);
        }
        eMatrix.push_back(energyRow);
    }
}

void PGM::vCumEnergy()
{
    vMatrix.clear();
    for (int row = 0; row < yValue; ++row)
    {
        std::vector<int> cumRow;
        for (int col = 0; col < xValue; ++col)
        {
            // upper boundary case
            if (row == 0)
                cumRow.push_back(eMatrix[row][col]);
            // left boundary case
            else if (col == 0)
                cumRow.push_back(std::min(vMatrix[row - 1][col], vMatrix[row - 1][col + 1]) +
                    eMatrix[row][col]);
            // right boundary case
            else if (col + 1 == xValue)
                cumRow.push_back(std::min(vMatrix[row - 1][col], vMatrix[row - 1][col - 1]) +
                    eMatrix[row][col]);
            else // not a boundary case
            {
                cumRow.push_back(std::min(std::min(vMatrix[row - 1][col], vMatrix[row - 1][col - 1]),
                                           vMatrix[row - 1][col + 1]) + eMatrix[row][col]);
            }
        }
        vMatrix.push_back(cumRow);
        cumRow.clear();
    }
}

void PGM::removeVSeams()
{
    for (int num = 0; num < vertCount; ++num)
    {
        int row = yValue-1;

        energyMatrix();
        vCumEnergy();
        auto min_ele = std::min_element(vMatrix[row].begin(), vMatrix[row].end());
        auto iter = std::distance(vMatrix[row].begin(), min_ele);
        values[row].erase(values[row].begin() + iter);
        --row;
        
        for(; row !=1 ; --row)
        {
            min_ele = vMatrix[row].begin() + iter;

            if(min_ele != vMatrix[row].begin() || min_ele != vMatrix[row].end())
            {
                min_ele = std::min_element(min_ele - 1, min_ele + 1);
                iter = std::distance(vMatrix[row].begin(), min_ele);
                values[row].erase(values[row].begin()+iter);
            }
            else if(min_ele == vMatrix[row].begin())
            {
                min_ele = std::min_element(min_ele, min_ele + 1);
                iter = std::distance(vMatrix[row].begin(), min_ele);
                values[row].erase(values[row].begin()+iter);
            }
            else if(min_ele == vMatrix[row].end())
            {
                min_ele = std::min_element(min_ele - 1, min_ele);
                iter = std::distance(vMatrix[row].begin(), min_ele);
                values[row].erase(values[row].begin()+iter);
            }
        }
        std::cout << "Finished 1 iteration" <<std::endl;
    }
}
