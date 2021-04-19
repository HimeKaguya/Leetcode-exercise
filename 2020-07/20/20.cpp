//[两数之和 II - 输入有序数组](https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/)
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target)
    {
        int n = numbers.size();
        int l = 0;
        int r = n - 1;
        vector<int> ans;
        while (numbers[l] + numbers[r] != target)
        {
            if (numbers[l] + numbers[r] >= target)
                r--;
            else
                l++;
        }
        ans.push_back(l + 1);
        ans.push_back(r + 1);
        return ans;
    }
};

int main()
{
    int t = 9;
    vector<int> n = { 2,7,11,15 };
    Solution* sol = new Solution;
    sol->twoSum(n,t);
    delete sol;
    return 0;
}