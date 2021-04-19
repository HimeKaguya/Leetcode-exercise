//[最接近三数之和](https://leetcode-cn.com/problems/3sum-closest/)
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;

const int target = 1;
vector<int> nums = { -1,2,1,-4 };
int main()
{
    sort(nums.begin(), nums.end());
    int m = nums[0] + nums[1] + nums[2];
    for (int i = 0; i < nums.size() - 2; i++)
    {
        int j = i + 1;
        int k = nums.size() - 1;
        while (j < k)
        {
            int trisum = nums[i] + nums[j] + nums[k];
            if (trisum == target)
            {
                cout << target << endl;
                return 0;
            }
            if (abs(trisum - target) < abs(m - target)) m = trisum;
            else if (trisum < target) j++;
            else k--;
        }
    }
    cout << m << endl;
    return 0;
}