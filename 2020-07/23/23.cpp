//[最小路径和](https://leetcode-cn.com/problems/minimum-path-sum/)
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        //dp[i][j]表示从起点到(i, j)的路径的最小和
        vector<vector<int>> dp(m, vector<int>(n, 0));
        //初始化边界
        dp[0][0] = grid[0][0];
        for (int i = 1; i < m; i++) { //第一列
            dp[i][0] = grid[i][0] + dp[i - 1][0];
        }
        for (int i = 1; i < n; i++) { //第一行
            dp[0][i] = grid[0][i] + dp[0][i - 1];
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                //用上方或者左边和较小的更新当前dp
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        return dp[m - 1][n - 1];
    }
};