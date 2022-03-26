#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

int main()
{   
    int time[100];
    int weight[100];
    int expected[100];
    int dataCount, taskCount, table_size, time_finished = 0;
    unsigned int temp, temp1=0;
    std::ifstream inputStream{"data"};
    inputStream >> dataCount;
    
    for (int dt=0; dt<dataCount; dt++)
    {
        inputStream >> taskCount;           
        for (int i = 0; i < taskCount; i++)
        {
            inputStream >> time[i];
            inputStream >> weight[i];
            inputStream >> expected[i];
        }
        table_size=pow(2,taskCount);
                std::vector<unsigned int> optimal[table_size];
        int table[table_size];
    

        table[0]=0;
        for(int i = 1; i<table_size; i++ )
        {
            time_finished=0;
            table[i]=INT32_MAX;
            for (unsigned int i2 = 0; i2 < taskCount; i2++)
            {
                temp = i;
                temp &= ~(1UL << i2);
                if(temp!=i)
                {
                    time_finished+=time[i2];
                }
            }
            
            for (unsigned int i2 = 0; i2 < taskCount; i2++)
            {
                temp = i;
                temp &= ~(1UL << i2);
                if(temp!=i)
                {
                    if(table[i]>(temp1=table[temp]+ std::max(0,weight[i2]*(time_finished-expected[i2]))))
                    {
                    table[i]=temp1;
                    optimal[i]=optimal[temp];
                    optimal[i].push_back(i2);
                    }
                }
            }
        }   
        std::cout << "data" << dt+10 <<std::endl;
        std::cout<< table[table_size-1] << std::endl; 
        for(int i: optimal[table_size-1])    
            std::cout << i+1 << ' ';
        std::cout<< std:: endl;
    }
    return 0;
}