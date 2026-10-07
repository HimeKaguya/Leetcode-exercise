# 面试经典150题

## 1 [88. 合并两个有序数组](https://leetcode.cn/problems/merge-sorted-array/description/?envType=study-plan-v2&envId=top-interview-150)

给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。

请你 合并 nums2 到 nums1 中，使合并后的数组同样按 非递减顺序 排列。

注意：最终，合并后数组不应由函数返回，而是存储在数组 nums1 中。为了应对这种情况，nums1 的初始长度为 m + n，其中前 m 个元素表示应合并的元素，后 n 个元素为 0 ，应忽略。nums2 的长度为 n 。

示例 1：

输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
输出：[1,2,2,3,5,6]
解释：需要合并 [1,2,3] 和 [2,5,6] 。
合并结果是 [1,2,2,3,5,6] ，其中斜体加粗标注的为 nums1 中的元素。
示例 2：

输入：nums1 = [1], m = 1, nums2 = [], n = 0
输出：[1]
解释：需要合并 [1] 和 [] 。
合并结果是 [1] 。
示例 3：

输入：nums1 = [0], m = 0, nums2 = [1], n = 1
输出：[1]
解释：需要合并的数组是 [] 和 [1] 。
合并结果是 [1] 。
注意，因为 m = 0 ，所以 nums1 中没有元素。nums1 中仅存的 0 仅仅是为了确保合并结果可以顺利存放到 nums1 中。

提示：

nums1.length == m + n
nums2.length == n
0 <= m, n <= 200
1 <= m + n <= 200
-109 <= nums1[i], nums2[j] <= 109

进阶：你可以设计实现一个时间复杂度为 O(m + n) 的算法解决此问题吗？

```C++
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for (int i = 0; i < n; ++i){
            nums1[m+i] = nums2[i]; 
        }
        sort(nums1.begin(),nums1.end());
    }
};
```

```C++
class Solution {
public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
        int p1 = m - 1, p2 = n - 1, p = m + n - 1;
        while (p2 >= 0) { // nums2 还有要合并的元素
            // 如果 p1 < 0，那么走 else 分支，把 nums2 合并到 nums1 中
            if (p1 >= 0 && nums1[p1] > nums2[p2]) {
                nums1[p--] = nums1[p1--]; // 填入 nums1[p1]
            } else {
                nums1[p--] = nums2[p2--]; // 填入 nums2[p1]
            }
        }
    }
};
```

## 2 [27. 移除元素](https://leetcode.cn/problems/remove-element/description/?envType=study-plan-v2&envId=top-interview-150)

给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素。元素的顺序可能发生改变。然后返回 nums 中与 val 不同的元素的数量。

假设 nums 中不等于 val 的元素数量为 k，要通过此题，您需要执行以下操作：

更改 nums 数组，使 nums 的前 k 个元素包含不等于 val 的元素。nums 的其余元素和 nums 的大小并不重要。
返回 k。
用户评测：

评测机将使用以下代码测试您的解决方案：

```Java
int[] nums = [...]; // 输入数组
int val = ...; // 要移除的值
int[] expectedNums = [...]; // 长度正确的预期答案。
                            // 它以不等于 val 的值排序。

int k = removeElement(nums, val); // 调用你的实现

assert k == expectedNums.length;
sort(nums, 0, k); // 排序 nums 的前 k 个元素
for (int i = 0; i < actualLength; i++) {
    assert nums[i] == expectedNums[i];
}
```

如果所有的断言都通过，你的解决方案将会 通过。

示例 1：

输入：`nums = [3,2,2,3], val = 3`
输出：`2, nums = [2,2,_,_]`
解释：你的函数函数应该返回 k = 2, 并且 nums 中的前两个元素均为 2。
你在返回的 k 个元素之外留下了什么并不重要（因此它们并不计入评测）。
示例 2：

输入：`nums = [0,1,2,2,3,0,4,2], val = 2`
输出：`5, nums = [0,1,4,0,3,_,_,_]`
解释：你的函数应该返回 k = 5，并且 nums 中的前五个元素为 0,0,1,3,4。
注意这五个元素可以任意顺序返回。
你在返回的 k 个元素之外留下了什么并不重要（因此它们并不计入评测）。

