//[¥Úº“ΩŸ…· III](https://leetcode-cn.com/problems/house-robber-iii/)
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int rob(TreeNode* root)
    {
        auto ret = dfs(root);
        return max(ret[0], ret[1]);
    }

    vector<int> dfs(TreeNode* root)
    {
        if (!root) return { 0 ,0 };

        auto ret1 = dfs(root->left);
        auto ret2 = dfs(root->right);

        return { root->val + ret1[1] + ret2[1], max(ret1[0], ret1[1]) + max(ret2[0], ret2[1]) };
    }
};