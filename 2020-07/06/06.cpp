//[不同路径 II](https://leetcode-cn.com/problems/unique-paths-ii/)
#include<iostream>
#include<vector>
using namespace std;

class Solution1 {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        if (m == 0 || obstacleGrid[0][0] == 1)
            return 0;
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        // dp[1][1] = 1;
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == 1 && j == 1)
                    dp[i][j] = 1;
                else
                {
                    if (obstacleGrid[i - 1][j - 1] == 1)
                        dp[i][j] = 0;
                    else
                        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }
        return dp[m][n];
    }
};

class Solution2 {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
    {
        int m = obstacleGrid.size(), n = obstacleGrid.at(0).size();
        vector<int> dp(n);
        dp[0] = (obstacleGrid[0][0] == 0);
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (obstacleGrid[i][j] == 1)
                {
                    dp[j] = 0;
                    continue;
                }
                if (j - 1 >= 0) //第一列默认为0（obstacleGrid[i][j] = 0）或1（obstacleGrid[i][j] = 1）
                    //关键！相当于二维数组dp[i][j] = dp[i-1][j] + dp[i][j-1]
                    //dp[j] -> dp[i-1][j], dp[j-1] -> dp[i][j-1]
                    dp[j] += dp[j - 1];
            }
        }
        return dp[n - 1];
    }
};