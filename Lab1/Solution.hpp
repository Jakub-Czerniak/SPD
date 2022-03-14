#ifndef SOLUTION_HPP
#define SOLUTION_HPP


class Solution {
    public:
    void doWork(std::vector<int> &candidates, int index, std::vector<int> &current, int currentSum, int target, std::vector<int> &ans);
    std::vector<int> combinationSum(std::vector<int> &candidates, int target);
};

#endif