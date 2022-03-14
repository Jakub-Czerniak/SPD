#include <chrono>
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator> 

#include "ProcessList.hpp"
#include "Solution.hpp"

int main()
{
    std::ifstream inputStream{"data2"};
    processList mainList=processList(inputStream);

    
    mainList.optimize();
    mainList.display();
    std::cout<<mainList.timeOnMachine()<<std::endl;
}