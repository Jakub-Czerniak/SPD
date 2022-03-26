#include <vector>
#include <algorithm>

#include "Solution.hpp"

//Zawartość tego pliku jest zmodyfikowaną przezemnie wersją, w celu zwracania tylko jednej odpowiedzi bez używania 
//dwa razy tej samej wartości, algorytmu rekurencyjnego CombinationSum 
    void Solution::doWork(std::vector<int> &candidates, int index, std::vector<int> &current, int currentSum, int target, std::vector<int> &ans) 
    {
        if (currentSum > target) {
            return;
        }
        if (currentSum == target || !ans.empty()) {
            if(ans.empty())
            ans=current;
            return;
        }
        for (int i = index; i < candidates.size(); i++) {
            if(i!=index)
            {
                current.push_back(candidates[i]);
                currentSum += candidates[i];
    
                doWork(candidates, i, current, currentSum, target, ans);
    
                current.pop_back();
                currentSum -= candidates[i];
            }
        }
    }

    std::vector<int> Solution::combinationSum(std::vector<int> &candidates, int target) 
    {
        std::vector<int> current; 
        std::vector<int> ans;
        sort(candidates.begin(), candidates.end());
        std::vector<int> uniqueCandidates;
        for (int i = 0; i < candidates.size(); i++) {
            if (i == 0 || candidates[i] != candidates[i-1]) {
                uniqueCandidates.push_back(candidates[i]);
            }
        }
        doWork(uniqueCandidates, 0, current, 0, target, ans); 
        return ans;
    }
