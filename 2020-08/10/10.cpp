//[计数二进制子串](https://leetcode-cn.com/problems/count-binary-substrings/)
#include<iostream>
#include<string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int countBinarySubstrings(string s) {
        int ptr = 0, n = s.size(), last = 0, ans = 0;
        while (ptr < n) {
            char c = s[ptr];
            int count = 0;
            while (ptr < n && s[ptr] == c) {
                ++ptr;
                ++count;
            }
            ans += min(count, last);
            last = count;
        }
        return ans;
    }
};

int main()
{
    string s = "01010";
    Solution* sol = new Solution;
    cout << sol->countBinarySubstrings(s) << endl;
    delete sol;
    return 0;
}