提示：

```C++
0 <= nums.length <= 100
0 <= nums[i] <= 50
0 <= val <= 100
```

```C++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        int left = 0;
        for (int right = 0; right < n; right++) {
            if (nums[right] != val) {
                nums[left] = nums[right];
                left++;
            }
        }
        return left;
    }
};
```

```C++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int idx = 0;
        for(auto x : nums)
            if(x != val) nums[idx++] = x;
        return idx;
    }
};
```

## 3 [26. 删除有序数组中的重复项](https://leetcode.cn/problems/remove-duplicates-from-sorted-array/description/?envType=study-plan-v2&envId=top-interview-150)

给你一个 非严格递增排列 的数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。元素的 相对顺序 应该保持 一致 。然后返回 nums 中唯一元素的个数。

考虑 nums 的唯一元素的数量为 k ，你需要做以下事情确保你的题解可以被通过：

更改数组 nums ，使 nums 的前 k 个元素包含唯一元素，并按照它们最初在 nums 中出现的顺序排列。nums 的其余元素与 nums 的大小不重要。
返回 k 。
判题标准:

系统会用下面的代码来测试你的题解:

```Java
int[] nums = [...]; // 输入数组
int[] expectedNums = [...]; // 长度正确的期望答案

int k = removeDuplicates(nums); // 调用

assert k == expectedNums.length;
for (int i = 0; i < k; i++) {
    assert nums[i] == expectedNums[i];
}
```

如果所有断言都通过，那么您的题解将被 通过。

示例 1：

输入：`nums = [1,1,2]`
输出：`2, nums = [1,2,_]`
解释：函数应该返回新的长度 2 ，并且原数组 nums 的前两个元素被修改为 1, 2 。不需要考虑数组中超出新长度后面的元素。
示例 2：

输入：`nums = [0,0,1,1,1,2,2,3,3,4]`
输出：`5, nums = [0,1,2,3,4]`
解释：函数应该返回新的长度 5 ， 并且原数组 nums 的前五个元素被修改为 0, 1, 2, 3, 4 。不需要考虑数组中超出新长度后面的元素。

提示：

```Java
1 <= nums.length <= 3 * 104
-104 <= nums[i] <= 104
nums 已按 非严格递增 排列
```

```C++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        return process(nums,1);
    }
    int process(vector<int>& nums,int k){
        int idx = 0;
        for(auto x : nums){
            if(idx < k or nums[idx - k] != x){
                nums[idx++] = x;
            }
        }
        return idx;  
    }
};
```

## 4 [80. 删除有序数组中的重复项 II](https://leetcode.cn/problems/remove-duplicates-from-sorted-array-ii/description/?envType=study-plan-v2&envId=top-interview-150)

给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使得出现次数超过两次的元素只出现两次 ，返回删除后数组的新长度。

不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

说明：

为什么返回数值是整数，但输出的答案是数组呢？

请注意，输入数组是以「引用」方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。

你可以想象内部操作如下:

// nums 是以“引用”方式传递的。也就是说，不对实参做任何拷贝
`int len = removeDuplicates(nums);`

// 在函数里修改输入数组对于调用者是可见的。
// 根据你的函数返回的长度, 它会打印出数组中 该长度范围内 的所有元素。

```C
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
```

示例 1：

输入：`nums = [1,1,1,2,2,3]`
输出：`5, nums = [1,1,2,2,3]`
解释：函数应返回新长度 length = 5, 并且原数组的前五个元素被修改为 1, 1, 2, 2, 3。 不需要考虑数组中超出新长度后面的元素。
示例 2：

输入：`nums = [0,0,1,1,1,1,2,3,3]`
输出：`7, nums = [0,0,1,1,2,3,3]`
解释：函数应返回新长度 length = 7, 并且原数组的前七个元素被修改为 0, 0, 1, 1, 2, 3, 3。不需要考虑数组中超出新长度后面的元素。

