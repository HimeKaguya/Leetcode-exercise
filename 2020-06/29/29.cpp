//[数组中的第K个最大元素](https://leetcode-cn.com/problems/kth-largest-element-in-an-array/)
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//class Solution 
//{
//public:
//    int findKthLargest(vector<int>& nums, int k)
//    {
//        sort(nums.rbegin(), nums.rend());
//        return nums[k - 1];
//    }
//};

//快速排序+选择
//class Solution {
//public:
//    int findKthLargest(vector<int>& nums, int k)
//    {
//        int low = 0, high = nums.size() - 1, mid = 0;
//        while (low <= high)
//        {
//            mid = partation(nums, low, high);
//            if (mid == k - 1) return nums[mid];
//            else if (mid > k - 1) high = mid - 1;
//            else low = mid + 1;
//        }
//        //  实际上返回 -1 代表没有第 k 大的数，这里不存在
//        return -1;
//    }
//
//    int partation(vector<int>& nums, int low, int high)
//    {
//        int left = low + 1, right = high;
//        swap(nums[low], nums[(low + high) / 2]);
//        int bound = nums[low];
//        //  双指针，快速排序，交换不符合条件的数据
//        while (left <= right) {
//            while (left < high && nums[left] >= bound) left++;
//            while (nums[right] < bound) right--;
//            if (left < right)
//                swap(nums[left++], nums[right--]);
//            else break;
//        }
//        //  将bound放到换分完成后的两个数组之间，作为边界, 返回bound的位次
//        swap(nums[low], nums[right]);
//        return right;
//    }
//};

//堆排序，调整，维护
class Solution {
public:
    void maxHeapify(vector<int>& a, int i, int heapSize) {
        int l = i * 2 + 1, r = i * 2 + 2, largest = i;
        if (l < heapSize && a[l] > a[largest]) {
            largest = l;
        }
        if (r < heapSize && a[r] > a[largest]) {
            largest = r;
        }
        if (largest != i) {
            swap(a[i], a[largest]);
            maxHeapify(a, largest, heapSize);
        }
    }

    void buildMaxHeap(vector<int>& a, int heapSize) {
        for (int i = heapSize / 2; i >= 0; --i) {
            maxHeapify(a, i, heapSize);
        }
    }

    int findKthLargest(vector<int>& nums, int k) {
        int heapSize = nums.size();
        buildMaxHeap(nums, heapSize);
        for (int i = nums.size() - 1; i >= nums.size() - k + 1; --i) {
            swap(nums[0], nums[i]);
            --heapSize;
            maxHeapify(nums, 0, heapSize);
        }
        return nums[0];
    }
};

int main()
{
    vector<int> nums = { 3,2,3,1,2,4,5,5,6 };
    int k = 4;
    Solution* sol = new Solution;
    cout << sol->findKthLargest(nums, k) << endl;
    delete sol;
    return 0;
}