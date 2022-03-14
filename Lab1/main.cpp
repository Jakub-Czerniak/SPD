#include <chrono>
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator> 

#include "ProcessList.hpp"
#include "Solution.hpp"

using namespace std::chrono;

int main()
{
    int duration_whole=0;

    std::ifstream inputStream{"data1"};
    processList mainList=processList(inputStream);
    std::cout<<"data1"<<std::endl;
    auto start = high_resolution_clock::now();
    mainList.optimize();
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    duration_whole+=duration.count();
    //mainList.display();
    std::cout<< "Time spend on machine: "<<mainList.timeOnMachine()<<std::endl;

    std::ifstream inputStream2{"data2"};
    mainList=processList(inputStream2);
    std::cout<<"data2"<<std::endl;
    start = high_resolution_clock::now();
    mainList.optimize();
    stop = high_resolution_clock::now(); 
    duration = duration_cast<microseconds>(stop - start);
    duration_whole+=duration.count();
    //mainList.display();
    std::cout<< "Time spend on machine: "<<mainList.timeOnMachine()<<std::endl;

    std::ifstream inputStream3{"data3"};
    mainList=processList(inputStream3);
    std::cout<<"data3"<<std::endl;
    start = high_resolution_clock::now();
    mainList.optimize();
    stop = high_resolution_clock::now(); 
    duration = duration_cast<microseconds>(stop - start);
    duration_whole+=duration.count();
    //mainList.display();
    std::cout<< "Time spend on machine: "<<mainList.timeOnMachine()<<std::endl;

    std::ifstream inputStream4{"data4"};
    mainList=processList(inputStream4);
    std::cout<<"data4"<<std::endl;
    start = high_resolution_clock::now();    
    mainList.optimize();
    stop = high_resolution_clock::now(); 
    duration = duration_cast<microseconds>(stop - start);
    duration_whole+=duration.count();
    //mainList.display();
    std::cout<< "Time spend on machine: "<<mainList.timeOnMachine()<<std::endl;
    
    std::cout << std::endl;
    std::cout<< "Time spend on optimalization: " << duration_whole << " mikrosekund."<< std::endl;
}