提示：

```C
1 <= nums.length <= 3 * 104
-104 <= nums[i] <= 104
nums 已按升序排列
```

```C++
class Solution {
public:
    int work(vector<int>& nums, int k) {
        int len = 0;
        for(auto num : nums)
            if(len < k || nums[len-k] != num)
                nums[len++] = num;
        return len;
    }
    int removeDuplicates(vector<int>& nums) {
        return work(nums, 2);
    }
};
```

## 5 [169. 多数元素](https://leetcode.cn/problems/majority-element/description/?envType=study-plan-v2&envId=top-interview-150)

给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

示例 1：

输入：`nums = [3,2,3]`
输出：3
示例 2：

输入：`nums = [2,2,1,1,1,2,2]`
输出：2

提示：

```C
n == nums.length
1 <= n <= 5 * 104
-109 <= nums[i] <= 109
```

```C++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int x = 0, votes = 0;
        for (int num : nums){
            if (votes == 0) x = num;
            votes += num == x ? 1 : -1;
        }
        return x;
    }
};
```

## 6 [121. 买卖股票的最佳时机](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/description/?envType=study-plan-v2&envId=top-interview-150)

给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。

你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。

示例 1：

输入：`[7,1,5,3,6,4]`
输出：5
解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
示例 2：

输入：prices = `[7,6,4,3,1]`
输出：0
解释：在这种情况下, 没有交易完成, 所以最大利润为 0。
提示：

```C
1 <= prices.length <= 10^5
0 <= prices[i] <= 10^4
```

```C++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int cost = INT_MAX, profit = 0;
        for (int price : prices) {
            cost = min(cost, price);
            profit = max(profit, price - cost);
        }
        return profit;
    }
};
```

## 7 [189. 轮转数组](https://leetcode.cn/problems/rotate-array/description/?envType=study-plan-v2&envId=top-interview-150)

给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。

示例 1:

输入: `nums = [1,2,3,4,5,6,7], k = 3`
输出: `[5,6,7,1,2,3,4]`
解释:
向右轮转 1 步: `[7,1,2,3,4,5,6]`
向右轮转 2 步: `[6,7,1,2,3,4,5]`
向右轮转 3 步: `[5,6,7,1,2,3,4]`
示例 2:

输入：`nums = [-1,-100,3,99], k = 2`
输出：`[3,99,-1,-100]`
解释:
向右轮转 1 步: `[99,-1,-100,3]`
向右轮转 2 步: `[3,99,-1,-100]`

提示：

```C
1 <= nums.length <= 10^5
-2^31 <= nums[i] <= 2^31 - 1
0 <= k <= 10^5
```

尽可能想出更多的解决方案，至少有 三种 不同的方法可以解决这个问题。
你可以使用空间复杂度为 O(1) 的 原地 算法解决这个问题吗？

```C++
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        auto reverse = [&](int i, int j) {
            while (i < j) {
                swap(nums[i++], nums[j--]);
            }
        };
        int n = nums.size();
        k %= n; // 轮转 k 次等于轮转 k%n 次
        reverse(0, n - 1);
        reverse(0, k - 1);
        reverse(k, n - 1);
    }
};
```

## 8 [122. 买卖股票的最佳时机 II](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/description/?envType=study-plan-v2&envId=top-interview-150)

给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。

在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。你也可以先购买，然后在 同一天 出售。

返回 你能获得的 最大 利润 。

示例 1：

输入：prices = [7,1,5,3,6,4]
输出：7
解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4。
随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6 - 3 = 3。
最大总利润为 4 + 3 = 7 。
示例 2：

输入：prices = [1,2,3,4,5]
输出：4
解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4。
最大总利润为 4 。
示例 3：

输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 交易无法获得正利润，所以不参与交易可以获得最大利润，最大利润为 0。

提示：

```C
1 <= prices.length <= 3 * 10^4
0 <= prices[i] <= 10^4
```

