//[不同的二叉搜索树 II](https://leetcode-cn.com/problems/unique-binary-search-trees-ii/)
#include<iostream>
#include<vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
class Solution {
    vector<vector<vector<TreeNode*>> > memo;    //1 加上记忆化后果然好多了，可见真的重复计算了好多
public:
    vector<TreeNode*> generateTrees(int st, int ed) {
        // 边界条件
        vector<TreeNode*> ans;
        if (st > ed) return { NULL };
        if (!memo[st][ed].empty()) return memo[st][ed];  //4 记忆化代码
        // 递归代码
        for (int i = st; i <= ed; i++) {
            for (auto& l : generateTrees(st, i - 1)) {
                for (auto& r : generateTrees(i + 1, ed)) {
                    TreeNode* root = new TreeNode(i, l, r);
                    ans.push_back(root);
                }
            }
        }
        return memo[st][ed] = ans;        //3 记忆化添加得代码
    }
    vector<TreeNode*> generateTrees(int n) {
        memo.resize(n + 1, vector<vector<TreeNode*>>(n + 1));    //2 记忆化添加得代码
        if (n == 0) return {};
        return generateTrees(1, n);
    }
};