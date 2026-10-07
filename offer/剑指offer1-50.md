# 剑指Offer

## 剑指1-50

### [剑指 Offer 03. 数组中重复的数字](https://leetcode.cn/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof)

在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。
**示例 1：**
输入：
[2, 3, 1, 0, 2, 5, 3]
输出：2 或 3
限制：
2 <= n <= 100000

**思路**
题目说明尚未被充分使用，即在一个长度为n的数组nums 里的所有数字都在 0 ~ n-1 的范围内。
此说明含义：数组元素的索引和值是一对多的关系。
因此，可遍历数组并通过交换操作，使元素的索引与值建立一一对应（即 `nums[i] = i`）。因而，就能通过索引映射对应的值，起到与字典等价的作用。
遍历中，第一次遇到数字 x 时，将其交换至索引 x 处；而当第二次遇到数字 x 时，一定有 `nums[x] = x` ，此时即可得到一组重复数字。
**复杂度分析：**
时间复杂度 O(N) ： 遍历数组使用 O(N) ，每轮遍历的判断和交换操作使用 O(1) 。
空间复杂度 O(1) ： 使用常数复杂度的额外空间。

```C++
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        int i =0;
        while(i<nums.size()){
            if (nums[i]==i){
                ++i;
                continue;
            }
            if(nums[nums[i]]==nums[i]) return nums[i];
            swap(nums[i],nums[nums[i]]);
        }
        return -1;
    }
};
```

### [剑指 Offer 04. 二维数组中的查找](https://leetcode.cn/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/)

在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个高效的函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
**示例:**
现有矩阵 matrix 如下：

```C++
[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
```

给定 target = 5，返回 true。
给定 target = 20，返回 false。

限制：
0 <= n <= 1000
0 <= m <= 1000

**思路**
我们将矩阵逆时针旋转 45° ，并将其转化为图形式，发现其类似于二叉搜索树，即对于每个元素，其左分支元素更小、右分支元素更大。因此，通过从 “根节点” 开始搜索，遇到比 target 大的元素就向左，反之向右，即可找到目标值 target。
“根节点” 对应的是矩阵的 “左下角” 和 “右上角” 元素，本文称之为 标志数 ，以 matrix 中的 左下角元素 为标志数 flag ，则有:
若 flag > target ，则 target 一定在 flag 所在 行的上方 ，即 flag 所在行可被消去。
若 flag < target ，则 target 一定在 flag 所在 列的右方 ，即 flag 所在列可被消去。
**算法流程：**
从矩阵 matrix 左下角元素（索引设为 (i, j) ）开始遍历，并与目标值对比：
当 `matrix[i][j] > target` 时，执行 i-- ，即消去第 i 行元素；
当 `matrix[i][j] < target` 时，执行 j++ ，即消去第 j 列元素；
当 `matrix[i][j] = target` 时，返回 true，代表找到目标值。
若行索引或列索引越界，则代表矩阵中无目标值，返回 false。
每轮 i 或 j 移动后，相当于生成了“消去一行（列）的新矩阵”， 索引(i,j) 指向新矩阵的左下角元素（标志数），因此可重复使用以上性质消去行（列）。

**复杂度分析：**
时间复杂度 O(M+N) ：其中，N 和 M 分别为矩阵行数和列数，此算法最多循环 M+N 次。
空间复杂度 O(1) : i, j 指针使用常数大小额外空间。

```C++
class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        int i = matrix.size() - 1, j = 0; //i是行数的最大值，j是列，j从第一列开始
        while(i >= 0 && j < matrix[0].size())
        {
            if(matrix[i][j] > target) i--; //比target大，一定在这一行上面
            else if(matrix[i][j] < target) j++; //比target小，一定在这一列右边
            else return true; //找到了就是true
        }
        return false; //还没有找到说明就没有这个target
    }
};
```

### [剑指 Offer 05. 替换空格](https://leetcode.cn/problems/ti-huan-kong-ge-lcof/)

请实现一个函数，把字符串 s 中的每个空格替换成"%20"。
**示例 1：**
输入：s = "We are happy."
输出："We%20are%20happy."
限制：
0 <= s 的长度 <= 10000

**思路**
首先扩充数组到每个空格替换成"%20"之后的大小。
然后从后向前替换空格，也就是双指针法，过程如下：
i指向新长度的末尾，j指向旧长度的末尾。
!替换空格
为什么要从后向前填充，从前向后填充不行么？因为从前向后填充就是`O(n^2)`的算法了，因为每次添加元素都要将添加元素之后的所有元素向后移动。
**其实很多数组填充类的问题，都可以先预先给数组扩容带填充后的大小，然后在从后向前进行操作。**
这么做有两个好处：

* 不用申请新数组。
* 从后向前填充元素，避免了从前先后填充元素要来的 每次添加元素都要将添加元素之后的所有元素向后移动。

复杂度分析：
时间复杂度 O(N) ： 遍历统计、遍历修改皆使用 O(N) 时间。
空间复杂度 O(1) ： 由于是原地扩展 s 长度，因此使用 O(1) 额外空间。

```C++
class Solution {
public:
    string replaceSpace(string s) {
        int count = 0, len = s.size();
        // 统计空格数量
        for (char &c : s) {
            if (c == ' ') count++;
        }
        // 修改 s 长度
        s.resize(len + 2 * count);
        // 倒序遍历修改
        for(int i = len - 1, j = s.size() - 1; i < j; i--, j--) {
            if (s[i] != ' ')
                s[j] = s[i];
            else {
                s[j - 2] = '%';
                s[j - 1] = '2';
                s[j] = '0';
                j -= 2;
            }
        }
        return s;
    }
};
```

### [剑指 Offer 06. 从尾到头打印链表](https://leetcode.cn/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/)

输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。
**示例 1：**
输入：head = [1,3,2]
输出：[2,3,1]
限制：
0 <= 链表长度 <= 10000

**思路**
利用栈先入后出的特性，将先遍历链表，把其中的值都push到stack中，然后再从stack中把值pop出去，得到最后的结果。
**复杂度分析**
时间复杂度：O(n)。正向遍历一遍链表，然后从栈弹出全部节点，等于又反向遍历一遍链表。
空间复杂度：O(n)。额外使用一个栈存储链表中的每个节点。

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        stack<int> st;
        while(head){
            st.push(head->val);
            head = head->next;
        }
        vector<int> vec;
        while(!st.empty()){
            vec.emplace_back(st.top());
            st.pop();
        }
        return vec;
    }
};
```

### [剑指 Offer 07. 重建二叉树](https://leetcode.cn/problems/zhong-jian-er-cha-shu-lcof/)

输入某二叉树的前序遍历和中序遍历的结果，请构建该二叉树并返回其根节点。
假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
**示例 1**:

```C++
Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]
```

**示例 2:**

```C++
Input: preorder = [-1], inorder = [-1]
Output: [-1]
```

限制：
0 <= 节点个数 <= 5000

**思路**
二叉树前序遍历的顺序为：

* 先遍历根节点；
* 随后递归地遍历左子树；
* 最后递归地遍历右子树。

二叉树中序遍历的顺序为：

* 先递归地遍历左子树；
* 随后遍历根节点；
* 最后递归地遍历右子树。

在「递归」地遍历某个子树的过程中，我们也是将这颗子树看成一颗全新的树，按照上述的顺序进行遍历。挖掘「前序遍历」和「中序遍历」的性质，我们就可以得出本题的做法。

方法一：递归
对于任意一颗树而言，前序遍历的形式总是
`[ 根节点, [左子树的前序遍历结果], [右子树的前序遍历结果] ]`
即根节点总是前序遍历中的第一个节点。而中序遍历的形式总是
`[ [左子树的中序遍历结果], 根节点, [右子树的中序遍历结果] ]`
只要我们在中序遍历中定位到根节点，那么我们就可以分别知道左子树和右子树中的节点数目。由于同一颗子树的前序遍历和中序遍历的长度显然是相同的，因此我们就可以对应到前序遍历的结果中，对上述形式中的所有左右括号进行定位。
这样以来，我们就知道了左子树的前序遍历和中序遍历结果，以及右子树的前序遍历和中序遍历结果，我们就可以递归地对构造出左子树和右子树，再将这两颗子树接到根节点的左右位置。
细节
在中序遍历中对根节点进行定位时，一种简单的方法是直接扫描整个中序遍历的结果并找出根节点，但这样做的时间复杂度较高。我们可以考虑使用哈希表来帮助我们快速地定位根节点。对于哈希映射中的每个键值对，键表示一个元素（节点的值），值表示其在中序遍历中的出现位置。在构造二叉树的过程之前，我们可以对中序遍历的列表进行一遍扫描，就可以构造出这个哈希映射。在此后构造二叉树的过程中，我们就只需要 `O(1)` 的时间对根节点进行定位了。

**复杂度分析**
时间复杂度：O(n)，其中 n 是树中的节点个数。

空间复杂度：O(n)，除去返回的答案需要的 O(n) 空间之外，我们还需要使用 O(n) 的空间存储哈希映射，以及 O(h)（其中 h 是树的高度）的空间表示递归时栈空间。这里 h < n，所以总空间复杂度为 O(n)。

```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    unordered_map<int, int> index;

