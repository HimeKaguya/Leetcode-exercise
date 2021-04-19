//[Õ®≈‰∑˚∆•≈‰](https://leetcode-cn.com/problems/wildcard-matching/)
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        s = ' ' + s;
        p = ' ' + p;
        int m = s.size();
        int n = p.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, false));
        dp[0][0] = true;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == p[j - 1] || p[j - 1] == '?')
                    dp[i][j] = dp[i - 1][j - 1];
                else if (p[j - 1] == '*')
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - 1] || dp[i][j - 1];
            }
        }
        return dp[m][n];
    }
};

int main()
{
    string s = "adceb";
    string p = "*a*b";
    Solution* sol = new Solution;
    cout << sol->isMatch(s, p) << endl;
    delete sol;
    return 0;
}