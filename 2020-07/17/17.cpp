//[搜索插入位置](https://leetcode-cn.com/problems/search-insert-position/)
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int l = 0, r = nums.size();
        while (l < r) {
            int mid = (l + r) >> 1;
            if (nums[mid] == target) return mid; //最求简洁可以删除此行，追求时间可以加入此行
            nums[mid] < target ? l = mid + 1 : r = mid;
        }
        return l;
    }
};

int main()
{
    vector<int> nums = { 1,2,3,5,6 };
    int t = 4;
    Solution* sol = new Solution;
    cout << sol->searchInsert(nums, t) << endl;
    delete sol;
    return 0;
}