public:
    TreeNode* myBuildTree(const vector<int>& preorder, const vector<int>& inorder, int preorder_left, int preorder_right, int inorder_left, int inorder_right) {
        if (preorder_left > preorder_right) {
            return nullptr;
        }
        
        // 前序遍历中的第一个节点就是根节点
        int preorder_root = preorder_left;
        // 在中序遍历中定位根节点
        int inorder_root = index[preorder[preorder_root]];
        
        // 先把根节点建立出来
        TreeNode* root = new TreeNode(preorder[preorder_root]);
        // 得到左子树中的节点数目
        int size_left_subtree = inorder_root - inorder_left;
        // 递归地构造左子树，并连接到根节点
        // 先序遍历中「从 左边界+1 开始的 size_left_subtree」个元素就对应了中序遍历中「从 左边界 开始到 根节点定位-1」的元素
        root->left = myBuildTree(preorder, inorder, preorder_left + 1, preorder_left + size_left_subtree, inorder_left, inorder_root - 1);
        // 递归地构造右子树，并连接到根节点
        // 先序遍历中「从 左边界+1+左子树节点数目 开始到 右边界」的元素就对应了中序遍历中「从 根节点定位+1 到 右边界」的元素
        root->right = myBuildTree(preorder, inorder, preorder_left + size_left_subtree + 1, preorder_right, inorder_root + 1, inorder_right);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        // 构造哈希映射，帮助我们快速定位根节点
        for (int i = 0; i < n; ++i) {
            index[inorder[i]] = i;
        }
        return myBuildTree(preorder, inorder, 0, n - 1, 0, n - 1);
    }
};
```

### [剑指 Offer 09. 用两个栈实现队列](https://leetcode.cn/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/)

用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead ，分别完成在队列尾部插入整数和在队列头部删除整数的功能。(若队列中没有元素，deleteHead 操作返回 -1 )
**示例 1：**

```C++
输入：
["CQueue","appendTail","deleteHead","deleteHead"]
[[],[3],[],[]]
输出：[null,null,3,-1]
示例 2：

输入：
["CQueue","deleteHead","appendTail","appendTail","deleteHead","deleteHead"]
[[],[],[5],[2],[],[]]
输出：[null,-1,null,null,5,2]
```

提示：
1 <= values <= 10000
最多会对 appendTail、deleteHead 进行 10000 次调用

**思路**
因为本题是要用栈来模拟队列，所以需要知道队列的特性就是先入先出，分析一个栈的特性先进后出为了模拟队列的出顺序，所以将一个栈的元素放入另一个栈中就实现了栈的出去顺序就是队列的顺序，也就是所谓的负负得正思路
定义两个栈，一个输入栈支持插入操作，一个输出栈支持删除操作。
根据栈先进后出的特性，我们每次往第一个栈里插入元素后，第一个栈的底部元素是最后插入的元素，第一个栈的顶部元素是下一个待删除的元素。为了维护队列先进先出的特性，我们引入第二个栈，用第二个栈维护待删除的元素，在执行删除操作的时候我们首先看下第二个栈是否为空。如果为空，我们将第一个栈里的元素一个个弹出插入到第二个栈里，这样第二个栈里元素的顺序就是待删除的元素的顺序，要执行删除操作的时候我们直接弹出第二个栈的元素返回即可。

**复杂度分析**
时间复杂度：appendTail 为 O(1)，deleteHead 为均摊 O(1)。对于每个元素，至多入栈和出栈各两次，故均摊复杂度为 O(1)。

空间复杂度：O(n)。其中 n 是操作总数。对于有 n 次 appendTail 操作的情况，队列中会有 n 个元素，故空间复杂度为 O(n)。

```C++
class CQueue {
public:
    stack<int> stk1;
    stack<int> stk2;
    CQueue() {
    }
    void appendTail(int value) {
        stk1.push(value);
    }
    int deleteHead() {
        if(stk1.empty()) return -1;
        while(stk1.size() - 1) 
        {
            stk2.push(stk1.top());
            stk1.pop();
        }
        int res = stk1.top();
        stk1.pop();
        while(stk2.size()) {
            stk1.push(stk2.top());
            stk2.pop();
        }
        return res;
    }
};
/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */
```

### [剑指 Offer 10- I. 斐波那契数列](https://leetcode.cn/problems/fei-bo-na-qi-shu-lie-lcof/)

写一个函数，输入 n ，求斐波那契（Fibonacci）数列的第 n 项（即 F(N)）。斐波那契数列的定义如下：

```C++
F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
```

斐波那契数列由 0 和 1 开始，之后的斐波那契数就是由之前的两数相加而得出。
答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
**示例 1：**
输入：n = 2
输出：1
**示例 2：**
输入：n = 5
输出：5
**提示：**
0 <= n <= 100

**思路**
方法二：矩阵快速幂
方法一的时间复杂度是 O(n)O(n)。使用矩阵快速幂的方法可以降低时间复杂度。

首先我们可以构建这样一个递推关系：

$\left[ \begin{matrix} 1 & 1 \\ 1 & 0 \end{matrix} \right] \left[ \begin{matrix} F(n)\\ F(n - 1) \end{matrix} \right] = \left[ \begin{matrix} F(n) + F(n - 1)\\ F(n) \end{matrix} \right] = \left[ \begin{matrix} F(n + 1)\\ F(n) \end{matrix} \right]$
因此：
$\left[ \begin{matrix} F(n + 1)\\ F(n) \end{matrix} \right] = \left[ \begin{matrix} 1 & 1 \\ 1 & 0 \end{matrix} \right] ^n \left[ \begin{matrix} F(1)\\ F(0) \end{matrix} \right]$
令：
M = $\left[ \begin{matrix} 1 & 1 \\ 1 & 0 \end{matrix} \right]$
因此只要我们能快速计算矩阵 M 的 n 次幂，就可以得到 F(n)的值。如果直接求取 $M^n$
 ，时间复杂度是 $O(n)$，可以定义矩阵乘法，然后用快速幂算法来加速这里 $M^n$ 的求取。
**复杂度分析**
时间复杂度：$O(\log n)$。
空间复杂度：$O(1)$。

```C++
class Solution {
public:
    const int MOD = 1e9+7;

    int fib(int n) {
        if (n < 2) {
            return n;
        }
        vector<vector<long>> q{{1, 1}, {1, 0}};
        vector<vector<long>> res = pow(q, n - 1);
        return res[0][0];
    }

    vector<vector<long>> pow(vector<vector<long>>& a, int n) {
        vector<vector<long>> ret{{1, 0}, {0, 1}};
        while (n > 0) {
            if (n & 1) {
                ret = multiply(ret, a);
            }
            n >>= 1;
            a = multiply(a, a);
        }
        return ret;
    }

