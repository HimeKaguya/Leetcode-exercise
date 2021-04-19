//[两个数组的交集 II](https://leetcode-cn.com/problems/intersection-of-two-arrays-ii/)
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return intersect(nums2, nums1);
        }
        unordered_map <int, int> m;
        for (int num : nums1) {
            ++m[num];
        }
        vector<int> intersection;
        for (int num : nums2) {
            if (m.count(num)) {
                intersection.push_back(num);
                --m[num];
                if (m[num] == 0) {
                    m.erase(num);
                }
            }
        }
        return intersection;
    }
};

int main()
{
    vector<int> nums1 = { 1, 2, 2, 1 }; 
    vector<int> nums2 = { 2, 2 };
    Solution* sol = new Solution;
    sol->intersect(nums1, nums2);
    delete sol;
    return 0;
}