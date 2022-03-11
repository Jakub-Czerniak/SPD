#include "Solution.hpp"


    bool Solution::doWork(std::vector<int> &candidates, int index, std::vector<int> &current, int currentSum, int target, std::vector<int> &ans) 
    {
        if (currentSum > target) {
            return false;
        }
        if (currentSum == target) {
            ans=current;
            return true;
        }
        for (int i = index; i < candidates.size(); i++) {
            current.push_back(candidates[i]);
            currentSum += candidates[i];

            if(doWork(candidates, i, current, currentSum, target, ans)==true);
                return true;
            current.pop_back();
            currentSum -= candidates[i];
        }
    }

    std::vector<int> Solution::combinationSum(std::vector<int> &candidates, int target) 
    {
        std::vector<int> current; 
        std::vector<int> ans;
        std::sort(candidates.begin(), candidates.end());
        std::vector<int> uniqueCandidates;
        for (int i = 0; i < candidates.size(); i++) {
            if (i == 0 || candidates[i] != candidates[i-1]) {
                uniqueCandidates.push_back(candidates[i]);
            }
        }
        doWork(uniqueCandidates, 0, current, 0, target, ans); 
        return ans;
    }
