//[�ָ���������ֵ](https://leetcode-cn.com/problems/split-array-largest-sum/)
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//DP
class Solution1 {
public:
    int splitArray(vector<int>& nums, int m) {
        int n = nums.size();
        vector<long long> sum(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + nums[i - 1];
        }
        vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 2e18));
        for (int j = 0; j <= m; j++) dp[0][j] = 0;
        for (int i = 1; i <= n; i++) { // ö�������ĩβ
            for (int j = 1; j <= min(m, i); j++) { // ö�ٲ�ֵ�������ĸ���
                for (int k = j; k <= i; k++) {
                    dp[i][j] = min(dp[i][j], max(dp[k - 1][j - 1], sum[i] - sum[k - 1]));
                }
            }
        }
        return dp[n][m];
    }
};

//̰��
class Solution2 {
public:
    vector<int> nums;
    int m;
    int splitArray(vector<int>& nums, int m) {
        this->nums = nums;
        this->m = m;

        // ��һ������ָ����С�����Ժ���������
        // ��С�����ԣ�����һ��Ԫ��Ϊ���飬���ֵ������������Ԫ�� ��minSum��
        // �������ԣ����ָ����飬��ô����������ܺͣ�maxSum��
        // �𰸵Ŀ��н����������֮�У����Խ��ж�������
        // �����ᳬ��64��������ʵ���ϸ�Сһ�㣬��������44�Σ�log(10000*INT_MAX)��
        long long int minSum = 0, maxSum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            maxSum += nums[i];
            if (minSum < nums[i]) minSum = nums[i];
        }

        long long int mid; // , ans = maxSum;
        while (minSum < maxSum) {
            // ģ������ٷ���⻹����һ��min��ʵû��Ҫ
            // while������ȹٷ���������ж�== ����ѭ��������������left==right
            // ��Ϊ����ÿ��Ԫ�ر�����������min/maxֵһ���Ǵ�
            mid = (maxSum + minSum) / 2; // ���ﲻ�÷�ֹ����ˣ���ֵԶ����LL�ܱ�������ֵ
            if (possible(mid)) {  // ���ֲ���
                // ans = min(ans, mid); // �ٷ�������Ĳ���
                maxSum = mid; // ��ȹٷ��������-1
            }
            else {
                minSum = mid + 1;
            }
        }
        return maxSum;
    }

    bool possible(int guess) {
        // ̰���㷨��̫�����ˣ�
        // �����������飬�����֣�����guess�����ֺ�Ͷ�������������һ��
        // Ȼ�����count�������Ƿ��mС�����仰˵���Ǵճ�������ֵ���������������m��
        // ���С�Ļ���֤��guess̫���ˣ���Ҫ������ټ�����
        // �������guess̫С�ˣ����ұ߼�����
        long long int sum = 0;
        int count = 1;
        for (int i = 0; i < nums.size(); i++) {
            if (sum + nums[i] > guess) {
                ++count;
                sum = nums[i];
            }
            else {
                sum += nums[i];
            }
        }
        return count <= m;
    }
};

int main()
{
    vector<int> n = { 7,2,5,10,8 };
    int m = 2;
    Solution1* s1 = new Solution1;
    cout << s1->splitArray(n, m) << endl;
    delete s1;
    Solution2* s2 = new Solution2;
    cout << s2->splitArray(n, m) << endl;
    delete s2;
    return 0;
}