```C++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int f0 = 0, f1 = INT_MIN;
        for (int p: prices) {
            int new_f0 = max(f0, f1 + p);
            f1 = max(f1, f0 - p);
            f0 = new_f0;
        }
        return f0;
    }
};
```

## 9 [55. 跳跃游戏](https://leetcode.cn/problems/jump-game/description/?envType=study-plan-v2&envId=top-interview-150)

给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。

示例 1：

输入：nums = [2,3,1,1,4]
输出：true
解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。
示例 2：

输入：nums = [3,2,1,0,4]
输出：false
解释：无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。

提示：

```C
1 <= nums.length <= 10^4
0 <= nums[i] <= 10^5
```

```C++
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int mx = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i > mx) { // 无法到达 i
                return false;
            }
            mx = max(mx, i + nums[i]); // 从 i 最右可以跳到 i + nums[i]
        }
        return true;
    }
};
```

## 10 [45. 跳跃游戏 II](https://leetcode.cn/problems/jump-game-ii/description/?envType=study-plan-v2&envId=top-interview-150)

给定一个长度为 n 的 0 索引整数数组 nums。初始位置为 nums[0]。

每个元素 nums[i] 表示从索引 i 向前跳转的最大长度。换句话说，如果你在 nums[i] 处，你可以跳转到任意 nums[i + j] 处:

0 <= j <= nums[i]
i + j < n
返回到达 nums[n - 1] 的最小跳跃次数。生成的测试用例可以到达 nums[n - 1]。

示例 1：