    vector<vector<long>> multiply(vector<vector<long>>& a, vector<vector<long>>& b) {
        vector<vector<long>> c{{0, 0}, {0, 0}};
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                c[i][j] = (a[i][0] * b[0][j] + a[i][1] * b[1][j]) % MOD;
            }
        }
        return c;
    }
};
```

### [剑指 Offer 10- II. 青蛙跳台阶问题](https://leetcode.cn/problems/qing-wa-tiao-tai-jie-wen-ti-lcof/)

一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。求该青蛙跳上一个 n 级的台阶总共有多少种跳法。
答案需要取模 1e9+7，如计算初始结果为：1000000008，请返回 1。

**复杂度分析**
时间复杂度 O(N) ： 计算 f(n)需循环 n 次，每轮循环内计算操作使用 O(1) 。
空间复杂度 O(1) ： 几个标志变量使用常数大小的额外空间。

```C++
class Solution {
public:
    int numWays(int n) {
    int a = 0, b = 1, c = 1;
    for (int i = 0; i<n; ++i){
        a = b; b = c;
        c = (a + b) % 1000000007;
    }
    return b;
    }
};
```

### [剑指 Offer 12. 矩阵中的路径](https://leetcode.cn/problems/ju-zhen-zhong-de-lu-jing-lcof/)

给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

**示例 1：**

```C++
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
输出：true
示例 2：

输入：board = [["a","b"],["c","d"]], word = "abcd"
输出：false
```

**提示**：
m == board.length
n = board[i].length
1 <= m, n <= 6
1 <= word.length <= 15
board 和 word 仅由大小写英文字母组成

**思路**
设函数 $\text{check}(i, j, k)$ 表示判断以网格的 $(i, j)$ 位置出发，能否搜索到单词 $\textit{word}[k..]$，其中 $\textit{word}[k..]$ 表示字符串 $\textit{word}$ 从第 k 个字符开始的后缀子串。如果能搜索到，则返回 $\texttt{true}$，反之返回 $\texttt{false}$。函数 $\text{check}(i, j, k)$ 的执行步骤如下：

如果 $\textit{board}[i][j] \neq s[k]$，当前字符不匹配，直接返回 $\texttt{false}$。
如果当前已经访问到字符串的末尾，且对应字符依然匹配，此时直接返回 $\texttt{true}$。
否则，遍历当前位置的所有相邻位置。如果从某个相邻位置出发，能够搜索到子串 $\textit{word}[k+1..]$，则返回 $\texttt{true}$，否则返回 $\texttt{false}$。
这样，我们对每一个位置 $(i,j)$ 都调用函数 $\text{check}(i, j, 0)$ 进行检查：只要有一处返回 $\texttt{true}$，就说明网格中能够找到相应的单词，否则说明不能找到。

为了防止重复遍历相同的位置，需要额外维护一个与 $\textit{board}$ 等大的 $\textit{visited}$ 数组，用于标识每个位置是否被访问过。每次遍历相邻位置时，需要跳过已经被访问的位置。

**复杂度分析**
时间复杂度：一个非常宽松的上界为 $O(MN \cdot 3^L)$，其中 $M, N$为网格的长度与宽度，$L$ 为字符串 $\textit{word}$ 的长度。在每次调用函数 $\text{check}$ 时，除了第一次可以进入 4 个分支以外，其余时间我们最多会进入 3 个分支（因为每个位置只能使用一次，所以走过来的分支没法走回去）。由于单词长为 $L$，故 $\text{check}(i, j, 0)$的时间复杂度为 $O(3^L)$，而我们要执行 $O(MN)$ 次检查。然而，由于剪枝的存在，我们在遇到不匹配或已访问的字符时会提前退出，终止递归流程。因此，实际的时间复杂度会远远小于 $\Theta(MN \cdot 3^L)$。

空间复杂度：$O(MN)$。我们额外开辟了 $O(MN)$ 的 $\textit{visited}$ 数组，同时栈的深度最大为 $O(\min(L, MN))$。

```C++
class Solution {
public:
    bool check(vector<vector<char>>& board, vector<vector<int>>& visited, int i, int j, string& s, int k) {
        if (board[i][j] != s[k]) {
            return false;
        } else if (k == s.length() - 1) {
            return true;
        }
        visited[i][j] = true;
        vector<pair<int, int>> directions{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        bool result = false;
        for (const auto& dir: directions) {
            int newi = i + dir.first, newj = j + dir.second;
            if (newi >= 0 && newi < board.size() && newj >= 0 && newj < board[0].size()) {
                if (!visited[newi][newj]) {
                    bool flag = check(board, visited, newi, newj, s, k + 1);
                    if (flag) {
                        result = true;
                        break;
                    }
                }
            }
        }
        visited[i][j] = false;
        return result;
    }

    bool exist(vector<vector<char>>& board, string word) {
        int h = board.size(), w = board[0].size();
        vector<vector<int>> visited(h, vector<int>(w));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                bool flag = check(board, visited, i, j, word, 0);
                if (flag) {
                    return true;
                }
            }
        }
        return false;
    }
};
```

### [剑指 Offer 14- I. 剪绳子](https://leetcode.cn/problems/jian-sheng-zi-lcof/)

给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m-1] 。请问 k[0]*k[1]*...*k[m-1] 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。
**示例 1：**
输入: 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1
示例 2:
输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36
**提示：**
2 <= n <= 58

```C++
class Solution {
public:
    int cuttingRope(int n) {
        vector <int> dp(n + 1);
        for (int i = 2; i <= n; i++) {
            int curMax = 0;
            for (int j = 1; j < i; j++) {
                curMax = max(curMax, max(j * (i - j), j * dp[i - j]));
            }
            dp[i] = curMax;
        }
        return dp[n];
    }
};
```

### [剑指 Offer 14- II. 剪绳子 II](https://leetcode.cn/problems/jian-sheng-zi-ii-lcof/)

给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m - 1] 。请问 k[0]*k[1]*...*k[m - 1] 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。
答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
**示例 1：**
输入: 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1
**示例 2:**
输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36
**提示：**
2 <= n <= 1000

```C++
class Solution {
public:
    int cuttingRope(int n) {       
        if (n <= 3) return n - 1;
        long ret = 1;
        if (n % 3 == 1){
            ret = 4;
            n = n - 4;
        }
        if (n % 3 == 2){
            ret = 2;
            n = n - 2;
        }
        while (n) {
            ret = ret * 3 % 1000000007;            
            n = n - 3;
        }
        return (int)ret;
    }
};
```

### [剑指 Offer 15. 二进制中1的个数](https://leetcode.cn/problems/er-jin-zhi-zhong-1de-ge-shu-lcof/)

编写一个函数，输入是一个无符号整数（以二进制串的形式），返回其二进制表达式中数字位数为 '1' 的个数（也被称为 汉明重量).）。

提示：
请注意，在某些语言（如 Java）中，没有无符号整数类型。在这种情况下，输入和输出都将被指定为有符号整数类型，并且不应影响您的实现，因为无论整数是有符号的还是无符号的，其内部的二进制表示形式都是相同的。
在 Java 中，编译器使用 二进制补码 记法来表示有符号整数。因此，在上面的 示例 3 中，输入表示有符号整数 -3。

**示例 1：**
输入：n = 11 (控制台输入 00000000000000000000000000001011)
输出：3
解释：输入的二进制串 00000000000000000000000000001011 中，共有三位为 '1'。
**示例 2：**
输入：n = 128 (控制台输入 00000000000000000000000010000000)
输出：1
解释：输入的二进制串 00000000000000000000000010000000 中，共有一位为 '1'。
**示例 3：**
输入：n = 4294967293 (控制台输入 11111111111111111111111111111101，部分语言中 n = -3）
输出：31
解释：输入的二进制串 11111111111111111111111111111101 中，共有 31 位为 '1'。
**提示**
输入必须是长度为 32 的 二进制串 。

```C++
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ret = 0;
        for (int i = 0; i < 32; i++) {
            if (n & (1 << i)) {
                ret++;
            }
        }
        return ret;
    }
};
```

### [剑指 Offer 16. 数值的整数次方](https://leetcode.cn/problems/shu-zhi-de-zheng-shu-ci-fang-lcof/)

实现 pow(x, n) ，即计算 x 的 n 次幂函数（即，xn）。不得使用库函数，同时不需要考虑大数问题。

**示例 1：**
输入：x = 2.00000, n = 10
输出：1024.00000
**示例 2：**
输入：x = 2.10000, n = 3
输出：9.26100
**示例 3：**
输入：x = 2.00000, n = -2
输出：0.25000
解释：2-2 = 1/22 = 1/4 = 0.25

**提示：**

-100.0 < x < 100.0
-231 <= n <= 231-1
-104 <= xn <= 104

```C++
class Solution {
private:
    double Pow(double x, long long n) {
        if(x == 1) return 1;
        if(n == 0) return 1;
        if(n == 1) return x;
        double t = Pow(x, n / 2);
        if(n & 1) {
            return x * t * t;
        } else {
            return t * t;
        }
    }
public:
    double myPow(double x, int n) {
        if(n < 1) {
            return 1.0 / Pow(x, -(long long)n) ;
        }
        return Pow(x, n);
    }
};
```

### [剑指 Offer 17. 打印从1到最大的n位数](https://leetcode.cn/problems/da-yin-cong-1dao-zui-da-de-nwei-shu-lcof/)

输入数字 n，按顺序打印出从 1 到最大的 n 位十进制数。比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。

**示例 1:**
输入: n = 1
输出: [1,2,3,4,5,6,7,8,9]

**说明：**
用返回一个整数列表来代替打印
n 为正整数

```C++
class Solution {
public:
    vector<int> printNumbers(int n) {
        vector<int> res;
        int x = pow(10, n) - 1;
        res.reserve(x);
        for (int i = 1; i <= x; i++) res.emplace_back(i);
        return res;
    }
};
```

### [剑指 Offer 18. 删除链表的节点](https://leetcode.cn/problems/shan-chu-lian-biao-de-jie-dian-lcof/)

给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。
返回删除后的链表的头节点。
注意：此题对比原题有改动

**示例 1:**
输入: head = [4,5,1,9], val = 5
输出: [4,1,9]
解释: 给定你链表中值为 5 的第二个节点，那么在调用了你的函数之后，该链表应变为 4 -> 1 -> 9.
**示例 2:**
输入: head = [4,5,1,9], val = 1
输出: [4,5,9]
解释: 给定你链表中值为 1 的第三个节点，那么在调用了你的函数之后，该链表应变为 4 -> 5 -> 9.
**说明：**
题目保证链表中节点的值互不相同
若使用 C 或 C++ 语言，你不需要 free 或 delete 被删除的节点

```C++
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        if(head->val == val) return head->next;
        ListNode *pre = head, *cur = head->next;
        while(cur != nullptr && cur->val != val) {
            pre = cur;
            cur = cur->next;
        }
        if(cur != nullptr) pre->next = cur->next;
        return head;
    }
};
```

### [剑指 Offer 19. 正则表达式匹配](https://leetcode.cn/problems/zheng-ze-biao-da-shi-pi-pei-lcof/)

请实现一个函数用来匹配包含$.$和$*$的正则表达式。模式中的字符'.'表示任意一个字符，而$*$表示它前面的字符可以出现任意次（含0次）。在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串$"aaa"$与模式$"a.a"$和$"ab*ac*a"$匹配，但与$"aa.a"$和$"ab*a"$均不匹配。

**示例 1:**
输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。
**示例 2:
**
输入:
s = "aa"
p = "a*"
输出: true
解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
**示例 3:**

输入:
s = "ab"
p = ".*"
输出: true
解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
**示例 4:**

输入:
s = "aab"
p = "c*a*b"
输出: true
解释: 因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。
**示例 5:**

输入:
s = "mississippi"
p = "mis*is*p*."
输出: false
s 可能为空，且只包含从 a-z 的小写字母。
p 可能为空，且只包含从 a-z 的小写字母以及字符 . 和$ *$，无连续的 $'*'$。

```C++
class Solution {
public:
    bool isMatch(string s, string p) 
    {
        return match(s.data(), p.data());
    }
    bool match(char* s, char* p) {
        if (!*p) return !*s;
        if (*(p + 1) != '*') 
            return *s == *p || (*p == '.' && *s != '\0') ? match(s + 1, p + 1) : false; 
        else 
            return *s == *p || (*p == '.' && *s != '\0') ? match(s, p + 2) || match(s + 1, p) : match(s, p + 2);
            //或者return (*s == *p || (*p == '.' && *s != '\0')) && match(s + 1, p) || match(s, p + 2);
    }
};
```

### [剑指 Offer 20. 表示数值的字符串](https://leetcode.cn/problems/biao-shi-shu-zhi-de-zi-fu-chuan-lcof/)

请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。

数值（按顺序）可以分成以下几个部分：

若干空格
一个 小数 或者 整数
（可选）一个 'e' 或 'E' ，后面跟着一个 整数
若干空格
小数（按顺序）可以分成以下几个部分：

（可选）一个符号字符（'+' 或 '-'）
下述格式之一：
至少一位数字，后面跟着一个点 '.'
至少一位数字，后面跟着一个点 '.' ，后面再跟着至少一位数字
一个点 '.' ，后面跟着至少一位数字
整数（按顺序）可以分成以下几个部分：

（可选）一个符号字符（'+' 或 '-'）
至少一位数字
部分数值列举如下：

["+100", "5e2", "-123", "3.1416", "-1E-16", "0123"]
部分非数值列举如下：

["12e", "1a3.14", "1.2.3", "+-5", "12e+5.4"]

示例 1：

输入：s = "0"
输出：true
示例 2：

输入：s = "e"
输出：false
示例 3：

输入：s = "."
输出：false
示例 4：

输入：s = "    .1  "
输出：true

提示：

1 <= s.length <= 20
s 仅含英文字母（大写和小写），数字（0-9），加号 '+' ，减号 '-' ，空格 ' ' 或者点 '.'

```C++
class Solution {
public:
    bool isNumber(string s) 
    {
        // 第一步，去掉首尾空格，l记录数字开始位，r记录数字结束位
        int l = 0, r = s.size() - 1;
        while (l < s.size() && s[l] == ' ') ++ l;
        while (r >= 0 && s[r] == ' ') -- r;
        if (l > r) return false;

        // 第二步，查找l到r之间是否存在e，若存在e，posE记录e的位置
        int posE = l - 1;
        for (int i = l; i <= r; ++ i)
        {
            if (s[i] == 'e' || s[i] == 'E')
            {
                posE = i;
                break;
            }
        }

        // 第三步，
        bool res = false;
        // 如果不存在E，直接判断 l 到 r 之间是否为整数或者小数
        if (posE == l - 1)
        {
            if (s[l] == '+' || s[l] == '-') ++ l;
            res = isFraction(l, r, s) || isInteger(l, r, s);
        }
        // 如果存在E，先判断 posE + 1 到 r 是否为整数，再判断 l 到 posE - 1 之间是否为整数或者小数
        else
        {
            int second_l = posE + 1;
            if (s[second_l] == '+' || s[second_l] == '-') ++ second_l;
            res = isInteger(second_l, r, s);

            if (s[l] == '+' || s[l] == '-') ++ l;
            res = res && (isFraction(l, posE - 1, s) || isInteger(l, posE - 1, s));
        }
        return res;
    }

