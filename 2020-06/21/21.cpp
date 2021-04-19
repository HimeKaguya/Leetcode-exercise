//[二叉树中的最大路径和](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/)
//Definition for a binary tree node.
#include<iostream>
#include <cstddef>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution
{
public:
    int maxPathSum(TreeNode* root)
    {
        get_max(root);
        return maxn_;
    }
private:
    int get_max(TreeNode* root)
    {
        if (!root) return 0;
        // 若左子树和比0小，则它取值=0，因为加上负数，最大值会变小
        int left_max = max(get_max(root->left), 0);
        // 右子树同理
        int right_max = max(get_max(root->right), 0);
        int new_path_sum = root->val + right_max + left_max;
        // 如果new_path_sum < maxn, 则最大路径不包括当前的root节点，只包括左（或右）节点
        maxn_ = max(maxn_, new_path_sum);
        // 最大和路径只能是左子树 or 右子树，不能同时选
        return root->val + max(left_max, right_max);
    }
    int maxn_ = INT_MIN;
};