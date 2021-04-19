//[������](https://leetcode-cn.com/problems/burst-balloons/)
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        // "������dp[start][end]��ʾ��start��end֮����������֮���ܵõ������ֵ"
        // �����start��end�ǲ��ᱻ�����ģ�Ҳ����һ��start��end�Ŀ�����

        // transition eqn : 
        // dp[start][end] = dp[start][i] + dp[i][end] + nums[start] * nums[i] * nums[end]

        const int numSize=nums.size();

        // ǰ�����������ڱ���������ԭ��������߾Ͳ���Ҫ��������
        // �������г��õļ���
        nums.insert(nums.begin(), 1);
        nums.insert(nums.end(), 1);

        // ��Ϊ���������������Գ��ȱ����numSize + 
        //int** dp = new int* [numSize + 2];
        //for (int i = 0; i < numSize + 2; ++i)
        //    dp[i] = new int[numSize + 2];
        vector<vector<int>>dp(numSize + 2, vector<int>(numSize + 2, 0));

        // ���ﵹ�ű�������Ϊ��transition eqn�ܿ�����������ÿ����Ҫ���Ǻ����ֵ
        // Ҳ����dp[start][i]��dp[i][end]��������Ҫstart֮ǰ��ֵ
        for (int start = numSize + 1; start >= 0; --start) {
            for (int end = start; end < numSize + 2; ++end) {
                // ��������������������������Ǿͱ����
                if (end - start < 2) { dp[start][end] = 0; continue; }

                for (int i = start + 1; i < end; ++i)
                    dp[start][end] =
                    max(dp[start][end],
                        dp[start][i] + dp[i][end] + nums[start] * nums[i] * nums[end]);
            }
        }

        // return��ʱ���ȡ��������0��������ò������������ڱ���
        return dp[0][numSize + 1];
    }
};

int main()
{
    vector<int> num = { 3,1,5,8 };
    Solution* sol = new Solution;
    cout << sol->maxCoins(num) << endl;
    delete sol;
    return 0;
}