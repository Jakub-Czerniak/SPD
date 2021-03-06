#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

#include "ProcessList.hpp"
#include "Solution.hpp"


processList::processList()
{
    processCount=0;
}

processList::processList(std::istream& is)
{
    is >> processCount;

    processTimes= new int*[processCount];
    for(int i=0;i<processCount;i++)
        processTimes[i]=new int[3];
    for (int i = 0; i < processCount; i++)
        for (int j = 0; j < 3; j++)
            is>>processTimes[i][j];
}

processList::~processList()
{
    for(int i=0;i<processCount;i++)
        delete processTimes[i];
    //delete processTimes;
}

processList::processList(const processList& pL)
{
    processCount=pL.processCount;

    processTimes= new int*[processCount];
    for(int i=0;i<processCount;i++)
        processTimes[i]=new int[3];
    for (int i = 0; i < processCount; i++)
        for (int j = 0; j < 3; j++)
            processTimes[i][j]=pL.processTimes[i][j];

}


void processList::display()
{
    for(int i=0;i<processCount;i++)
    {
        for(int j=0;j<3;j++)
        {
            std::cout<<processTimes[i][j]<<" ";
        }
    std::cout<<std::endl;
    }
}

void processList::addLine(int a, int b, int c)
{   
    processCount++;

    int temp_matrix[processCount][3];
    for(int i=0;i<processCount-1;i++)
        for(int j=0;j<3;j++)
            temp_matrix[i][j]=processTimes[i][j];
    temp_matrix[processCount-1][0]=a;
    temp_matrix[processCount-1][1]=b;
    temp_matrix[processCount-1][2]=c;

    if(processCount>1)
    {
        for(int i=0;i<processCount-1;i++)
            delete processTimes[i];
        delete processTimes;
    }
    processTimes= new int*[processCount];
    for(int i=0;i<processCount;i++)
    {
        processTimes[i]=new int[3];
        for(int j=0;j<3;j++)
        processTimes[i][j]=temp_matrix[i][j];
    }
}

void processList::connect(processList front, processList middle, processList back)
{    


    for(int i=0;i<front.processCount;i++)
        for(int j=0;j<3;j++)
            this->processTimes[i][j]=front.processTimes[i][j];
    for(int i=0;i<middle.processCount;i++)
        for(int j=0;j<3;j++)
            this->processTimes[i+front.processCount][j]=middle.processTimes[i][j];
    for(int i=0;i<back.processCount;i++)
        for(int j=0;j<3;j++)
            this->processTimes[i+front.processCount+middle.processCount][j]=back.processTimes[i][j];
}

void processList::sortHighest(int column)
{
    int maximum=-1;
    int index_of_max=-1;
    int temp_vector[3];

    for(int j=0;j<processCount;j++)
    {
        for(int i=j;i<processCount;i++)
        {
            if(processTimes[i][column]>maximum)
            {
            index_of_max=i;
            maximum=processTimes[i][column];
            }
        }
        for(int k=0;k<3;k++)
        {
        temp_vector[k]=processTimes[index_of_max][k]; 
        processTimes[index_of_max][k]=processTimes[j][k];
        processTimes[j][k]=temp_vector[k];
        }
        maximum=-1;
    }
}

void processList::sortSmallest(int column)
{
    int minimum=INT32_MAX;
    int index_of_min=-1;
    int temp_vector[3];

    for(int j=0;j<processCount;j++)
    {
        for(int i=j;i<processCount;i++)
        {
            if(processTimes[i][column]<minimum)
            {
            index_of_min=i;
            minimum=processTimes[i][column];
            }
        }
        for(int k=0;k<3;k++)
        {
        temp_vector[k]=processTimes[index_of_min][k]; 
        processTimes[index_of_min][k]=processTimes[j][k];
        processTimes[j][k]=temp_vector[k];
        }
        minimum=INT32_MAX;
    }
}

void processList::optimize()
{
    Solution sol;
    processList front;
    processList middle;
    processList middle_front;
    processList middle_back;
    processList back;
    processList empty;
    std::vector<int> combination;
    bool equals=false;
    bool used[processCount]{};

    for(int i=0;i<processCount;i++)
    {
        if(processTimes[i][0]>processTimes[i][1] && processTimes[i][2]>processTimes[i][1]) 
        {
            middle.addLine(processTimes[i][0],processTimes[i][1],processTimes[i][2]);
            used[i]=true;
        }
        else if(processTimes[i][0]<processTimes[i][2])
        {
            front.addLine(processTimes[i][0],processTimes[i][1],processTimes[i][2]);
            used[i]=true;
        }
        else if(processTimes[i][0]>processTimes[i][2])
        {
            back.addLine(processTimes[i][0],processTimes[i][1],processTimes[i][2]);
            used[i]=true;
        }
        else if(processTimes[i][0]==processTimes[i][2])
        {
            combination.push_back(processTimes[i][1]);
            equals=true;
            /*if(i==0 || i==1 || i==3 || i==4 || i==5 || i==7 || i==8 || i==11 || i==12)
            front.addLine(processTimes[i][0],processTimes[i][1],processTimes[i][2]);
            else
            back.addLine(processTimes[i][0],processTimes[i][1],processTimes[i][2]);*/
        }
    }
    if(equals==true) //data2 alg
    {
        int sum_r=0;
        std::vector<int> result; 

        for(int i=0; i<middle.processCount ;i++)
                sum_r+=middle.processTimes[i][0]; //sum of all middle waiting times

        result=sol.combinationSum(combination, sum_r);
        if(!result.empty())
            for(int i=0;i<result.size();i++)
                for(int j=0; j<processCount ;j++)
                    if(result[i]==processTimes[j][1] && used[j]!=true)
                    {
                        front.addLine(processTimes[j][0],processTimes[j][1],processTimes[j][2]);
                        used[j]=true;
                    }       

            for(int j=0; j<processCount ;j++)
                if(used[j]!=true)
                {
                    back.addLine(processTimes[j][0],processTimes[j][1],processTimes[j][2]);
                }

    }

    for(int i=0;i<middle.processCount;i++)
    {
        if(middle.processTimes[i][0]<middle.processTimes[i][2])
        {
            middle_front.addLine(middle.processTimes[i][0],middle.processTimes[i][1],middle.processTimes[i][2]);
        }
        else if(middle.processTimes[i][0]>middle.processTimes[i][2])
        {
            middle_back.addLine(middle.processTimes[i][0],middle.processTimes[i][1],middle.processTimes[i][2]);
        }
    }

    front.sortSmallest(0);
    middle_front.sortSmallest(0);
    middle_back.sortHighest(2);
    back.sortHighest(2);    
    middle.connect(middle_front,middle_back,empty);
    this->connect(front,middle,back);
}


int processList::timeOnMachine()
{
    int i=0;
    bool finished, finished_b;

    if(processTimes[processCount-1][2]==0) //if the last cooling time is equal to zero the loop is executed with out doing anything
        i-=1;

    for(i;finished!=true ;i++)
    {
        finished_b=false;
        finished=true;
        for(int j=0;j<processCount;j++)
        {
            if(processTimes[j][0]!=0)
            {
            processTimes[j][0]-=1;
            finished=false;
            }
            else if(processTimes[j][1]!=0 && (j==0 || processTimes[j-1][1]==0) && finished_b==false)
            {
            processTimes[j][1]-=1;
            finished=false;
            finished_b=true;
            }
            if(processTimes[j][2]!=0 && processTimes[j][1]==0)
            {
            processTimes[j][2]-=1;
            finished=false;
            }            
        }
    }
        
    return i;
}
