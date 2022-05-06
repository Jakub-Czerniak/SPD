#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

//bez akcerelacji n^3 * n
//akcerelacja obliczenie najdluzszej sciezki 3n^2*m


int cmaxCalculate(std::vector <int> order, int taskCount, int machineCount)
{
    int Cmax = 0;
    int cmaxTable[taskCount][machineCount];

    for(int task = 0; task<taskCount; task++)
        for(int mc = 0; mc<machineCount;mc++)
            cmaxTable[ order[task] ][mc] = std::max(cmaxTable[ order[task-1] ][mc],cmaxTable[ order[task] ][mc-1]);// + processTable[order[task]][mc];

    return cmaxTable[taskCount][machineCount];
}

int main()
{
    int processTable[500][20];
    int cmaxTable[501][21];
    bool usedTaskID[500];
    std::vector <int> order;
    std::vector <int> tempOrder;
    int dataCount, taskCount, machineCount, cmax, min = 0;  

    std::ifstream inputStream{"data.txt"};
    inputStream >> dataCount;
    dataCount=1;

    for(int dt=0; dt<dataCount; dt++)
    {
        inputStream >> taskCount;
        inputStream >> machineCount;
        std::cout<<taskCount<<std::endl;
        std::cout<<machineCount<<std::endl;
        for(int task = 0; task<taskCount; task++)
            for(int mc=0; mc<machineCount; mc++)
                inputStream >> processTable[task][mc];

        for(int task = 0; task<taskCount; task++)
        {
            for(int mc=0; mc<machineCount; mc++)
            {
                std::cout<<processTable[task][mc]<<" ";
            }
            std::cout<<std::endl;
        }


        tempOrder.push_back(0);
        for(int i=0;i<=taskCount;i++)
            cmaxTable[i][0]=0;
        for(int i=0;i<=machineCount;i++)
            cmaxTable[0][i]=0;


        for (int task = 1; task<= taskCount; task++)
        {
            min=INT32_MAX;
            tempOrder.clear();
            tempOrder.push_back(0);
            tempOrder.insert(tempOrder.end(), order.begin(), order.end());

            for (int taskID = 1; taskID <= taskCount; taskID++)
            {
                if(usedTaskID[taskID]!=true)
                {
                    if(taskID != 1)
                    {
                        tempOrder.clear();
                        tempOrder.push_back(0);                        
                    }
                    tempOrder.push_back(taskID);
                                        for (int i: tempOrder)
            std::cout << i << ' ';
                    //cmax = cmaxCalculate(order, task, machineCount);
                    //bool used_taskID[]
                    // if 0...

                    /*cmaxTable[0][0]=processTable[taskID][0];
                    for(int mc=1; mc<machineCount; mc++)
                        cmaxTable[0][mc]=cmaxTable[0][mc-1] + processTable[0][mc];

                    for(int i=1; i < task; i++)
                        cmaxTable[order[i]][0]=cmaxTable[order[i-1]][0] + processTable[order[i]][0];*/

                    for(int i = 1; i <= task; i++)
                        for(int mc = 1; mc <= machineCount; mc++)      
                        {                  
                            std::cout<<"Cmax order-1:"<<cmaxTable[ tempOrder[i-1] ][mc]<< " order: " << tempOrder[i]<<std::endl;
                            std::cout<<"Cmax mc -1 :"<<cmaxTable[ tempOrder[i] ][mc-1]<<" mc: " << mc <<std::endl;
                            std::cout<<"procTabl :"<<processTable[tempOrder[i]-1][mc-1]<<std::endl;
                            cmaxTable[ tempOrder[i] ][mc] = std::max(cmaxTable[ tempOrder[i-1] ][mc],cmaxTable[ tempOrder[i] ][mc-1]) + processTable[tempOrder[i]-1][mc-1];
                            std::cout<<"cmaxTable :"<<cmaxTable[ tempOrder[i] ][mc]<<std::endl;
                        }

                    cmax= cmaxTable[tempOrder[task]][machineCount];
                    std::cout<<"Cmax:"<<cmax<<std::endl;
                    if(cmax<min)
                    {
                        if(min!=INT32_MAX)
                        {
                            usedTaskID[order.back()]=false;
                            order.pop_back();
                        }
                        order.push_back(taskID);
                        min=cmax;
                        usedTaskID[taskID]=true;
                    }
                    else
                        order.pop_back();
                }
            }
        }

        
        for (int i: order)
            std::cout << i << ' ';
        std::cout << std::endl;
        std::cout << cmaxTable[taskCount-1][machineCount-1] << std::endl;

        for(int task = 1; task<=taskCount; task++)
        {
            for(int mc=1; mc<=machineCount; mc++)
            {
                std::cout<<cmaxTable[task][mc]<<" ";
            }
            std::cout<<std::endl;
        }
    }

    return 0;
}