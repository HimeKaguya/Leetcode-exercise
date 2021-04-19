//[最长重复子数组](https://leetcode-cn.com/problems/maximum-length-of-repeated-subarray/)
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//DP
//class Solution {
//public:
//    int findLength(vector<int>& A, vector<int>& B) {
//        vector<int> dp(B.size() + 1, 0);
//        int result = 0;
//        for (int i = 0; i < A.size(); ++i) {
//            for (int j = B.size() - 1; j >= 0; --j) {
//                dp[j + 1] = A[i] == B[j] ? dp[j] + 1 : 0;
//                result = max(result, dp[j + 1]);
//            }
//        }
//        return result;
//    }
//};

//滑动窗口
class Solution {
public:
    int maxLength(vector<int>& A, vector<int>& B, int addA, int addB, int len) {
        int ret = 0, k = 0;
        for (int i = 0; i < len; i++) {
            if (A[addA + i] == B[addB + i]) {
                k++;
            }
            else {
                k = 0;
            }
            ret = max(ret, k);
        }
        return ret;
    }
    int findLength(vector<int>& A, vector<int>& B) {
        int n = A.size(), m = B.size();
        int ret = 0;
        for (int i = 0; i < n; i++) {
            int len = min(m, n - i);
            int maxlen = maxLength(A, B, i, 0, len);
            ret = max(ret, maxlen);
        }
        for (int i = 0; i < m; i++) {
            int len = min(n, m - i);
            int maxlen = maxLength(A, B, 0, i, len);
            ret = max(ret, maxlen);
        }
        return ret;
    }
};

int main()
{
    vector<int> A = { 1,2,3,2,1 };
    vector<int> B = { 3,2,1,4,7 };
    Solution* sol = new Solution;
    cout << sol->findLength(A, B) << endl;
    delete sol;
    return 0;
}