#include <vector>
#include <queue>
#include <iostream>
#include <fstream>



struct smallestR{
constexpr bool operator() (std::pair<int, int> const& a,std::pair<int, int> const& b) const noexcept
    {
        if(a.first!=b.first)
            return a.first > b.first;
        else
            return a.second > b.second;
    }
};

struct biggestQ{
constexpr bool operator() (std::pair<int, int> const& a,std::pair<int, int> const& b) const noexcept
    {
        if(a.first!=b.first)
            return a.first < b.first;
        else
            return a.second < b.second;
    }
};

std::pair<int, std::vector<int>> schrage(int R[], int P[], int Q[], int taskCount)
{
    std::priority_queue <std::pair<int,int>, std::vector<std::pair<int, int>>, smallestR> smallestR_heap;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, biggestQ> biggestQ_heap;
    std::vector<int> order; 
    int C[taskCount];
    int t = 0, sRindex = 0, bQindex = 0, cmax=0;

    for(int i = 0; i<taskCount; i++)
        smallestR_heap.push(std::make_pair(R[i],i));

    while(!smallestR_heap.empty())
    {
        if(smallestR_heap.top().first<=t)
        {
            biggestQ_heap.push(std::make_pair(Q[smallestR_heap.top().second],smallestR_heap.top().second));
            smallestR_heap.pop();
        }
        else if(biggestQ_heap.empty())
            t=smallestR_heap.top().first;
        else
        {
        bQindex= biggestQ_heap.top().second;
        biggestQ_heap.pop();
        order.push_back(bQindex+1);
        t+=P[bQindex];   
        cmax=std::max(cmax,t+Q[bQindex]);  
        continue;    
        }

        while( !smallestR_heap.empty() && smallestR_heap.top().first <= t )
        {
            biggestQ_heap.push(std::make_pair( Q[ smallestR_heap.top().second ] , smallestR_heap.top().second) );
            smallestR_heap.pop();
        }
        bQindex= biggestQ_heap.top().second;

        biggestQ_heap.pop();
        order.push_back(bQindex+1);
        t+=P[bQindex];
        cmax=std::max(cmax,t+Q[bQindex]);
    }

    while(!biggestQ_heap.empty())
    {
        bQindex= biggestQ_heap.top().second;
        biggestQ_heap.pop();
        order.push_back(bQindex+1);
        t+=P[bQindex];
        cmax=std::max(cmax,t+Q[bQindex]);
    }

    return make_pair(cmax, order);
}



int schrageOpt(int R[], int P[], int Q[], int taskCount)
{
    std::priority_queue <std::pair<int,int>, std::vector<std::pair<int, int>>, smallestR> smallestR_heap;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, biggestQ> biggestQ_heap;
    int C[taskCount];
    int t = 0, sRindex = 0, bQindex = 0, cmax=0;

    for(int i = 0; i<taskCount; i++)
        smallestR_heap.push(std::make_pair(R[i],i));
   
    while(!smallestR_heap.empty())
    {   
        if(smallestR_heap.top().first<=t )
        {
            biggestQ_heap.push(std::make_pair(Q[smallestR_heap.top().second],smallestR_heap.top().second));
            smallestR_heap.pop();
        }
        else if(biggestQ_heap.empty())
            t=smallestR_heap.top().first;
        else
        {
        bQindex= biggestQ_heap.top().second;
        
        if(smallestR_heap.top().first > t+P[bQindex] )
        {
            t+=P[bQindex]; 
            biggestQ_heap.pop(); 
            cmax=std::max(cmax,t+Q[bQindex]);   
        }
        else
        {
            P[bQindex]-=smallestR_heap.top().first-t;
            t=smallestR_heap.top().first;
        }
        continue;    
        }

        while( !smallestR_heap.empty() && smallestR_heap.top().first <= t )
        {
            biggestQ_heap.push(std::make_pair( Q[ smallestR_heap.top().second ] , smallestR_heap.top().second) );
            smallestR_heap.pop();
        }
        bQindex= biggestQ_heap.top().second;
        if(smallestR_heap.top().first > t+P[bQindex] )
        {
            t+=P[bQindex]; 
            biggestQ_heap.pop(); 
            cmax=std::max(cmax,t+Q[bQindex]);   
        }
        else
        {
            P[bQindex]-=smallestR_heap.top().first-t;
            t=smallestR_heap.top().first;
        }
    }

    while(!biggestQ_heap.empty())
    {
        bQindex= biggestQ_heap.top().second;
        biggestQ_heap.pop();
        t+=P[bQindex];
        cmax=std::max(cmax,t+Q[bQindex]);
    }

    return cmax;
}



int main()
{
    int dataCount, taskCount;
    int R[50];
    int P[50];
    int Q[50];
    std::pair <int, std::vector<int>> result;
    int resultOpt;
    std::ifstream inputStream{"data.txt"};
    inputStream >> dataCount;
    dataCount=8;

    for(int i = 0; i<=dataCount; i++)
    {
        inputStream >> taskCount;
        for(int tC=0;tC<taskCount;tC++)
        {
            inputStream >> R[tC];
            inputStream >> P[tC];
            inputStream >> Q[tC];
        }
        result = schrage(R,P,Q,taskCount);
        resultOpt = schrageOpt(R,P,Q,taskCount);
        std::cout << "Schrage z wywlaszczaniem min Cmax: " << resultOpt << std::endl;
        std::cout << "Schrage min Cmax: " << result.first << std::endl;
        for (int i: result.second)
            std::cout << i << ' ';
        std::cout << std::endl;
    }


    return 0;
}