    // 判断 l 到 r 是否为整数
    bool isInteger(int l, int r, string& s)
    {
        if (l > r)  return false;
        for (int i = l; i <= r; ++ i)
        {
            if (s[i] > '9' || s[i] < '0')
                return false;
        }
        return true;
    }

    // 判断 l 到 r 是否为小数
    bool isFraction(int l, int r, string& s)
    {
        // 小数判断同理，先找到 . 的位置 posDot
        // 再判断 l 到 posDot - 1，posDot + 1 到 r 是否为整数
        if (r - l < 1)  return false;
        int posDot = l - 1;
        for (int i = l; i <= r; ++ i)
        {
            if (s[i] == '.')
            {
                posDot = i;
                break;
            }
        }
        if (posDot == l - 1)    return false;
        else if (posDot == l)   return isInteger(posDot + 1, r, s);
        else if (posDot == r)   return isInteger(l, posDot - 1, s);
        else                    return isInteger(l, posDot - 1, s) && isInteger(posDot + 1, r, s);
    }
};
```

### [剑指 Offer 21. 调整数组顺序使奇数位于偶数前面](https://leetcode.cn/problems/diao-zheng-shu-zu-shun-xu-shi-qi-shu-wei-yu-ou-shu-qian-mian-lcof/)

输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数在数组的前半部分，所有偶数在数组的后半部分。

**示例：**
输入：nums = [1,2,3,4]
输出：[1,3,2,4]
注：[3,1,2,4] 也是正确的答案之一。
提示：
0 <= nums.length <= 50000
0 <= nums[i] <= 10000

```C++
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            while (left < right and nums[left] % 2 == 1) {
                left++;
            }
            while (left < right and nums[right] % 2 == 0) {
                right--;
            }
            if (left < right) {
                swap(nums[left++], nums[right--]);
            }
        }
        return nums;
    }
};

