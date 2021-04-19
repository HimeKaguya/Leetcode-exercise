//[�����Ҳ�С�ڵ�ǰԪ�صĸ���](https://leetcode-cn.com/problems/count-of-smaller-numbers-after-self/)
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//ģ������
class Solution1 {
public:
	vector<int> countSmaller(vector<int>& nums) {
		if (nums.empty()) return {};
		if (nums.size() == 1) return { 0 };
		/*���ڱ�����������*/
		vector<int> counts(nums.size(), 0);
		/*����һ���������������*/
		vector<int> sort_nums;

		sort_nums.push_back(nums[nums.size() - 1]);
		size_t i = nums.size() - 2;
		do {
			/*ͨ��lower_bound()����Ѱ���½磬����һ��������(Ҳ���������sorted_num��index)*/
			auto it = lower_bound(sort_nums.begin(), sort_nums.end(), nums[i]);
			/*ͨ����������Ķ��ֲ������ʣ����ǿ���֪��iter-sorted_num.begin()(��������sorted_num�������ʼλ��)����
			��Ŀ��Ҫ�ı�nums[i]С�����ָ���*/
			counts[i] = it - sort_nums.begin();
			/*��ʱnums[i]�Ѿ�ʹ�����ˣ���Ҫ���Ժ�����������ж�
			�����Ҫ����sorted_num��������nums[i]���뵽iterλ��*/
			sort_nums.insert(it, nums[i]);
		} while (i-- != 0);

		return counts;
	}

};

//����������
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
/*����һ�����ֲ�������ÿ����������ĸ�ֵ,�ֱ���:
 int val;����������ֵval
 int count;���val����Ĵ���Ҳ������nums�����ֱ�valС�����ĸ���
 left ������ָ��
 right ������ָ��
 һ�����캯�������캯�����϶���
 */

void BST_insert(BSTNode* node, BSTNode* insert_node, int& count_small)
{
    if (node->val >= insert_node->val)
    {
        /*����Ľ���С,���ȽϽ��(��node)��count++��Ȼ����뵽������(�����Ϊ��)*/
        node->count++;
        if (node->left)
        {
            BST_insert(node->left, insert_node, count_small);
        }
        else
        {
            /*������Ϊ�գ����������Ϊ��ǰ��������*/
            node->left = insert_node;
        }
    }
    else {
        /*����Ľ�������Ҫ��������(�����Ϊ��)������*/
        count_small += node->count + 1;
        if (node->right)
        {
            BST_insert(node->right, insert_node, count_small);
        }
        else
        {
            /*��ǰ������Ϊ�գ���������Ϊ��ǰ����Һ���*/
            node->right = insert_node;
        }
    }
}
/*count_small��Ϊһ�����õĲ������ڵݹ�Ѱ��������ʱ����Ϊһ��������ȫ�ֱ������Ĵ���*/


class Solution2 {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        /*�������Ϊ�շ��ؿ�ֵ*/
        if (n == 0)return {};
        vector<int> count;
        count.push_back(0);
        /*����һ������������*/
        BSTNode* node = new BSTNode(nums[n - 1]);
        int count_small;
        for (int i = 1; i < n; i++)
        {
            count_small = 0;
            BST_insert(node, new BSTNode(nums[n - i - 1]), count_small);
            count.push_back(count_small);
        }
        /*���Ҫ����ɾ�����ڵ�*/
        delete node;
        reverse(count.begin(), count.end());
        /*push_back��ʱ��������ģ���ʱֻҪ��count����reverse����*/
        return count;
    }
};

//�鲢����
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int>count;//������
        vector<pair<int, int> > num;//����ÿ�������������
        for (int i = 0; i < nums.size(); ++i)
        {
            count.push_back(0);
            num.push_back(make_pair(nums[i], i));//����ÿ����������ԭ�����е���ţ���������������д���˳��
        }
        merge_sort(num, count);
        return count;
    }

    //�鲢����
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

    //�ϲ�������
    void merge(vector<pair<int, int> >& sub_vec1, vector<pair<int, int> >& sub_vec2, vector<pair<int, int> >& vec, vector<int>& count)
    {
        int i = 0;
        int j = 0;
        while (i < sub_vec1.size() && j < sub_vec2.size())
        {
            if (sub_vec1[i].first <= sub_vec2[j].first)
            {
                vec.push_back(sub_vec1[i]);
                count[sub_vec1[i].second] += j;//��仰������ע�͵ĵط����������͹鲢�������Ҫ��֮ͬ��
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
            count[sub_vec1[i].second] += j;// -��-
        }
        for (; j < sub_vec2.size(); ++j)
        {
            vec.push_back(sub_vec2[j]);
        }
    }
};


