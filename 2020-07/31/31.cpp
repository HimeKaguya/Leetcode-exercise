//[Ä§ÊõË÷Òý](https://leetcode-cn.com/problems/magic-index-lcci/)
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int findMagicIndex(vector<int>& nums)
    {
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            if (nums[i] == i) return i;
        }
        return -1;
    }
};

int main()
{
    vector<int> nums = { 0,2,4,6,8 };
    Solution* s = new Solution;
    cout << s->findMagicIndex(nums) << endl;
    delete s;
    return 0;
}