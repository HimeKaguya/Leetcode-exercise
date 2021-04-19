//[复原IP地址](https://leetcode-cn.com/problems/restore-ip-addresses/)
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Solution {
    int n;//原始串的长度
    vector<string> ans;//存放结果
    string ss;//存放原始串s,只不过s这个名字被用于backtrack函数中了，所以起新名字
    int idx;//ss的指针
    int num_dot;//串s中，已有的点号的个数

public:

    bool check(string m)
    {//判断一个数字字符，是否处于[0,255]之内
        int x = stoi(m);
        return x >= 0 && x <= 255;
    }

    void backtrack(string& s)
    {//当前传入的s，要么是空串，要么是以"."结尾的串。以.结尾时，ss可能已经耗尽
        if (idx > n - 1 && num_dot == 4)
        {//如果刚好4个“.”号，而且ss耗尽。删掉最后一个点号后加入答案。
            ans.push_back(s.substr(0, s.size() - 1));
            return;
        }
        else if (num_dot >= 4 && idx <= n - 1)
        {//说明不能构成一个合法的IP
            return;
        }

        //否则，添加1位，2位或者3位。添加之前，先要判断idx后面有没有这么多位
        vector<string> strs;

        for (int i = 0; i < 3; i++)
        {//第i个元素长度i+1
            //候选人
            string candidate = ss.substr(idx, i + 1);
            //注意如果长度为2或者3的时候，第1位不能为0，否则“01”这种，不可能出现在合法IP中，特判：
            if (i != 0 && candidate[0] == '0')continue;
            if (idx + i <= n - 1)strs.push_back(candidate);//候选人加入strs，有机会回溯了
        }

        for (int i = 0; i < strs.size(); i++)
        {//挨个回溯试试
            if (check(strs[i]))
            {
                s += (strs[i] + ".");//包含句号，总共加入了i+2位
                num_dot++;//多了一个句点
                idx += (i + 1);
                backtrack(s);
                num_dot--;
                idx -= (i + 1);
                //保留前s.size()-(i+2)位,去掉最后i+2位
                s = s.substr(0, s.size() - (i + 2));
            }
        }
        return;
    }

    vector<string> restoreIpAddresses(string s) {
        //回溯算法
        n = s.size();
        ans.clear();
        string path = "";
        ss = s;//ss代表最初的字符串
        idx = 0, num_dot = 0;

        backtrack(path);

        return ans;
    }
};

int main()
{
    string s = "25525511135";
    Solution* sol = new Solution;
    sol->restoreIpAddresses(s);
    delete sol;
    return 0;
}