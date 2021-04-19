//[�������е����·����](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/)
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
        // ���������ͱ�0С������ȡֵ=0����Ϊ���ϸ��������ֵ���С
        int left_max = max(get_max(root->left), 0);
        // ������ͬ��
        int right_max = max(get_max(root->right), 0);
        int new_path_sum = root->val + right_max + left_max;
        // ���new_path_sum < maxn, �����·����������ǰ��root�ڵ㣬ֻ�����󣨻��ң��ڵ�
        maxn_ = max(maxn_, new_path_sum);
        // ����·��ֻ���������� or ������������ͬʱѡ
        return root->val + max(left_max, right_max);
    }
    int maxn_ = INT_MIN;
};