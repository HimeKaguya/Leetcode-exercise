//[µ¥´Ê²ð·Ö](https://leetcode-cn.com/problems/word-break/)
#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
using namespace std;

//class Solution 
//{
//public:
//    bool wordBreak(string s, vector<string>& wordDict)
//    {
//        auto wordDictSet = unordered_set <string>();
//        for (auto word : wordDict)
//        {
//            wordDictSet.insert(word);
//        }
//
//        //for (auto it = wordDictSet.begin(); it != wordDictSet.end(); ++it)
//        //{
//        //    cout << *it << endl;
//        //}
//
//        auto dp = vector <bool>(s.size() + 1);
//
//        dp[0] = true;
//
//        for (int i = 1; i <= s.size(); ++i)
//        {
//            for (int j = 0; j < i; ++j) 
//            {
//                string a = s.substr(j, i - j);
//                if (dp[j] && wordDictSet.find(a) != wordDictSet.end())
//                {
//                    dp[i] = true;
//                    break;
//                }
//            }
//        }
//        return dp[s.size()];
//    }
//};

class Solution
{
public:
    bool wordBreak(string s, vector<string>& wordDict)
    {
        vector<bool> dp(s.size() + 1);
        dp[0] = true;
        for (int i = 1; i <= s.size(); i++)
        {
            int left = i - 1;
            if (dp[left] == false) continue;
            for (int j = 0; j < wordDict.size(); j++) {
                if (s.substr(left, wordDict[j].size()) == wordDict[j]) {
                    dp[left + wordDict[j].size()] = true;
                }
            }
        }
        return dp[s.size()];
    }
};

int main()
{
    string s = "leetcode";
    vector<string>wordDict = { "leet", "code" };

    Solution* sol = new Solution;
    cout << sol->wordBreak(s, wordDict) << endl;
    delete sol;
    return 0;
}
