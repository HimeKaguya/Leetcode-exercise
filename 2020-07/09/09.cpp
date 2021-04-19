//[»Ö¸´¿Õ¸ñ](https://leetcode-cn.com/problems/re-space-lcci/)
#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
#include<algorithm>
#include<string_view>
using namespace std;
using namespace std;

class Solution {
public:
    int respace(vector<string>& dictionary, string sentence)
    {
        unordered_set<string> s;
        for (auto d : dictionary)
        {
            s.insert(d);
        }
        int n = sentence.size();
        auto dp = vector<int>(n + 1, 0);

        for (int i = 1; i <= n; i++)
        {
            dp[i] = dp[i - 1] + 1;
            for (int j = 1; j <= i; j++)
            {
                string sub = sentence.substr(j - 1, i - j + 1);
                if (s.find(sub) != s.end())
                    dp[i] = min(dp[i], dp[j - 1]);
            }
        }
        return dp[n];
    }
};

class Solution1 {
public:
    int respace(vector<string>& dictionary, string sentence) {
        unordered_set<string_view> s;
        for (const string& str : dictionary)
            s.insert(str);
        int n = sentence.size();
        vector<int> dp(n + 1);

        string_view sv(sentence);

        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1] + 1;
            for (int j = 1; j <= i; ++j) {
                string_view sub = sv.substr(j - 1, i - j + 1);
                if (s.find(sub) != s.end())
                    dp[i] = min(dp[i], dp[j - 1]);
            }
        }

        return dp[n];
    }
};


int main()
{
    vector<string> d = { "looked","just","like","her","brother" };
    string s = "jesslookedjustliketimherbrother";
    Solution1* sol = new Solution1;
    cout << sol->respace(d, s) << endl;
    delete sol;
    return 0;
}