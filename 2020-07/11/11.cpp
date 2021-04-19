//[计算右侧小于当前元素的个数](https://leetcode-cn.com/problems/count-of-smaller-numbers-after-self/)
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//模拟排序
class Solution1 {
public:
	vector<int> countSmaller(vector<int>& nums) {
		if (nums.empty()) return {};
		if (nums.size() == 1) return { 0 };
		/*用于保存结果的数组*/
		vector<int> counts(nums.size(), 0);
		/*建立一个保持排序的数组*/
		vector<int> sort_nums;

		sort_nums.push_back(nums[nums.size() - 1]);
		size_t i = nums.size() - 2;
		do {
			/*通过lower_bound()二分寻找下界，返回一个迭代器(也就是相对于sorted_num的index)*/
			auto it = lower_bound(sort_nums.begin(), sort_nums.end(), nums[i]);
			/*通过排序数组的二分查找性质，我们可以知道iter-sorted_num.begin()(可以理解成sorted_num数组的起始位置)就是
			题目需要的比nums[i]小的数字个数*/
			counts[i] = it - sort_nums.begin();
			/*这时nums[i]已经使用完了，需要给以后的数字拿来判断
			插入后要保持sorted_num排序，所以nums[i]插入到iter位置*/
			sort_nums.insert(it, nums[i]);
		} while (i-- != 0);

		return counts;
	}

};

//二叉搜索树
struct BSTNode {
    int val;
    int count;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int x)
        : val(x)
        , left(NULL)
        , right(NULL)
        , count(0)
    {}
};
/*建立一个二分查找树，每个树结点有四个值,分别是:
 int val;这个结点代表的值val
 int count;这个val代表的次数也就是在nums数组种比val小的数的个数
 left 左子树指针
 right 右子树指针
 一个构造函数，构造函数如上定义
 */

void BST_insert(BSTNode* node, BSTNode* insert_node, int& count_small)
{
    if (node->val >= insert_node->val)
    {
        /*插入的结点更小,被比较结点(即node)的count++，然后插入到左子树(如果不为空)*/
        node->count++;
        if (node->left)
        {
            BST_insert(node->left, insert_node, count_small);
        }
        else
        {
            /*左子树为空，插入结点就作为当前结点的左孩子*/
            node->left = insert_node;
        }
    }
    else {
        /*插入的结点更大，需要在右子树(如果不为空)继续找*/
        count_small += node->count + 1;
        if (node->right)
        {
            BST_insert(node->right, insert_node, count_small);
        }
        else
        {
            /*当前右子树为空，插入结点作为当前结点右孩子*/
            node->right = insert_node;
        }
    }
}
/*count_small作为一个引用的参数，在递归寻找子树的时候作为一个“类似全局变量”的存在*/


class Solution2 {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        /*如果数组为空返回空值*/
        if (n == 0)return {};
        vector<int> count;
        count.push_back(0);
        /*建立一个二叉搜素树*/
        BSTNode* node = new BSTNode(nums[n - 1]);
        int count_small;
        for (int i = 1; i < n; i++)
        {
            count_small = 0;
            BST_insert(node, new BSTNode(nums[n - i - 1]), count_small);
            count.push_back(count_small);
        }
        /*最后不要忘记删除树节点*/
        delete node;
        reverse(count.begin(), count.end());
        /*push_back的时候是逆序的，此时只要将count数组reverse即可*/
        return count;
    }
};

//归并排序
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int>count;//保存结果
        vector<pair<int, int> > num;//关联每个数和它的序号
        for (int i = 0; i < nums.size(); ++i)
        {
            count.push_back(0);
            num.push_back(make_pair(nums[i], i));//保存每个数和它在原数组中的序号，以免在排序过程中打乱顺序
        }
        merge_sort(num, count);
        return count;
    }

    //归并排序
    void merge_sort(vector<pair<int, int> >& vec, vector<int>& count)
    {
        if (vec.size() < 2)
            return;

        int mid = vec.size() / 2;
        vector<pair<int, int> > sub_vec1;
        vector<pair<int, int> > sub_vec2;
        for (int i = 0; i < mid; ++i)
            sub_vec1.push_back(vec[i]);
        for (int i = mid; i < vec.size(); ++i)
            sub_vec2.push_back(vec[i]);

        merge_sort(sub_vec1, count);
        merge_sort(sub_vec2, count);
        vec.clear();
        merge(sub_vec1, sub_vec2, vec, count);
    }

    //合并两数组
    void merge(vector<pair<int, int> >& sub_vec1, vector<pair<int, int> >& sub_vec2, vector<pair<int, int> >& vec, vector<int>& count)
    {
        int i = 0;
        int j = 0;
        while (i < sub_vec1.size() && j < sub_vec2.size())
        {
            if (sub_vec1[i].first <= sub_vec2[j].first)
            {
                vec.push_back(sub_vec1[i]);
                count[sub_vec1[i].second] += j;//这句话和下面注释的地方就是这道题和归并排序的主要不同之处
                i++;
            }
            else {
                vec.push_back(sub_vec2[j]);
                j++;
            }
        }

        for (; i < sub_vec1.size(); ++i)
        {
            vec.push_back(sub_vec1[i]);
            count[sub_vec1[i].second] += j;// -。-
        }
        for (; j < sub_vec2.size(); ++j)
        {
            vec.push_back(sub_vec2[j]);
        }
    }
};