输入: nums = [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
示例 2：

输入: nums = [2,3,0,1,4]
输出: 2

提示：

```C
1 <= nums.length <= 10^4
0 <= nums[i] <= 1000
题目保证可以到达 nums[n-1]
```

```C++
class Solution {
public:
    int jump(vector<int>& nums) {
        //由于题目给的条件是一定能到达，所以找到那个每次都找到那个离终点最远的位置，然后直到回到起始点，看看需要用几步。此时即为最小步数。
        if (nums.size() == 1){
            return 0;
        }
        int n = nums.size(); 
        int ans = 0;
        int range = n - 1;
        int i = 0;
        while (i <= range){
            if (nums[i] + i >= range){
                ans++;
                if (i == 0){
                    return ans;
                }
                else{
                    range = i;
                    i = 0;
                }
            }
            else{
                i++;
            }
        }
        return ans;
        
    }
};
```

## 11 [274. H 指数](https://leetcode.cn/problems/h-index/description/?envType=study-plan-v2&envId=top-interview-150)

给你一个整数数组 citations ，其中 citations[i] 表示研究者的第 i 篇论文被引用的次数。计算并返回该研究者的 h 指数。

根据维基百科上 h 指数的定义：h 代表“高引用次数” ，一名科研人员的 h 指数 是指他（她）至少发表了 h 篇论文，并且 至少 有 h 篇论文被引用次数大于等于 h 。如果 h 有多种可能的值，h 指数 是其中最大的那个。

示例 1：

输入：citations = [3,0,6,1,5]
输出：3
解释：给定数组表示研究者总共有 5 篇论文，每篇论文相应的被引用了 3, 0, 6, 1, 5 次。
     由于研究者有 3 篇论文每篇 至少 被引用了 3 次，其余两篇论文每篇被引用不多于 3 次，所以她的 h 指数是 3。
示例 2：

输入：citations = [1,3,1]
输出：1

提示：

```C
n == citations.length
1 <= n <= 5000
0 <= citations[i] <= 1000
```

```C++
class Solution {
public:
    int hIndex(vector<int> &citations) {
        int n = citations.size();
        vector<int> cnt(n + 1);
        for (int c : citations) {
            cnt[min(c, n)]++; // 引用次数 > n，等价于引用次数为 n
        }
        int s = 0;
        for (int i = n; ; i--) { // i=0 的时候，s>=i 一定成立
            s += cnt[i];
            if (s >= i) { // 说明有至少 i 篇论文的引用次数至少为 i
                return i;
            }
        }
    }
};
```

## 12 [380. O(1) 时间插入、删除和获取随机元素](https://leetcode.cn/problems/insert-delete-getrandom-o1/description/?envType=study-plan-v2&envId=top-interview-150)

实现RandomizedSet 类：

RandomizedSet() 初始化 RandomizedSet 对象
bool insert(int val) 当元素 val 不存在时，向集合中插入该项，并返回 true ；否则，返回 false 。
bool remove(int val) 当元素 val 存在时，从集合中移除该项，并返回 true ；否则，返回 false 。
int getRandom() 随机返回现有集合中的一项（测试用例保证调用此方法时集合中至少存在一个元素）。每个元素应该有 相同的概率 被返回。
你必须实现类的所有函数，并满足每个函数的 平均 时间复杂度为 O(1) 。

示例：

输入

```C
["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
[[], [1], [2], [2], [], [1], [2], []]
输出
[null, true, false, true, 2, true, false, 2]

解释
RandomizedSet randomizedSet = new RandomizedSet();
randomizedSet.insert(1); // 向集合中插入 1 。返回 true 表示 1 被成功地插入。
randomizedSet.remove(2); // 返回 false ，表示集合中不存在 2 。
randomizedSet.insert(2); // 向集合中插入 2 。返回 true 。集合现在包含 [1,2] 。
randomizedSet.getRandom(); // getRandom 应随机返回 1 或 2 。
randomizedSet.remove(1); // 从集合中移除 1 ，返回 true 。集合现在包含 [2] 。
randomizedSet.insert(2); // 2 已在集合中，所以返回 false 。
randomizedSet.getRandom(); // 由于 2 是集合中唯一的数字，getRandom 总是返回 2 。
```

提示：

```C
-2^31 <= val <= 2^31 - 1
最多调用 insert、remove 和 getRandom 函数 2 * 10^5 次
在调用 getRandom 方法时，数据结构中 至少存在一个 元素。
```

```C++
class RandomizedSet {
private:
    unordered_map<int,int> hash;    //哈希表储存元素值和对应下标，为了remove时实现O（1）
    vector<int> dyArray;        //vector可以作为动态数组，实现getRandom和insert的常数时间操作

public:
    /** Initialize your data structure here. */
    RandomizedSet() {

    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        auto it = hash.find(val);
        if(it != hash.end()) return false;  //如果集合中已经存在val，返回false，节省时间
        dyArray.push_back(val);
        hash[val] = dyArray.size() - 1;
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        auto it = hash.find(val);
        if(it == hash.end()) return false;  //删除时，如果集合中不存在val，返回false

        int lastPos = dyArray.size() - 1;   //将被删除值和数组最后一位进行交换
        int valPos = hash[val];
        dyArray[valPos] = dyArray[lastPos];
        dyArray.pop_back();                 //vector数组删除val
        hash[dyArray[valPos]] = valPos;     //被交换的值下标发生变化，需要更新
        hash.erase(val);                    //哈希表中删除val的项
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        int size = dyArray.size();
        int pos = rand()%size;  //对下标产生随机数
        return dyArray[pos];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
```

## 13 [238. 除自身以外数组的乘积](https://leetcode.cn/problems/product-of-array-except-self/description/?envType=study-plan-v2&envId=top-interview-150)

给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积 。

题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。

请 不要使用除法，且在 O(n) 时间复杂度内完成此题。

示例 1：

输入: nums = [1,2,3,4]
输出: [24,12,8,6]

示例 2：

输入: nums = [-1,1,0,-3,3]
输出: [0,0,9,0,0]

提示：

```C
2 <= nums.length <= 10^5
-30 <= nums[i] <= 30
保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内
```

进阶：你可以在 O(1) 的额外空间复杂度内完成这个题目吗？（ 出于对空间复杂度分析的目的，输出数组 不被视为 额外空间。）

```C++
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> suf(n);
        suf[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--) {
            suf[i] = suf[i + 1] * nums[i + 1];
        }

        int pre = 1;
        for (int i = 0; i < n; i++) {
            // 此时 pre 为 nums[0] 到 nums[i-1] 的乘积，直接乘到 suf[i] 中
            suf[i] *= pre;
            pre *= nums[i];
        }

        return suf;
    }
};
```

## 14 [134. 加油站](https://leetcode.cn/problems/gas-station/description/?envType=study-plan-v2&envId=top-interview-150)

在一条环路上有 n 个加油站，其中第 i 个加油站有汽油 gas[i] 升。

你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。

给定两个整数数组 gas 和 cost ，如果你可以按顺序绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1 。如果存在解，则保证它是唯一的。

示例 1：

输入: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
输出: 3
解释:
从 3 号加油站(索引为 3 处)出发，可获得 4 升汽油。此时油箱有 = 0 + 4 = 4 升汽油
开往 4 号加油站，此时油箱有 4 - 1 + 5 = 8 升汽油
开往 0 号加油站，此时油箱有 8 - 2 + 1 = 7 升汽油
开往 1 号加油站，此时油箱有 7 - 3 + 2 = 6 升汽油
开往 2 号加油站，此时油箱有 6 - 4 + 3 = 5 升汽油
开往 3 号加油站，你需要消耗 5 升汽油，正好足够你返回到 3 号加油站。
因此，3 可为起始索引。

示例 2：

输入: gas = [2,3,4], cost = [3,4,3]
输出: -1
解释:
你不能从 0 号或 1 号加油站出发，因为没有足够的汽油可以让你行驶到下一个加油站。
我们从 2 号加油站出发，可以获得 4 升汽油。 此时油箱有 = 0 + 4 = 4 升汽油
开往 0 号加油站，此时油箱有 4 - 3 + 2 = 3 升汽油
开往 1 号加油站，此时油箱有 3 - 3 + 3 = 3 升汽油
你无法返回 2 号加油站，因为返程需要消耗 4 升汽油，但是你的油箱只有 3 升汽油。
因此，无论怎样，你都不可能绕环路行驶一周。

提示：

```C
gas.length == n
cost.length == n
1 <= n <= 10^5
0 <= gas[i], cost[i] <= 10^4
```

```C++
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        int i = 0;
        while (i < n) {
            int sumOfGas = 0, sumOfCost = 0;
            int cnt = 0;
            while (cnt < n) {
                int j = (i + cnt) % n;
                sumOfGas += gas[j];
                sumOfCost += cost[j];
                if (sumOfCost > sumOfGas) {
                    break;
                }
                cnt++;
            }
            if (cnt == n) {
                return i;
            } else {
                i = i + cnt + 1;
            }
        }
        return -1;
    }
};
```

## 15 [135. 分发糖果](https://leetcode.cn/problems/candy/description/?envType=study-plan-v2&envId=top-interview-150)

n 个孩子站成一排。给你一个整数数组 ratings 表示每个孩子的评分。

你需要按照以下要求，给这些孩子分发糖果：

每个孩子至少分配到 1 个糖果。
相邻两个孩子评分更高的孩子会获得更多的糖果。
请你给每个孩子分发糖果，计算并返回需要准备的 最少糖果数目 。

示例 1：

输入：ratings = [1,0,2]
输出：5
解释：你可以分别给第一个、第二个、第三个孩子分发 2、1、2 颗糖果。

示例 2：

输入：ratings = [1,2,2]
输出：4
解释：你可以分别给第一个、第二个、第三个孩子分发 1、2、1 颗糖果。
     第三个孩子只得到 1 颗糖果，这满足题面中的两个条件。

提示：

```C
n == ratings.length
1 <= n <= 2 * 10^4
0 <= ratings[i] <= 2 * 10^4
```

```C++
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        int ret = 1;
        int inc = 1, dec = 0, pre = 1;
        for (int i = 1; i < n; i++) {
            if (ratings[i] >= ratings[i - 1]) {
                dec = 0;
                pre = ratings[i] == ratings[i - 1] ? 1 : pre + 1;
                ret += pre;
                inc = pre;
            } else {
                dec++;
                if (dec == inc) {
                    dec++;
                }
                ret += dec;
                pre = 1;
            }
        }
        return ret;
    }
};
```
