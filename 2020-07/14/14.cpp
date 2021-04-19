//[��������С·����](https://leetcode-cn.com/problems/triangle/)
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle)
    {
        int n = triangle.size();
        vector<int> dp(n + 1, 0);  // ������һ�е���Сֵ
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 0; j < triangle[i].size(); j++) {
                dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
            }
        }
        return dp[0];
    }
};