```

### [剑指 Offer 22. 链表中倒数第k个节点](https://leetcode.cn/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/)

输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。

例如，一个链表有 6 个节点，从头节点开始，它们的值依次是 1、2、3、4、5、6。这个链表的倒数第 3 个节点是值为 4 的节点。

**示例：**
给定一个链表: 1->2->3->4->5, 和 k = 2.
返回链表 4->5.

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* fast = head;
        ListNode* slow = head;

        while (fast && k > 0) {
            fast = fast->next;
            k--;
        }
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }

        return slow;
    }
};
```

### [剑指 Offer 24. 反转链表](https://leetcode.cn/problems/fan-zhuan-lian-biao-lcof/)

定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。
**示例:**
输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL

```C++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while(curr){
            ListNode* next = curr -> next;
            curr -> next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
};
```

### [剑指 Offer 25. 合并两个排序的链表](https://leetcode.cn/problems/he-bing-liang-ge-pai-xu-de-lian-biao-lcof/)

输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。

示例1：

输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *dup = new ListNode(0), *cur = dup; //创建一个头节点，用cur指向该节点
        while (l1 && l2) {
            l1->val < l2->val ? (cur->next = l1, l1 = l1->next) : (cur->next = l2, l2 = l2->next);
            cur = cur->next;              
        }
        cur->next = l1 ? l1 : l2; //加入最后一个非空节点
        return dup->next; //返回合并链表
    }
};
```

### [剑指 Offer 26. 树的子结构](https://leetcode.cn/problems/shu-de-zi-jie-gou-lcof/)

输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)

B是A的子结构， 即 A中有出现和B相同的结构和节点值。

例如:
给定的树 A:

```C++
     3
    / \
   4   5
  / \
 1   2
给定的树 B：

   4 
  /
 1
返回 true，因为 B 与 A 的一个子树拥有相同的结构和节点值。

示例 1：

输入：A = [1,2,3], B = [3,1]
输出：false
示例 2：

输入：A = [3,4,5,1,2], B = [4,1]
输出：true
```

```C++
class Solution {
public:
    bool isSubStructure(TreeNode* A, TreeNode* B) {
     // 特判：树 A 为空 或 树 B 为空 时，直接返回 false
     if (A == nullptr || B == nullptr) return false;
    /* 
    1. 判断 B 是 A 的子树，recur(A, B);
    2. 判断 B 是 A 的左子树，isSubisSubStructure(A->left, B);
    3. 判断 B 是 A 的右子树，isSubisSubStructure(A->right, B);
    */
    return recur(A, B) || isSubStructure(A->left, B) || isSubStructure(A->right, B);
    }
    bool recur(TreeNode* A, TreeNode* B) {
        if (B == nullptr) return true;
        if (A == nullptr || A->val != B->val) return false;
        return recur(A->left, B->left) && recur(A->right, B->right);
    }
};
```

### [剑指 Offer 27. 二叉树的镜像](https://leetcode.cn/problems/er-cha-shu-de-jing-xiang-lcof/)

请完成一个函数，输入一个二叉树，该函数输出它的镜像。

例如输入：

```C++
     4
   /   \
  2     7
 / \   / \
1   3 6   9
镜像输出：

     4
   /   \
  7     2
 / \   / \
9   6 3   1
```

示例 1：

输入：root = [4,2,7,1,3,6,9]
输出：[4,7,2,9,6,3,1]

```C++
class Solution {
public:
    TreeNode* mirrorTree(TreeNode* root) {
        if (root == nullptr){
            return nullptr;
        }
        TreeNode* left = mirrorTree(root->left);
        TreeNode* right = mirrorTree(root->right);
        root->left = right;
        root->right = left;
        return root;
};
```

### [剑指 Offer 28. 对称的二叉树](https://leetcode.cn/problems/dui-cheng-de-er-cha-shu-lcof/)

请实现一个函数，用来判断一棵二叉树是不是对称的。如果一棵二叉树和它的镜像一样，那么它是对称的。

例如，二叉树 [1,2,2,3,4,4,3] 是对称的。

```C++
    1
   / \
  2   2
 / \ / \
3  4 4  3
但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:

    1
   / \
  2   2
   \   \
   3    3
```

示例 1：

输入：root = [1,2,2,3,4,4,3]
输出：true
示例 2：

输入：root = [1,2,2,null,3,null,3]
输出：false

限制：
0 <= 节点个数 <= 1000

```C++
class Solution {
public:
    bool check(TreeNode* p , TreeNode* q){
        if(!p && !q) return true;
        if(!p || !q) return false;
        return p->val == q->val && check(p->left,q->right) && check(p->right,q->left);
    }
    bool isSymmetric(TreeNode* root) {
        return check(root,root);
    }
};
```

### [剑指 Offer 29. 顺时针打印矩阵](https://leetcode.cn/problems/shun-shi-zhen-da-yin-ju-zhen-lcof/)

输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。

```C++
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]

输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
输出：[1,2,3,4,8,12,11,10,9,5,6,7]
```

限制：
0 <= matrix.length <= 100
0 <= matrix[i].length <= 100

```C++
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) 
            return {};
        vector<int> res;
        int top = 0;                      //上边界
        int bottom = matrix.size() - 1;   //下边界
        int left = 0;                     //左边界
        int right = matrix[0].size() - 1; //右边界
        
        while (true) {
            // 从左到右
            for (int i = left; i <= right; ++ i) 
                res.push_back(matrix[top][i]);
            // 每次从左往右执行一次，则要往下移一层
            if (++ top > bottom) break;
            // 从上到下
            for (int i = top; i <= bottom; ++ i) 
                res.push_back(matrix[i][right]);
            // 每次从上到下执行一次，则要往左移一列
            if (-- right < left) break;
            // 从右到左
            for (int i = right; i >= left; -- i) 
                res.push_back(matrix[bottom][i]);
            // 每次从右到左执行一次，则要往上移一行
            if (-- bottom < top) break;
            // 从下到上
            for (int i = bottom; i >= top; -- i) 
                res.push_back(matrix[i][left]);
            // 每次从下到上执行一次，则要往右移一列
            if (++ left > right) break;
        }
        return res;
    }
};
```

### [剑指 Offer 30. 包含min函数的栈](https://leetcode.cn/problems/bao-han-minhan-shu-de-zhan-lcof/)

定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的 min 函数在该栈中，调用 min、push 及 pop 的时间复杂度都是 O(1)。

示例:

```C++
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.min();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.min();   --> 返回 -2.
```

提示：
各函数的调用总次数不超过 20000 次

```C++
class MinStack {
public:
    /** initialize your data structure here. */
    stack<int>main_stack;
    stack<int>min_stack;
    MinStack() {
        min_stack.push(INT_MAX);
    }
    
    void push(int x) {
        main_stack.push(x);
        min_stack.push(::min(min_stack.top(),x));
    }
    void pop() {
        main_stack.pop();
        min_stack.pop();
    }
    int top() {
        return main_stack.top();
    }
    int min() {
        return min_stack.top();
    }
};
/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */
```

### [剑指 Offer 31. 栈的压入、弹出序列](https://leetcode.cn/problems/zhan-de-ya-ru-dan-chu-xu-lie-lcof/)

输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如，序列 {1,2,3,4,5} 是某栈的压栈序列，序列 {4,5,3,2,1} 是该压栈序列对应的一个弹出序列，但 {4,3,5,1,2} 就不可能是该压栈序列的弹出序列。
**示例 1：**

```C++
输入：pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
输出：true
解释：我们可以按以下顺序执行：
push(1), push(2), push(3), push(4), pop() -> 4,
push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1
示例 2：

