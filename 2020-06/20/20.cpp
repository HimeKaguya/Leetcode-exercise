//[正则表达式匹配](https://leetcode-cn.com/problems/regular-expression-matching/)
#include<iostream>
#include<string>
using namespace std;
int i = 0;
bool match(const char* s, const char* p)
{
    if (!*p) return !*s;
    if (*(p + 1) != '*')
        return *s == *p || (*p == '.' && *s != '\0') ? match(s + 1, p + 1) : false;
    else
        return *s == *p || (*p == '.' && *s != '\0') ? match(s, p + 2) || match(s + 1, p) : match(s, p + 2);
}
bool isMatch(string s, string p)
{
    return match(s.data(), p.data());
}
int main()
{
    string s = "ab";
    string p = "a*";
    cout << isMatch(s, p) << endl;
    return 0;
}