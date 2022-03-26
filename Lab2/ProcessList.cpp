#include <iostream>
#include <fstream>

#include "ProcessList.hpp"

processList::processList()
{
    processCount=0;
}

processList::processList(std::istream& is)
{
    is >> processCount;
    processData= new int*[processCount];
    for(int i=0;i<processCount;i++)
        processData[i]=new int[4];
    for (int i = 0; i < processCount; i++)
        for (int j = 0; j < 4; j++)
        {
            if(j==0)
            processData[i][j]=i;
            else
            is>>processData[i][j];
        }
}

processList::processList(const processList& pL)
{
    processCount=pL.processCount;

    processData= new int*[processCount];
    for(int i=0;i<processCount;i++)
        processData[i]=new int[4];
    for (int i = 0; i < processCount; i++)
        for (int j = 0; j < 4; j++)
            processData[i][j]=pL.processData[i][j];

}

processList::~processList()
{
    for(int i=0;i<processCount;i++)
        delete processData[i];
    //delete processData;
}


void processList::display()
{
    for(int i=0;i<processCount;i++)
    {
        for(int j=0;j<4;j++)
        {
            std::cout<<processData[i][j]<<" ";
        }
    std::cout<<std::endl;
    }
}

void processList::optimaze()
{

}

int processList::sumWiti()
{
    int sum=0, time=0;
    
    for(int i=0; i<processCount; i++)
    {
        time+=processData[i][2]
        sum+=processData[i][3]*

    }

    return sum;
}