输入：pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
输出：false
解释：1 不能在 2 之前弹出。
```

**提示：**

```C++
0 <= pushed.length == popped.length <= 1000
0 <= pushed[i], popped[i] < 1000
pushed 是 popped 的排列。
```

```C++
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> st;
        int n = pushed.size();
        for (int i = 0, j = 0; i < n; i++) {
            st.emplace(pushed[i]);
            while (!st.empty() && st.top() == popped[j]) {
                st.pop();
                j++;
            }
        }
        return st.empty();
    }
};
```

### [剑指 Offer 32 - I. 从上到下打印二叉树](https://leetcode.cn/problems/cong-shang-dao-xia-da-yin-er-cha-shu-lcof/)

从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。

例如:

```C++
给定二叉树: [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
返回：

[3,9,20,15,7]
```

提示：

节点总数 <= 1000

```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> levelOrder(TreeNode* root) {
        /* 根据函数返回值定义存储结果的变量 */
        vector<int> result;
        /* 定义一个队列用于存储节点的数据 */
        queue<TreeNode*> que;
        /* 判空 */
        if(root != NULL) que.push(root);

        /* 开始层序遍历 */
        while(!que.empty()) {
            /* 计算队列的大小也即有多少个孩子 */
            int size = que.size();
            /* 层序遍历 */
            for(int i = 0; i < size; i++) {
                /* 获取第一个节点数据 */
                TreeNode* node = que.front();
                que.pop();

                result.push_back(node->val);
                if(node->left != NULL) que.push(node->left);
                if(node->right != NULL) que.push(node->right);

            }
        }
        return result;
    }
};
```

### [剑指 Offer 32 - II. 从上到下打印二叉树 II](https://leetcode.cn/problems/cong-shang-dao-xia-da-yin-er-cha-shu-ii-lcof/)

从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行。
例如:

```C++
给定二叉树: [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
返回其层次遍历结果：

[
  [3],
  [9,20],
  [15,7]
]
```

提示：
节点总数 <= 1000

```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        /* 根据函数返回值定义存储结果的变量 */
        vector<vector<int>> result;
        /* 定义一个队列用于存储节点的数据 */
        queue<TreeNode*> que;
        /* 判空 */
        if(root != NULL) que.push(root);

        /* 开始层序遍历 */
        while(!que.empty()) {
            /* 计算队列的大小也即有多少个孩子 */
            int size = que.size();
            /* 定义一个临时vector 存储每一层 */
            vector<int> vec;
            /* 层序遍历 */
            for(int i = 0; i < size; i++) {
                /* 获取第一个节点数据 */
                TreeNode* node = que.front();
                que.pop();

                vec.push_back(node->val);
                if(node->left != NULL) que.push(node->left);
                if(node->right != NULL) que.push(node->right);
            }
            /* 将一层的数据保存 */
            result.push_back(vec);
        }
        return result;
    }
};
```

### [剑指 Offer 32 - III. 从上到下打印二叉树 III](https://leetcode.cn/problems/cong-shang-dao-xia-da-yin-er-cha-shu-iii-lcof/)

请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。
例如:

```C++
给定二叉树: [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
返回其层次遍历结果：

[
  [3],
  [20,9],
  [15,7]
]
```

提示：
节点总数 <= 1000

```C++
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        /* 根据函数返回值定义存储结果的变量 */
        vector<vector<int>> result;
        /* 定义一个队列用于存储节点的数据 */
        queue<TreeNode*> que;
        /* 判空 */
        if(root != NULL) que.push(root);

        /* 定义一个变量 用于判断奇偶层 */
        int count = 0;

        /* 开始层序遍历 */
        while(!que.empty()) {
            /* 计算队列的大小也即有多少个孩子 */
            int size = que.size();
            /* 定义一个临时vector 存储每一层 */
            vector<int> vec;
            stack<int> st;
            /* 层序遍历 */
            for(int i = 0; i < size; i++) {
                /* 获取第一个节点数据 */
                TreeNode* node = que.front();
                que.pop();

                vec.push_back(node->val);
                if(node->left != NULL) que.push(node->left);
                if(node->right != NULL) que.push(node->right);
            }
            /* 奇数层因为需要反向所以想到栈 */
            if(count%2 != 0) {
                for(int i = 0; i < vec.size(); i++) {
                    st.push(vec[i]);
                }
                vec.clear();
                while(!st.empty()) {
                    vec.push_back(st.top());
                    st.pop();
                }
            }
            /* 将一层的数据保存 */
            result.push_back(vec);
            /* 计数== 层数 */
            count++;
        }
        return result;
    }
};
```

### [剑指 Offer 33. 二叉搜索树的后序遍历序列](https://leetcode.cn/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof/)

输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。如果是则返回 true，否则返回 false。假设输入的数组的任意两个数字都互不相同。

```C++
     5
    / \
   2   6
  / \
 1   3
示例 1：

输入: [1,6,3,2,5]
输出: false
示例 2：

输入: [1,3,2,6,5]
输出: true
```

提示：

数组长度 <= 1000

```C++
class Solution {
public:
    bool traversal(vector<int>& postorder, int start, int end) {
        /* 递归终止条件 */
        if(start >= end) return true;
        int index = start;
        /* 中间处理逻辑 */
        while(postorder[index] < postorder[end]) index++;
        /* 记录分割点 */
       int midIndex = index;
        while(postorder[index] > postorder[end]) index++;
        /* 递归左右子树 */
        bool left = traversal(postorder, start, midIndex-1);
        bool right = traversal(postorder, midIndex, end-1);
        return index == end && left && right;
    }

    bool verifyPostorder(vector<int>& postorder) {
        return traversal(postorder, 0, postorder.size()-1);
    }
};
```

剑指 Offer 34. 二叉树中和为某一值的路径
给你二叉树的根节点 root 和一个整数目标和 targetSum ，找出所有 从根节点到叶子节点 路径总和等于给定目标和的路径。
叶子节点 是指没有子节点的节点。

```C++
示例 1：
输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
输出：[[5,4,11,2],[5,8,4,5]]
示例 2：
输入：root = [1,2,3], targetSum = 5
输出：[]
示例 3：
输入：root = [1,2], targetSum = 0
输出：[]
```

提示：
树中节点总数在范围 [0, 5000] 内
-1000 <= Node.val <= 1000
-1000 <= targetSum <= 1000

```C++
class Solution {
public:
    vector<vector<int>> ret;
    vector<int> path;

    void dfs(TreeNode* root, int target) {
        if (root == nullptr) {
            return;
        }
        path.emplace_back(root->val);
        target -= root->val;
        if (root->left == nullptr && root->right == nullptr && target == 0) {
            ret.emplace_back(path);
        }
        dfs(root->left, target);
        dfs(root->right, target);
        path.pop_back();
    }

    vector<vector<int>> pathSum(TreeNode* root, int target) {
        dfs(root, target);
        return ret;
    }
};
```

### [剑指 Offer 35. 复杂链表的复制](https://leetcode.cn/problems/fu-za-lian-biao-de-fu-zhi-lcof/)

请实现 copyRandomList 函数，复制一个复杂链表。在复杂链表中，每个节点除了有一个 next 指针指向下一个节点，还有一个 random 指针指向链表中的任意节点或者 null。

```C++
示例 1：
输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]
示例 2：
输入：head = [[1,1],[2,1]]
输出：[[1,1],[2,1]]
示例 3：
输入：head = [[3,null],[3,0],[3,null]]
输出：[[3,null],[3,0],[3,null]]
示例 4：
输入：head = []
输出：[]
解释：给定的链表为空（空指针），因此返回 null。
```

提示：
-10000 <= Node.val <= 10000
Node.random 为空（null）或指向链表中的节点。
节点数目不超过 1000 。

```C++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head == nullptr) return nullptr;
        Node* cur = head;
        unordered_map<Node*, Node*> map;
        // 3. 复制各节点，并建立 “原节点 -> 新节点” 的 Map 映射
        while(cur != nullptr) {
            map[cur] = new Node(cur->val);
            cur = cur->next;
        }
        cur = head;
        // 4. 构建新链表的 next 和 random 指向
        while(cur != nullptr) {
            map[cur]->next = map[cur->next];
            map[cur]->random = map[cur->random];
            cur = cur->next;
        }
        // 5. 返回新链表的头节点
        return map[head];
    }
};
```

### [剑指 Offer 36. 二叉搜索树与双向链表](https://leetcode.cn/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof/)

输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。要求不能创建任何新的节点，只能调整树中节点指针的指向。
我们希望将这个二叉搜索树转化为双向循环链表。链表中的每个节点都有一个前驱和后继指针。对于双向循环链表，第一个节点的前驱是最后一个节点，最后一个节点的后继是第一个节点。
$[4,2,5,1,3,NULL,NULL]$
下图展示了上面的二叉搜索树转化成的链表。“head” 表示指向链表中有最小元素的节点。
特别地，我们希望可以就地完成转换操作。当转化完成以后，树中节点的左指针需要指向前驱，树中节点的右指针需要指向后继。还需要返回链表中的第一个节点的指针。

```C++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if(root == nullptr) return nullptr;
        dfs(root);
        head->left = pre;
        pre->right = head;
        return head;
    }
