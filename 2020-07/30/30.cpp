//[�������](https://leetcode-cn.com/problems/integer-break/)
#include<iostream>
using namespace std;

class Solution {
public:
    int integerBreak(int n) {
        int mmax = 0, res = n % 3, les = n / 3; //����,����
        if (n <= 3) mmax = 1 * (n - 1);
        else {
            if (res == 0) mmax = pow(3, les); //���ֳ�2�����ֳ�3
            else if (res == 1) mmax = pow(3, les - 1) * 2 * 2; //�ֳ�2��2������Ϊ3
            else mmax = pow(3, les) * 2; //�ֳ�һ��2������Ϊ3
        }
        return mmax;
    }
};

int main()
{
    int n = 10;
    Solution* s = new Solution;
    cout << s->integerBreak(n) << endl;
    delete s;
    return 0;
}