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

void neh(std::ifstream &inputStream)
{
    int processTable[500][20];
    int cmaxTable[501][21];
    std::vector <int> order;
    std::vector <int> tempOrder;
    std::priority_queue <std::pair<int,int>, std::vector<std::pair<int, int>>, myComp> weightedTasks;
    int dataCount, taskCount, machineCount, cmax, min, minPos, weight, taskID = 0;

    //std::ifstream inputStream{"data.txt"};
    inputStream >> dataCount;
    dataCount = 10;

    for(int dt=0; dt<=dataCount; dt++)
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

}

void qneh(/*std::ifstream &inputStream*/)
{
    int processTable[500][20];
    int cmaxTable[501][21];
    int cmaxTableBackward[501][21];
    int tempCmax[3];
    std::vector <int> order;
    std::priority_queue <std::pair<int,int>, std::vector<std::pair<int, int>>, myComp> weightedTasks;
    int dataCount, taskCount, machineCount, cmax, min, minPos, weight, taskID = 0;

    std::ifstream inputStream{"data.txt"};
    inputStream >> dataCount;
    dataCount=10;
      
    for(int dt=0; dt<=dataCount; dt++)
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

        order.push_back(0);
        order.push_back(weightedTasks.top().second);
        weightedTasks.pop();
        order.push_back(0);

        for(int i=0;i<=taskCount;i++)
            cmaxTable[i][0]=0;
        for(int i=0;i<=machineCount;i++)
            cmaxTable[0][i]=0;

        for(int i=0;i<=taskCount;i++)
            for(int j=0;j<=machineCount;j++)
                cmaxTableBackward[i][j]=0;

        for (int task = 1; task< taskCount; task++)
        {
            min=INT32_MAX;

            taskID=weightedTasks.top().second;
            //std::cout<<taskID<<std::endl;
            weightedTasks.pop();

            for(int i = 1; i <= task; i++)
                for(int mc = 1; mc <= machineCount; mc++)      
                    cmaxTable[ order[i] ][mc] = std::max(cmaxTable[ order[i-1] ][mc],cmaxTable[ order[i] ][mc-1]) + processTable[order[i]-1][mc-1];

            for(int i = task; i > 0 ; i--)
                for(int mc = machineCount; mc > 0 ; mc--)      
                    cmaxTableBackward[ order[i] ][mc-1] = std::max(cmaxTableBackward[ order[i+1] ][mc-1],cmaxTableBackward[ order[i] ][mc]) + processTable[order[i]-1][mc-1];
            //std::cout<<"cmax backward" << std::endl;
            /*for(int i = 0; i <=task ; i++)
            {
                for(int mc = 0; mc <= machineCount; mc++) 
                {
                    std::cout<<cmaxTableBackward[order[i]][mc]<< ' ' ;
                }
            std::cout<<std::endl;
            }*/

            for(int pos=0;pos<=task;pos++ )
            {
                tempCmax[0]= cmaxTable[ order[pos] ][ 1 ] + processTable[taskID-1][0];
                for(int mc=1;mc<machineCount;mc++)
                    tempCmax[mc]= std::max(cmaxTable[order[pos]][mc+1],tempCmax[mc-1]) + processTable[taskID-1][mc];
                //tempCmax[2]= std::max(cmaxTable[order[pos]][3],tempCmax[1]) + processTable[taskID-1][2];
                //std::cout<< tempCmax[0] <<" "<< tempCmax[1] <<" "<< tempCmax[2] <<" "<<std::endl;
                for(int mc=0; mc<machineCount; mc++)
                {
                    cmax= std::max(cmax , cmaxTableBackward[ order[pos+1] ][mc] + tempCmax[mc] );
                    //std::cout<< cmaxTableBackward[order[pos+1]][mc]<< " + "<< tempCmax[mc] <<std::endl;
                }
                //std::cout<<"cmaxss"<< cmax<<std::endl;
                if(cmax<min)
                {
                    minPos=pos+1;
                    min=cmax;
                }  
                cmax=0;          
            }   
            order.insert(order.begin()+minPos,taskID);
        }

        std::cout<<"min: "<<min<<std::endl;  
        //inputStream.close();
        for(int i=1; i<order.size()-1;i++)
          std::cout << order[i] << ' ';
        std::cout << std::endl;

        order.clear();
    }
}


int main()
{
    //std::ifstream inputStream{"data.txt"};
    qneh();
    return 0;
}