private:
    Node *pre, *head;
    void dfs(Node* cur) {
        if(cur == nullptr) return;
        dfs(cur->left);
        if(pre != nullptr) pre->right = cur;
        else head = cur;
        cur->left = pre;
        pre = cur;
        dfs(cur->right);
    }
};
```

### [剑指 Offer 37. 序列化二叉树](https://leetcode.cn/problems/xu-lie-hua-er-cha-shu-lcof/)

请实现两个函数，分别用来序列化和反序列化二叉树。
你需要设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。
提示：输入输出格式与 LeetCode 目前使用的方式一致，详情请参阅 LeetCode 序列化二叉树的格式。你并非必须采取这种方式，你也可以采用其他的方法解决这个问题。
示例：

```C++
输入：root = [1,2,3,null,null,4,5]
输出：[1,2,3,null,null,4,5]
```

```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        // 层序遍历 BFS
        string ret;
        queue<TreeNode*> que;
        que.emplace(root);
        while (!que.empty()) {
            int size = que.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                // 空节点直接加入"None,"
                if (node == NULL) ret += "None,";
                else {
                    // 加入节点val，并依次遍历左右子树
                    ret += to_string(node->val) + ",";
                    que.emplace(node->left);
                    que.emplace(node->right);
                }
            }
        }
        return ret;        
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.size() == 0) return NULL;
        list<string> dataArray;
        string str;
        for (auto& c : data) {
            if (c == ',') {
                dataArray.emplace_back(str);
                str.clear();
            } else {
                str.push_back(c);
            }
        }
        if (str.size() != 0) {
            dataArray.emplace_back(str);
            str.clear();
        }
        queue<TreeNode*> que;
        if (dataArray.front() == "None") return NULL;
        TreeNode* root = new TreeNode(stoi(dataArray.front()));
        que.emplace(root);
        dataArray.pop_front();
        while (!que.empty() && !dataArray.empty()) {
            int size = que.size();
            for (int i = 0; i < size && !dataArray.empty(); i++) {
                TreeNode* cur = que.front(); // 父节点
                que.pop();
                // 第一个为左节点
                if (dataArray.front() != "None") {
                    TreeNode* node1 = new TreeNode(stoi(dataArray.front()));
                    cur->left = node1;
                    que.push(node1);
                }
                dataArray.pop_front();
                
                // 第二个为右节点
                if (dataArray.front() != "None") {
                    TreeNode* node2 = new TreeNode(stoi(dataArray.front()));
                    cur->right = node2;
                    que.push(node2);
                }
                dataArray.pop_front();
            }
        }
        return root;       
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
```

### [剑指 Offer 38. 字符串的排列](https://leetcode.cn/problems/zi-fu-chuan-de-pai-lie-lcof/)

输入一个字符串，打印出该字符串中字符的所有排列。
你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。
示例:
输入：s = "abc"
输出：["abc","acb","bac","bca","cab","cba"]
限制：
1 <= s 的长度 <= 8

```C++
class Solution {
public:
    vector<string> permutation(string s) {
        dfs(s, 0);
        return res;
    }
private:
    vector<string> res;
    void dfs(string s, int x) {
        if(x == s.size() - 1) {
            res.push_back(s);                       // 添加排列方案
            return;
        }
        set<int> st;
        for(int i = x; i < s.size(); i++) {
            if(st.find(s[i]) != st.end()) continue; // 重复，因此剪枝
            st.insert(s[i]);
            swap(s[i], s[x]);                       // 交换，将 s[i] 固定在第 x 位
            dfs(s, x + 1);                          // 开启固定第 x + 1 位字符
            swap(s[i], s[x]);                       // 恢复交换
        }
    }
};
```

### [剑指 Offer 39. 数组中出现次数超过一半的数字](https://leetcode.cn/problems/shu-zu-zhong-chu-xian-ci-shu-chao-guo-yi-ban-de-shu-zi-lcof/)

数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
你可以假设数组是非空的，并且给定的数组总是存在多数元素。
示例 1:
输入: [1, 2, 3, 2, 2, 2, 5, 4, 2]
输出: 2
限制：
1 <= 数组长度 <= 50000

```C++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }
};
```

### [剑指 Offer 40. 最小的k个数](https://leetcode.cn/problems/zui-xiao-de-kge-shu-lcof/)

输入整数数组 arr ，找出其中最小的 k 个数。例如，输入4、5、1、6、2、7、3、8这8个数字，则最小的4个数字是1、2、3、4。

示例 1：

```C++
输入：arr = [3,2,1], k = 2
输出：[1,2] 或者 [2,1]
示例 2：
输入：arr = [0,1,2,1], k = 1
输出：[0]
```

限制：
0 <= k <= arr.length <= 10000
0 <= arr[i] <= 10000

```C++
class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> vec(k, 0);
        sort(arr.begin(), arr.end());
        for (int i = 0; i < k; ++i) {
            vec[i] = arr[i];
        }
        return vec;
    }
};
```

```C++
class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> vec(k, 0);
        if (k == 0) { // 排除 0 的情况
            return vec;
        }
        priority_queue<int> Q;
        for (int i = 0; i < k; ++i) {
            Q.push(arr[i]);
        }
        for (int i = k; i < (int)arr.size(); ++i) {
            if (Q.top() > arr[i]) {
                Q.pop();
                Q.push(arr[i]);
            }
        }
        for (int i = 0; i < k; ++i) {
            vec[i] = Q.top();
            Q.pop();
        }
        return vec;
    }
};
```

### [剑指 Offer 41. 数据流中的中位数](https://leetcode.cn/problems/shu-ju-liu-zhong-de-zhong-wei-shu-lcof/)

如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。

例如，

[2,3,4] 的中位数是 3

[2,3] 的中位数是 (2 + 3) / 2 = 2.5

设计一个支持以下两种操作的数据结构：

void addNum(int num) - 从数据流中添加一个整数到数据结构中。
double findMedian() - 返回目前所有元素的中位数。
示例 1：

```C++
输入：
["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]
[[],[1],[2],[],[3],[]]
输出：[null,null,null,1.50000,null,2.00000]
示例 2：
输入：
["MedianFinder","addNum","findMedian","addNum","findMedian"]
[[],[2],[],[3],[]]
输出：[null,null,2.00000,null,2.50000]
```

限制：
最多会对 addNum、findMedian 进行 50000 次调用。

```C++
class MedianFinder {
public:
    priority_queue<int, vector<int>, less<int>> queMin;
    priority_queue<int, vector<int>, greater<int>> queMax;

    MedianFinder() {}

    void addNum(int num) {
        if (queMin.empty() || num <= queMin.top()) {
            queMin.push(num);
            if (queMax.size() + 1 < queMin.size()) {
                queMax.push(queMin.top());
                queMin.pop();
            }
        } else {
            queMax.push(num);
            if (queMax.size() > queMin.size()) {
                queMin.push(queMax.top());
                queMax.pop();
            }
        }
    }

    double findMedian() {
        if (queMin.size() > queMax.size()) {
            return queMin.top();
        }
        return (queMin.top() + queMax.top()) / 2.0;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
```

### [剑指 Offer 42. 连续子数组的最大和](https://leetcode.cn/problems/lian-xu-zi-shu-zu-de-zui-da-he-lcof/)

输入一个整型数组，数组中的一个或连续多个整数组成一个子数组。求所有子数组的和的最大值。
要求时间复杂度为O(n)。

```C++
示例1:
输入: nums = [-2,1,-3,4,-1,2,1,-5,4]
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
```

提示：
1 <= arr.length <= 10^5
-100 <= arr[i] <= 100

```C++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int pre = 0, maxAns = nums[0];
        for (const auto &x: nums) {
            pre = max(pre + x, x);
            maxAns = max(maxAns, pre);
        }
        return maxAns;
    }
};
```

### [剑指 Offer 43. 1～n 整数中 1 出现的次数](https://leetcode.cn/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/)

输入一个整数 n ，求1～n这n个整数的十进制表示中1出现的次数。
例如，输入12，1～12这些整数中包含1 的数字有1、10、11和12，1一共出现了5次。
示例 1：
输入：n = 12
输出：5
示例 2：
输入：n = 13
输出：6
限制：
1 <= n < 2^31

```C++
class Solution {
public:
    int countDigitOne(int n) {
        // mulk 表示 10^k
        // 在下面的代码中，可以发现 k 并没有被直接使用到（都是使用 10^k）
        // 但为了让代码看起来更加直观，这里保留了 k
        long long mulk = 1;
        int ans = 0;
        for (int k = 0; n >= mulk; ++k) {
            ans += (n / (mulk * 10)) * mulk + min(max(n % (mulk * 10) - mulk + 1, 0LL), mulk);
            mulk *= 10;
        }
        return ans;
    }
};
```

### [剑指 Offer 44. 数字序列中某一位的数字](https://leetcode.cn/problems/shu-zi-xu-lie-zhong-mou-yi-wei-de-shu-zi-lcof/)

数字以0123456789101112131415…的格式序列化到一个字符序列中。在这个序列中，第5位（从下标0开始计数）是5，第13位是1，第19位是4，等等。

请写一个函数，求任意第n位对应的数字。
示例 1：
输入：n = 3
输出：3
示例 2：
输入：n = 11
输出：0
限制：
0 <= n < 2^31

```C++
class Solution {
public:
    int findNthDigit(int n) {
        int d = 1, count = 9;
        while (n > (long) d * count) {
            n -= d * count;
            d++;
            count *= 10;
        }
        int index = n - 1;
        int start = (int) pow(10, d - 1);
        int num = start + index / d;
        int digitIndex = index % d;
        int digit = (num / (int) (pow(10, d - digitIndex - 1))) % 10;
        return digit;
    }
};
```

### [剑指 Offer 45. 把数组排成最小的数](https://leetcode.cn/problems/ba-shu-zu-pai-cheng-zui-xiao-de-shu-lcof/)

输入一个非负整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。
示例 1:
输入: [10,2]
输出: "102"
示例 2:
输入: [3,30,34,5,9]
输出: "3033459"
提示:
0 < nums.length <= 100
说明:
输出结果可能非常大，所以你需要返回一个字符串而不是整数
拼接起来的数字可能会有前导 0，最后结果不需要去掉前导 0

```C++
class Solution {
public:
    string minNumber(vector<int>& nums) {
        // 本质还是一个排序的问题，区别是比大小的方式变了。。两个数A、B,如果拼接后AB小于BA，则A小于B。
        for(int i=nums.size()-1;i>0;i--){
            for(int j=0;j<i;j++){
                if (exchange(nums[j],nums[j+1])){
                    swap(nums[j],nums[j+1]);
                }
            }
        }
        string res ="";
        for(int i:nums)
            res +=to_string(i);
        return res;
    }
    bool exchange(int i,int j){   // 如果拼接后ij>ji,则需要交换i和j的位置，反之不需要交换
        string s1 = to_string(i)+to_string(j);
        string s2 = to_string(j)+to_string(i); 
        if (s1>s2) return true;  // 字符串可以直接比大小
         return false;
    }
};
```

### [剑指 Offer 46. 把数字翻译成字符串](https://leetcode.cn/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof/)

给定一个数字，我们按照如下规则把它翻译为字符串：0 翻译成 “a” ，1 翻译成 “b”，……，11 翻译成 “l”，……，25 翻译成 “z”。一个数字可能有多个翻译。请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。
示例 1:
输入: 12258
输出: 5
解释: 12258有5种不同的翻译，分别是"bccfi", "bwfi", "bczi", "mcfi"和"mzi"
提示：
0 <= num < 2^31

```C++
class Solution {
public:
    int translateNum(int num) {
        string src = to_string(num);
        int p = 0, q = 0, r = 1;
        for (int i = 0; i < src.size(); ++i) {
            p = q; 
            q = r; 
            r = 0;
            r += q;
            if (i == 0) {
                continue;
            }
            auto pre = src.substr(i - 1, 2);
            if (pre <= "25" && pre >= "10") {
                r += p;
            }
        }
        return r;
    }
};
```

### [剑指 Offer 47. 礼物的最大价值](https://leetcode.cn/problems/li-wu-de-zui-da-jie-zhi-lcof/)

在一个 m*n 的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于 0）。你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者向下移动一格、直到到达棋盘的右下角。给定一个棋盘及其上面的礼物的价值，请计算你最多能拿到多少价值的礼物？
示例 1:

```C++
输入: 
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
输出: 12
解释: 路径 1→3→5→2→1 可以拿到最多价值的礼物
```

提示：
0 < grid.length <= 200
0 < grid[0].length <= 200

```C++
class Solution {
public:
    int maxValue(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(i == 0 && j == 0) continue;
                if(i == 0) grid[i][j] += grid[i][j-1];
                else if(j == 0) grid[i][j] += grid[i-1][j];
                else grid[i][j] += max(grid[i-1][j], grid[i][j-1]);
            }
        }
        return grid[m-1][n-1];
    }
};
```

### [剑指 Offer 48. 最长不含重复字符的子字符串](https://leetcode.cn/problems/zui-chang-bu-han-zhong-fu-zi-fu-de-zi-zi-fu-chuan-lcof/)

请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。

示例 1:

输入: "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:
输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:
输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

提示：
s.length <= 40000

```C++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // 哈希集合，记录每个字符是否出现过
        unordered_set<char> occ;
        int n = s.size();
        // 右指针，初始值为 -1，相当于我们在字符串的左边界的左侧，还没有开始移动
        int rk = -1, ans = 0;
        // 枚举左指针的位置，初始值隐性地表示为 -1
        for (int i = 0; i < n; ++i) {
            if (i != 0) {
                // 左指针向右移动一格，移除一个字符
                occ.erase(s[i - 1]);
            }
            while (rk + 1 < n && !occ.count(s[rk + 1])) {
                // 不断地移动右指针
                occ.insert(s[rk + 1]);
                ++rk;
            }
            // 第 i 到 rk 个字符是一个极长的无重复字符子串
            ans = max(ans, rk - i + 1);
        }
        return ans;
    }
};
```

### [剑指 Offer 49. 丑数](https://leetcode.cn/problems/chou-shu-lcof/)

我们把只包含质因子 2、3 和 5 的数称作丑数（Ugly Number）。求按从小到大的顺序的第 n 个丑数。

示例:
输入: n = 10
输出: 12
解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
说明:  
1 是丑数。
n 不超过1690。

```C++
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n + 1);
        dp[1] = 1;
        int p2 = 1, p3 = 1, p5 = 1;
        for (int i = 2; i <= n; i++) {
            int num2 = dp[p2] * 2, num3 = dp[p3] * 3, num5 = dp[p5] * 5;
            dp[i] = min(min(num2, num3), num5);
            if (dp[i] == num2) {
                p2++;
            }
            if (dp[i] == num3) {
                p3++;
            }
            if (dp[i] == num5) {
                p5++;
            }
        }
        return dp[n];
    }
};
```

### [剑指 Offer 50. 第一个只出现一次的字符](https://leetcode.cn/problems/di-yi-ge-zhi-chu-xian-yi-ci-de-zi-fu-lcof/)

在字符串 s 中找出第一个只出现一次的字符。如果没有，返回一个单空格。 s 只包含小写字母。
示例 1:
输入：s = "abaccdeff"
输出：'b'
示例 2:
输入：s = ""
输出：' '
限制：
0 <= s 的长度 <= 50000

```C++
class Solution {
public:
    char firstUniqChar(string s) {
        map<char,int> mp;
        for(auto i:s){
            mp[i]++;
        }
        for(auto i:s){
            if(mp[i]==1) return i;
        }
        return ' ';
    }
};
```
