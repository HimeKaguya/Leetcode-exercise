//[³ýÊý²©ÞÄ](https://leetcode-cn.com/problems/divisor-game/)
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    bool divisorGame(int N) {
        if (N == 1) return false;
        if (N == 2) return true;
        vector<bool> dp(N + 1, false);
        dp[2] = true;
        for (int i = 3; i <= N; i++) {
            for (int j = 1; j < i; j++) {
                if (i % j == 0 && dp[i - j] == false) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[N];
    }
};

int main()
{
    int n = 7;
    Solution* sol = new Solution;
    cout << sol->divisorGame(n) << endl;
    delete sol;
    return 0;
}