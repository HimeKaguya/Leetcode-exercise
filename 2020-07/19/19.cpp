//[戳气球](https://leetcode-cn.com/problems/burst-balloons/)
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        // "我们令dp[start][end]表示从start到end之间的气球戳破之后能得到的最大值"
        // 这里的start和end是不会被戳爆的，也就是一个start到end的开区间

        // transition eqn : 
        // dp[start][end] = dp[start][i] + dp[i][end] + nums[start] * nums[i] * nums[end]

        const int numSize=nums.size();

        // 前后补上两个“哨兵”，这样原数组的两边就不需要单独处理
        // 是链表中常用的技巧
        nums.insert(nums.begin(), 1);
        nums.insert(nums.end(), 1);

        // 因为补上了两个，所以长度变成了numSize + 
        //int** dp = new int* [numSize + 2];
        //for (int i = 0; i < numSize + 2; ++i)
        //    dp[i] = new int[numSize + 2];
        vector<vector<int>>dp(numSize + 2, vector<int>(numSize + 2, 0));

        // 这里倒着遍历，因为从transition eqn能看出来，我们每次需要的是后面的值
        // 也就是dp[start][i]和dp[i][end]，而不需要start之前的值
        for (int start = numSize + 1; start >= 0; --start) {
            for (int end = start; end < numSize + 2; ++end) {
                // 如果区间气球总数不够三个，那就别戳了
                if (end - start < 2) { dp[start][end] = 0; continue; }

                for (int i = start + 1; i < end; ++i)
                    dp[start][end] =
                    max(dp[start][end],
                        dp[start][i] + dp[i][end] + nums[start] * nums[i] * nums[end]);
            }
        }

        // return的时候就取最长，这里从0到最后正好不包含两个“哨兵”
        return dp[0][numSize + 1];
    }
};

int main()
{
    vector<int> num = { 3,1,5,8 };
    Solution* sol = new Solution;
    cout << sol->maxCoins(num) << endl;
    delete sol;
    return 0;
}