//[Â·¾¶×ÜºÍ](https://leetcode-cn.com/problems/path-sum/)
#include<iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    int x = 0;
    int result = false;
public:
    bool hasPathSum(TreeNode* root, int sum) {
        deep(root, sum, x);
        return result;
    }
    void deep(TreeNode* root, int sum, int z) {
        if (root == NULL)
            return;
        z += root->val;
        if (root->left == NULL && root->right == NULL && z == sum)
            result = true;

        deep(root->left, sum, z);
        deep(root->right, sum, z);
    }
};

int main()
{
    int sum = 0;
    TreeNode root = TreeNode(0);
    Solution* sol = new Solution;
    cout << sol->hasPathSum(&root, sum) << endl;
    delete sol;
    return 0;
}