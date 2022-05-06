#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <queue>

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
    std::priority_queue <std::pair<int,int>> weightedTasks;
    int dataCount, taskCount, machineCount, cmax, min, minTaskID, weight = 0;

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

        for(int task = 1; task<=taskCount; task++)
        {
            weight=0;
            for(int mc=1; mc<=machineCount; mc++)
            {
                weight+=processTable[task-1][mc-1];
            }
            weightedTasks.push(std::make_pair(weight,task));
        }

        //wyzeruj usedTask

        tempOrder.push_back(0);
        for(int i=0;i<=taskCount;i++)
            cmaxTable[i][0]=0;
        for(int i=0;i<=machineCount;i++)
            cmaxTable[0][i]=0;


        for (int task = 1; task<= taskCount; task++)
        {
            min=INT32_MAX;
            for (int taskID = 1; taskID <= taskCount; taskID++)
           {
                if(usedTaskID[taskID]==true)
                    continue;

                for(int it=1;it<=task;it++ )
                {
                    tempOrder.clear();
                    tempOrder.push_back(0);
                    tempOrder.insert(tempOrder.end(), order.begin(), order.end());
                    tempOrder.insert(tempOrder.begin()+it,taskID);

                    for (int i: tempOrder)
                        std::cout << i << ' ';
                    std::cout<<std::endl;

                    for(int i = 1; i <= task; i++)
                        for(int mc = 1; mc <= machineCount; mc++)      
                            cmaxTable[ tempOrder[i] ][mc] = std::max(cmaxTable[ tempOrder[i-1] ][mc],cmaxTable[ tempOrder[i] ][mc-1]) + processTable[tempOrder[i]-1][mc-1];

                    cmax= cmaxTable[tempOrder[task]][machineCount];
                    //std::cout<<"Cmax:"<<cmax<<std::endl;
                    if(cmax<min)
                    {
                        if(min!=INT32_MAX)
                            usedTaskID[minTaskID]=false;

                        minTaskID=taskID;
                        min=cmax;
                        usedTaskID[taskID]=true;
                    }            
                }   
            }   
            order.push_back(minTaskID);
        }

        
        for (int i: order)
            std::cout << i << ' ';
        std::cout << std::endl;
        std::cout << cmaxTable[order[taskCount-1]][machineCount] << std::endl;

        for(int task = 1; task<=taskCount; task++)
        {
            for(int mc=1; mc<=machineCount; mc++)
            {
                std::cout<<cmaxTable[order[task-1]][mc]<<" ";
            }
            std::cout<<std::endl;
        }
    }

    return 0;
}