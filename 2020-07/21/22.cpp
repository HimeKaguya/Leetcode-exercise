//[旋转数组的最小数字](https://leetcode-cn.com/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof/)
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int minArray(vector<int>& numbers) {
        int low = 0;
        int high = numbers.size() - 1;
        while (low < high) {
            int pivot = low + (high - low) / 2;
            if (numbers[pivot] < numbers[high]) {
                high = pivot;
            }
            else if (numbers[pivot] > numbers[high]) {
                low = pivot + 1;
            }
            else {
                high--;
            }
        }
        return numbers[low];
    }
};

int main()
{
    vector<int> n = { 7,11,15,2 };
    Solution* sol = new Solution;
    cout<<sol->minArray(n)<<endl;
    delete sol;
    return 0;
}