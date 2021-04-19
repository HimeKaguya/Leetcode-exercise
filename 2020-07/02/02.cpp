//[有序矩阵中第K小的元素](https://leetcode-cn.com/problems/kth-smallest-element-in-a-sorted-matrix/)
#include<iostream>
#include<vector>
#include<algorithm>
#include <queue>
using namespace std;

//暴力
//class Solution {
//public:
//    int kthSmallest(vector<vector<int>>& matrix, int k) {
//        vector<int> rec;
//        for (auto row : matrix) {
//            for (int it : row) {
//                rec.push_back(it);
//            }
//        }
//        sort(rec.begin(), rec.end());
//        return rec[k - 1];
//    }
//};

//归并
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        struct point {
            int val, x, y;
            point(int val, int x, int y) : val(val), x(x), y(y) {}
            bool operator> (const point& a) const { return this->val > a.val; }
        };
        priority_queue<point, vector<point>, greater<point>> que;
        int n = matrix.size();
        for (int i = 0; i < n; i++) {
            que.emplace(matrix[i][0], i, 0);
        }
        for (int i = 0; i < k - 1; i++) {
            point now = que.top();
            que.pop();
            if (now.y != n - 1) {
                que.emplace(matrix[now.x][now.y + 1], now.x, now.y + 1);
            }
        }
        return que.top().val;
    }
};

//二分查找
//class Solution {
//public:
//    int kthSmallest(vector<vector<int>>& matrix, int k) {
//        int left = matrix[0][0], right = matrix.back().back();
//        while (left < right) {
//            int mid = left + (right - left) / 2;
//            int cnt = search_less_equal(matrix, mid);
//            if (cnt < k) left = mid + 1;
//            else right = mid;
//        }
//        return left;
//    }
//
//    int search_less_equal(vector<vector<int>>& matrix, int target) {
//        int n = matrix.size(), i = n - 1, j = 0, res = 0;
//        while (i >= 0 && j < n) {
//            if (matrix[i][j] <= target) {
//                res += i + 1;
//                ++j;
//            }
//            else {
//                --i;
//            }
//        }
//        return res;
//    }
//};


int main()
{
    //matrix = [
    //    [1, 5, 9] ,
    //    [10, 11, 13],
    //    [12, 13, 15]
    //    ]
    vector<vector<int>> matrix;
    int row, column, data;
    cout << "输入row和column";
    cin >> row >> column;
    cin.clear();
    for (int i = 0; i < row; i++) 
    {
        vector<int> tmp;//一维vector  tmp
        for (int j = 0; j < column; j++) 
        {
            cin >> data;
            tmp.push_back(data);
        }
        matrix.push_back(tmp);//把一维 vector tmp 放进 二维vector vt
    }
    int k = 8;
    Solution* sol = new Solution;
    cout << sol->kthSmallest(matrix,k) << endl;
    delete sol;
    return 0;
}