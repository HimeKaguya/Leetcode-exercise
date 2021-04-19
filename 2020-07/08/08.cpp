//[ÌøË®°å](https://leetcode-cn.com/problems/diving-board-lcci/)
#include<iostream>
#include<vector>
#include<set>
using namespace std;

class Solution1 {
public:
    vector<int> divingBoard(int shorter, int longer, int k)
    {
        set<int> l = {};
        for (int i = 0; i <= k && k != 0; i++)
        {
            l.insert(longer * i + shorter * (k - i));
        }
        return vector<int>(l.begin(), l.end());
    }
};

class Solution2 {
public:
    vector<int> divingBoard(int shorter, int longer, int k) {
        if (k == 0) {
            return vector<int>{};
        }
        if (shorter == longer) {
            return vector<int> {shorter* k};
        }
        vector<int> vec(k + 1);
        for (int i = 0; i <= k; i++) {
            vec[i] = (k - i) * shorter + i * longer;
        }
        return vec;
    }
};

int main()
{
    int shorter = 2, longer = 3, k = 4;
    Solution1* s1 = new Solution1;
    s1->divingBoard(shorter, longer, k);
    delete s1;
    Solution2* s2 = new Solution2;
    s2->divingBoard(shorter, longer, k);
    delete s2;
    return 0;
}