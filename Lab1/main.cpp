#include "ProcessList.hpp"
#include "Solution.hpp"
#include <chrono>

int main()
{
    std::ifstream inputStream{"data2"};
    processList mainList=processList(inputStream);
    Solution Sol;
    std::vector vec={1,2,3,4,5,6,7};
    std::vector<int> ans;
            std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout<<std::endl;
    ans=Sol.combinationSum(vec,7);
                std::copy(ans.begin(), ans.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout<<std::endl;
    
    //mainList.optimize();
    //mainList.display();
    //td::cout<<mainList.timeOnMachine()<<std::endl;

}