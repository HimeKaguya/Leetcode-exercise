//[еп╤овспРап](https://leetcode-cn.com/problems/is-subsequence/)
#include<iostream>
#include<string>
using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t)
    {
        int m = s.size();
        int n = t.size();
        int i = 0, j = 0;
        while (i < m && j < n)
        {
            if (s[i] == t[j])
                i++;
            j++;
        }
        return i == m;
    }
};

int main()
{
    string s = "ace";
    string t = "aacsbegg";
    Solution* sol = new Solution;
    cout << sol->isSubsequence(s, t) << endl;
    delete sol;
    return 0;
}