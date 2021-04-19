//[最佳买卖股票时机含冷冻期](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)
#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int sold = 0, rest = 0, hold = INT_MIN;
        for (int p : prices) {
            int pre_sold = sold;
            sold = hold + p;
            hold = max(hold, rest - p);
            rest = max(rest, pre_sold);
        }
        return max(sold, rest);
    }
};

int main()
{
    vector<int> p = { 1,2,3,0,2 };
    Solution* sol = new Solution;
    cout << sol->maxProfit(p) << endl;
    delete sol;
    return 0;
}