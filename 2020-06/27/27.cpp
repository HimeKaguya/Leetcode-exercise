//[缺失的第一个正数](https://leetcode-cn.com/problems/first-missing-positive/)
#include<iostream>
#include<vector>
using namespace std;

//class Solution {
//public:
//    int firstMissingPositive(vector<int>& nums)
//    {
//        if (nums.size() == 0) return 1;
//        int min_n = nums[0];
//        for (int i = 0; i < nums.size(); i++)
//        {
//            if (nums[i] > 0 && nums[i] < min_n) min_n = nums[i];
//        }
//        if (min_n > 1) return 1;
//        else
//        {
//            for (int i = 1; i <= nums.size()+1; i++)
//            {
//                if (find(nums.begin(), nums.end(), i) == nums.end()) return i;
//            }
//        }
//        return 0;
//    }
//};

class Solution {
public:
    int firstMissingPositive(vector<int>& nums)
    {
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i])
            {
                swap(nums[nums[i] - 1], nums[i]);
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (nums[i] != i + 1) return i + 1;
        }
        return n + 1;
    }
};

int main()
{
    vector<int> nums = { 3,4,-1,1 };
    Solution* sol = new Solution;
    cout << sol->firstMissingPositive(nums) << endl;
    delete sol;
    return 0;
}