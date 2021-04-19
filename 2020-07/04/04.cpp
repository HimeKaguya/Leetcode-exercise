//[最长有效括号](https://leetcode-cn.com/problems/longest-valid-parentheses/)
#include<iostream>
#include<string>
#include<algorithm>
#include<stack>
using namespace std;

//两次遍历，不占用额外空间
//class Solution {
//public:
//    int longestValidParentheses(string s) {
//        int left = 0, right = 0, maxlength = 0;
//        int n = s.size();
//        for (int i = 0; i < n; i++)
//        {
//            if (s[i] == '(') left++;
//            else right++;
//            if (left == right) maxlength = max(maxlength, right * 2);
//            else if (right > left) left = right = 0;
//        }
//        left = right = 0;
//        for (int i = n - 1; i >= 0; i--)
//        {
//            if (s[i] == '(') left++;
//            else right++;
//            if (left == right) maxlength = max(maxlength, left * 2);
//            else if (left > right) left = right = 0;
//        }
//        return maxlength;
//    }
//};

//栈
class Solution {
public:
    int longestValidParentheses(string s) {
        int maxlength = 0;
        int n = s.size();
        stack<int> st;
        st.push(-1);
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '(')   st.push(i);
            else
            {
                st.pop();
                if (st.empty()) st.push(i);
                else maxlength = max(maxlength, i - st.top());
            }
        }
        return maxlength;
    }
};

int main()
{
    string s = "(()()))((";
    Solution* sol = new Solution;
    cout << sol->longestValidParentheses(s) << endl;
    delete sol;
    return 0;
}