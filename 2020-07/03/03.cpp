//[将有序数组转换为二叉搜索树](https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree/)
#include<iostream>
#include<vector>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
public:
    TreeNode* generate_tree(vector<int>& nums, int left, int right) {
        if (left > right)
            return NULL;
        int p = (left + right) / 2;
        TreeNode* root = new TreeNode(nums[p]);
        root->left = generate_tree(nums, left, p - 1);
        root->right = generate_tree(nums, p + 1, right);
        return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return generate_tree(nums, 0, nums.size() - 1);
    }
};

int main()
{
    vector<int> nums = { -10,-3,0,5,9 };
    Solution* sol = new Solution;
    cout << sol->sortedArrayToBST(nums) << endl;
    delete sol;
    return 0;
}