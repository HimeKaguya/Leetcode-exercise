//[��С·����](https://leetcode-cn.com/problems/minimum-path-sum/)
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
        //dp[i][j]��ʾ����㵽(i, j)��·������С��
        vector<vector<int>> dp(m, vector<int>(n, 0));
        //��ʼ���߽�
        dp[0][0] = grid[0][0];
        for (int i = 1; i < m; i++) { //��һ��
            dp[i][0] = grid[i][0] + dp[i - 1][0];
        }
        for (int i = 1; i < n; i++) { //��һ��
            dp[0][i] = grid[0][i] + dp[0][i - 1];
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                //���Ϸ�������ߺͽ�С�ĸ��µ�ǰdp
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        return dp[m - 1][n - 1];
    }
};