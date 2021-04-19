//[长度最小的子数组](https://leetcode-cn.com/problems/minimum-size-subarray-sum/)
#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums)
    {
        int res = nums.size(), sum = 0, i = 0;
        for (int j = 0; j < nums.size(); j++)
        {
            sum += nums[j];
            while (sum >= s) { //指针i不断前进，temp不断减去nums[i]，直到小于s，则退出循环
                res = min(res, j - i + 1);
                sum -= nums[i++];
            }
        }
        return i == 0 ? 0 : res;
    }
};

int main()
{
    vector<int> nums = { 2,3,1,2,4,3 };
    int s = 7;
    Solution* sol = new Solution;
    cout << sol->minSubArrayLen(s, nums) << endl;
    delete sol;
    return 0;
}