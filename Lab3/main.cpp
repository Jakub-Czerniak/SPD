#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <queue>
#include <chrono>

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

 std::pair<int,std::vector<int>> neh(int processTable[500][20], int taskCount, int machineCount)
{
    int cmaxTable[501][21];
    std::vector <int> order;
    std::vector <int> tempOrder;
    std::pair <int, std::vector<int>> result;
    std::priority_queue <std::pair<int,int>, std::vector<std::pair<int, int>>, myComp> weightedTasks;
    int cmax, min, minPos, weight, taskID = 0;


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

    result=std::make_pair(cmaxTable[order[taskCount-1]][machineCount], order);
    
    return result;
}

std::pair<int,std::vector<int>> qneh(int processTable[500][20], int taskCount, int machineCount)
{
    int cmaxTable[501][21];
    int cmaxTableBackward[501][21];
    int tempCmax[20];
    std::vector <int> order;
    std::pair <int, std::vector<int>> result;
    std::priority_queue <std::pair<int,int>, std::vector<std::pair<int, int>>, myComp> weightedTasks;
    int cmax, min, minPos, weight, taskID = 0;


    for(int i=0;i<=taskCount;i++)
        cmaxTable[i][0]=0;
    for(int i=0;i<=machineCount;i++)
        cmaxTable[0][i]=0;

    for(int i=0;i<=taskCount;i++)
        for(int j=0;j<=machineCount;j++)
            cmaxTableBackward[i][j]=0;
      
        
    for(int task = 1; task<=taskCount; task++)
    {
        weight=0;
        for(int mc=1; mc<=machineCount; mc++)
        {
            weight+=processTable[task-1][mc-1];
        }
        weightedTasks.push(std::make_pair(weight,task));
    }
    order.push_back(0);
    order.push_back(weightedTasks.top().second);
    weightedTasks.pop();
    order.push_back(0);
    for (int task = 1; task< taskCount; task++)
    {
        min=INT32_MAX;
        taskID=weightedTasks.top().second;
        weightedTasks.pop();
        for(int i = 1; i <= task; i++)
            for(int mc = 1; mc <= machineCount; mc++)      
                cmaxTable[ order[i] ][mc] = std::max(cmaxTable[ order[i-1] ][mc],cmaxTable[ order[i] ][mc-1]) + processTable[order[i]-1][mc-1];
        for(int i = task; i > 0 ; i--)
            for(int mc = machineCount; mc > 0 ; mc--)      
                cmaxTableBackward[ order[i] ][mc-1] = std::max(cmaxTableBackward[ order[i+1] ][mc-1],cmaxTableBackward[ order[i] ][mc]) + processTable[order[i]-1][mc-1];
        for(int pos=0;pos<=task;pos++ )
        {
            tempCmax[0]= cmaxTable[ order[pos] ][ 1 ] + processTable[taskID-1][0];
            
            for(int mc=1;mc<machineCount;mc++)
                tempCmax[mc]= std::max(cmaxTable[order[pos]][mc+1],tempCmax[mc-1]) + processTable[taskID-1][mc];
            for(int mc=0; mc<machineCount; mc++)
                cmax= std::max(cmax , cmaxTableBackward[ order[pos+1] ][mc] + tempCmax[mc] );
            if(cmax<min)
            {
                minPos=pos+1;
                min=cmax;
            }  
            cmax=0;        
        }    
        order.insert(order.begin()+minPos,taskID);
    }
    order.erase(order.begin());
    order.pop_back();

    result=std::make_pair(min,order);  

    return result;
}


int main()
{
    int dataCount, taskCount, machineCount, nehTime, qnehTime, nehAbsoluteTime, qnehAbsoluteTime = 0;
    int processTable[500][20];
    std::pair <int, std::vector<int>> result;
    std::chrono::_V2::system_clock::time_point start,stop;
    std::chrono::microseconds duration;

    std::ifstream inputStream{"data.txt"};

    inputStream >> dataCount;

    for(int dt=0; dt<=dataCount; dt++)
    {
        inputStream >> taskCount;
        inputStream >> machineCount;
        for(int task = 0; task<taskCount; task++)
            for(int mc=0; mc<machineCount; mc++)
                inputStream >> processTable[task][mc];
        std::cout << "NEH data" << dt <<std::endl;
        start = std::chrono::high_resolution_clock::now();
        result=neh(processTable,taskCount,machineCount);
        stop = std::chrono::high_resolution_clock::now(); 
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        nehTime=duration.count();
        for (int i: result.second)
                std::cout << i << ' ';
        std::cout << std::endl;
        std::cout << "MinCmax: " << result.first << std::endl;
        std::cout << "Czas trwania: " << nehTime << std::endl << std::endl;
        nehAbsoluteTime+=nehTime;


        std::cout << "QNEH data" << dt <<std::endl;
        start = std::chrono::high_resolution_clock::now();
        result=qneh(processTable,taskCount,machineCount);
        stop = std::chrono::high_resolution_clock::now(); 
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        qnehTime=duration.count();
        for (int i: result.second)
                std::cout << i << ' ';
        std::cout << std::endl;
        std::cout << "MinCmax: " << result.first << std::endl;
        std::cout << "Czas trwania: " << qnehTime << std::endl << std::endl;
        qnehAbsoluteTime+=qnehTime;
    }

    std::cout<< "Calkowity czas trwanie neh: "<< nehAbsoluteTime << " mikrosekund." <<std::endl;
    std::cout<< "Calkowity czas trwanie qneh: "<< qnehAbsoluteTime << " mikrosekund."<<std::endl;
    
    return 0;
}