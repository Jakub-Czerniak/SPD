#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <queue>

//bez akcerelacji n^3 * n
//akcerelacja obliczenie najdluzszej sciezki 3n^2*m


struct myComp {
    constexpr bool operator() (std::pair<int, int> const& a,std::pair<int, int> const& b) const noexcept
    {
        if(a.first!=b.first)
            return a.first < b.first;
        else
            return a.second > b.second;
    }
};

int main()
{
    int processTable[500][20];
    int cmaxTable[501][21];
    bool usedTaskID[500];
    std::vector <int> order;
    std::vector <int> tempOrder;
    std::priority_queue <std::pair<int,int>, std::vector<std::pair<int, int>>, myComp> weightedTasks;
    int dataCount, taskCount, machineCount, cmax, min, minPos, weight, taskID = 0;

    std::ifstream inputStream{"data.txt"};
    inputStream >> dataCount;
    dataCount=10;

    for(int dt=0; dt<dataCount; dt++)
    {
        inputStream >> taskCount;
        inputStream >> machineCount;
        for(int task = 0; task<taskCount; task++)
            for(int mc=0; mc<machineCount; mc++)
                inputStream >> processTable[task][mc];

        for(int task = 1; task<=taskCount; task++)
        {
            weight=0;
            for(int mc=1; mc<=machineCount; mc++)
            {
                weight+=processTable[task-1][mc-1];
            }
            weightedTasks.push(std::make_pair(weight,task));
        }


        tempOrder.push_back(0);
        for(int i=0;i<=taskCount;i++)
            cmaxTable[i][0]=0;
        for(int i=0;i<=machineCount;i++)
            cmaxTable[0][i]=0;

        for (int task = 1; task<= taskCount; task++)
        {
            min=INT32_MAX;

            taskID=weightedTasks.top().second;
            weightedTasks.pop();

            for(int pos=1;pos<=task;pos++ )
            {
                tempOrder.clear();
                tempOrder.push_back(0);
                tempOrder.insert(tempOrder.end(), order.begin(), order.end());
                tempOrder.insert(tempOrder.begin()+pos,taskID);

                for(int i = 1; i <= task; i++)
                    for(int mc = 1; mc <= machineCount; mc++)      
                        cmaxTable[ tempOrder[i] ][mc] = std::max(cmaxTable[ tempOrder[i-1] ][mc],cmaxTable[ tempOrder[i] ][mc-1]) + processTable[tempOrder[i]-1][mc-1];
                cmax= cmaxTable[tempOrder[task]][machineCount];

                if(cmax<min)
                {
                    minPos=pos-1;
                    min=cmax;
                }            
            }   
              
            order.insert(order.begin()+minPos,taskID);
        }

        for(int i = 0; i < taskCount; i++)
                    for(int mc = 1; mc <= machineCount; mc++)      
                        cmaxTable[ order[i] ][mc] = std::max(cmaxTable[ order[i-1] ][mc],cmaxTable[ order[i] ][mc-1]) + processTable[order[i]-1][mc-1];
                cmax=cmaxTable[order[taskCount-1]][machineCount];


        for (int i: order)
            std::cout << i << ' ';
        std::cout << std::endl;
        std::cout << cmaxTable[order[taskCount-1]][machineCount] << std::endl;

        order.clear();
        tempOrder.clear();
    }

    return 0;
}