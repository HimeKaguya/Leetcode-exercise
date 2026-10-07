import numpy as np
import pandas as pd
from collections import Counter
from sortedcollections import SortedList

# def skipped_number_to_real_cost(N):
#     # 将N转为字符串以便逐位处理
#     str_N = str(N)
#     real_cost = 0
#     # 遍历每一位数字
#     for digit in str_N:
#         digit = int(digit)
#         # 如果数字大于4，那么在实际数中要减去1（因为跳过了4）
#         if digit > 4:
#             digit -= 1
#         # 将当前位的数字转换为十进制，并累加到real_cost中
#         real_cost = real_cost * 9 + digit
#     return real_cost

# # 测试输入
# if __name__ == '__main__':
#     N = int(input())
#     print(skipped_number_to_real_cost(N))

# def max_difference(nums):
#     n = len(nums)
#     # 计算前缀和
#     prefix_sum = [0] * (n + 1)
#     for i in range(1, n + 1):
#         prefix_sum[i] = prefix_sum[i - 1] + nums[i - 1]

#     # 计算后缀和
#     suffix_sum = [0] * (n + 1)
#     for i in range(n - 1, -1, -1):
#         suffix_sum[i] = suffix_sum[i + 1] + nums[i]

#     # 初始化最大差值为负无穷
#     max_diff = float('-inf')

#     # 遍历分割点，计算差值并更新最大差值
#     for i in range(1, n):
#         diff = abs(prefix_sum[i] - suffix_sum[i])
#         max_diff = max(max_diff, diff)

#     # 返回最大差值
#     return max_diff


# # 主程序
# if __name__ == '__main__':
#     # 读取输入
#     n = int(input())
#     nums = list(map(int, input().split()))
#     # 调用函数计算差值的最大值
#     result = max_difference(nums)
#     # 输出结果
#     print(result)

# def find_last_started_engines(N, E, start_info):
#     # 初始化一个列表用于存储每个发动机的启动时刻，初始时刻设为无穷大
#     start_times = [float('inf')] * N
    
#     # 遍历手动启动信息，更新对应发动机的启动时刻
#     for T, P in start_info:
#         # 确保如果同一个发动机有多个启动时刻时，只保留最早的
#         start_times[P] = min(start_times[P], T)
    
#     # 创建一个待处理列表，按启动时刻排序
#     to_process = sorted(start_info, key=lambda x: x[0])
    
#     # 模拟启动过程
#     while to_process:
#         # 从队列中取出一个待处理的启动事件
#         T, P = to_process.pop(0)
        
#         # 计算相邻发动机的位置，注意循环连接
#         left = (P - 1) % N
#         right = (P + 1) % N
        
#         # 检查并更新左侧相邻发动机的启动时刻
#         if start_times[left] > T + 1:
#             start_times[left] = T + 1
#             # 将更新后的相邻发动机加入待处理队列
#             to_process.append((T + 1, left))
        
#         # 检查并更新右侧相邻发动机的启动时刻
#         if start_times[right] > T + 1:
#             start_times[right] = T + 1
#             # 将更新后的相邻发动机加入待处理队列
#             to_process.append((T + 1, right))
    
#     # 找出启动时刻的最大值
#     max_time = max(start_times)
    
#     # 找出所有在最大启动时刻启动的发动机
#     last_started_engines = [i for i in range(N) if start_times[i] == max_time]
    
#     # 输出这些发动机的数量
#     print(len(last_started_engines))
#     # 输出这些发动机的位置编号，按升序排列
#     print(" ".join(map(str, sorted(last_started_engines))))

# # 读取输入，N表示发动机数量，E表示手动启动事件数量
# N, E = map(int, input().split())
# # 读取每个手动启动事件的时刻和发动机编号
# start_info = [tuple(map(int, input().split())) for _ in range(E)]

# # 计算并输出最后启动的发动机
# find_last_started_engines(N, E, start_info)

# class TreeNode:
#     def __init__(self, value):
#         self.value = value
#         self.left = None
#         self.middle = None
#         self.right = None

# def insert_node(root, num):
#     """
#     插入节点的递归函数
#     """
#     # 没有根节点，创建新节点
#     if root is None:
#         return TreeNode(num)
#     # 如果插入的数小于当前节点数减去500，插入到左子树
#     if num < root.value - 500:
#         root.left = insert_node(root.left, num)
#     # 如果插入的数大于当前节点数加上500，插入到右子树
#     elif num > root.value + 500:
#         root.right = insert_node(root.right, num)
#     # 否则插入到中子树
#     else:
#         root.middle = insert_node(root.middle, num)
#     return root

# def height(root):
#     """
#     计算树的高度
#     """
#     # 如果节点为空，高度为0
#     if root is None:
#         return 0
#     # 计算左子树、中子树和右子树的高度
#     left_height = height(root.left)
#     middle_height = height(root.middle)
#     right_height = height(root.right)
#     # 树的总高度为最高的子树高度加1（当前节点的高度）
#     return max(left_height, middle_height, right_height) + 1

# # 输入描述
# N = int(input())  # 输入的数的个数
# nums = list(map(int, input().split()))  # 输入的数

# # 根据规则构造三叉搜索树
# root = None
# for num in nums:
#     root = insert_node(root, num)

# # 输出树的高度
# print(height(root))

# def find_longest_subsequence(sequence, target_sum):
#     # 将输入的字符串序列转换为整数列表
#     nums = list(map(int, sequence.split(',')))
#     n = len(nums)

#     # 创建前缀和数组
#     prefix_sum = [0] * (n + 1)

#     # 计算前缀和数组
#     for i in range(n):
#         prefix_sum[i + 1] = prefix_sum[i] + nums[i]

#     # 初始化最长长度为-1，表示未找到符合条件的子序列
#     max_length = -1

#     # 遍历所有可能的子序列区间，查找和为target_sum的最长子序列
#     for start in range(n):
#         for end in range(start, n):
#             # 计算子序列[start, end]的和
#             current_sum = prefix_sum[end + 1] - prefix_sum[start]
#             # 如果子序列的和等于target_sum，更新最长长度
#             if current_sum == target_sum:
#                 max_length = max(max_length, end - start + 1)

#     return max_length


# # 输入处理
# if __name__ == "__main__":
#     # 读取输入的序列
#     sequence = input().strip()
#     # 读取目标和
#     target_sum = int(input().strip())

#     # 调用函数并输出结果
#     result = find_longest_subsequence(sequence, target_sum)
#     print(result)

# def generate_permutations(current, nums, result):
#     if len(current) == len(nums):
#         result.append(current)
#     else:
#         for num in nums:
#             if num not in current:
#                 generate_permutations(current + [num], nums, result)

# def get_permutation(n, k):
#     nums = list(range(1, n + 1))
#     permutations = []
#     generate_permutations([], nums, permutations)
#     permutations.sort()
#     return ''.join(map(str, permutations[k - 1]))

# # 读取输入
# n = int(input())
# k = int(input())

# # 获取第k个排列
# kth_permutation = get_permutation(n, k)

# # 输出结果
# print(kth_permutation)

# def find_correct_words():
#     # 输入谜面单词列表和谜底库单词列表
#     err_words = input().split(",")
#     lib_words = input().split(",")

#     words_set = set(lib_words)  # 用于存储匹配到的正确单词的集合
#     result = []

#     for err_word in err_words:
#         err_chars = set(err_word)  # 谜面单词去重后的字符集合
#         found = False  # 标记是否找到匹配的谜底单词

#         for lib_word in lib_words:
#             # 判断谜底单词的字符集合与谜面单词去重后的字符集合是否相等
#             if len(set(lib_word)) == len(err_chars) and set(lib_word) == err_chars:
#                 result.append(lib_word)  # 将匹配到的谜底单词添加到结果列表中
#                 found = True  # 标记为找到匹配的谜底单词
#                 break

#         if not found:
#             result.append("not found")  # 如果未找到匹配的谜底单词，则添加 "not found" 到结果列表中

#     return result


# result = find_correct_words()

# if len(result) == 0:
#     print("not found")
# else:
#     print(",".join(result))  # 使用逗号连接结果列表，并打印最终结果


# def findAnswer(N, guesses):
#     possibleAnswers = set()  # 可能的答案集合
#     for i in range(10000):
#         digits = [int(x) for x in str(i).zfill(4)]  # 将数字i转换为四位数的列表形式
#         valid = True  # 判断数字i是否满足所有猜测的条件
#         for guess in guesses:
#             guessDigits = [int(x) for x in str(guess[0])]  # 将猜测数字guess转换为列表形式
#             a = guess[1]  # 位置正确的数字个数
#             b = guess[2]  # 数字正确但位置不对的个数
#             correct = 0  # 记录数字位置正确的个数
#             misplaced = 0  # 记录数字位置不对但数字正确的个数
#             digitCount1 = [0] * 10  # 记录数字i中每个数字的个数
#             digitCount2 = [0] * 10  # 记录猜测数字guess中每个数字的个数
#             for j in range(4):
#                 if digits[j] == guessDigits[j]:  # 判断数字i和猜测数字guess在相同位置是否相等
#                     correct += 1
#                 else:
#                     digitCount1[digits[j]] += 1
#                     digitCount2[guessDigits[j]] += 1
#             misplaced = sum(min(digitCount1[k], digitCount2[k]) for k in range(10))  # 计算数字位置不对但数字正确的个数
#             if a != correct or b != misplaced:  # 判断数字i是否满足当前猜测的条件
#                 valid = False
#                 break
#         if valid:
#             possibleAnswers.add(i)  # 如果数字i满足所有猜测的条件，则将其添加到可能的答案集合中
#     if len(possibleAnswers) == 1:
#         return str(possibleAnswers.pop()).zfill(4)  # 如果可能的答案集合中只有一个数字，则返回该数字作为答案
#     else:
#         return "NA"  # 如果可能的答案集合中有多个数字，则无法确定答案，返回NA作为结果

# N = int(input())  # 输入猜测次数
# guesses = []  # 保存每次猜测和结果的列表
# for _ in range(N):
#     guess, result = input().split()  # 输入猜测数字和结果
#     guesses.append((int(guess), int(result[0]), int(result[2])))  # 将猜测数字和结果添加到列表中
# print(findAnswer(N, guesses))  # 调用函数查找答案并输出结果


# def find_leftmost_substring(s1, s2, k):
#     n1 = len(s1)
#     n2 = len(s2)

#     # 统计s1中每个字母出现的次数
#     count_s1 = [0] * 26
#     for char in s1:
#         count_s1[ord(char) - ord('a')] += 1

#     # 统计滑动窗口中每个字母出现的次数
#     count_window = [0] * 26

#     # 初始化滑动窗口的起始位置和结束位置
#     start = 0
#     end = 0

#     while end < n2:
#         # 将当前字符加入滑动窗口
#         count_window[ord(s2[end]) - ord('a')] += 1

#         # 当滑动窗口的大小大于等于n1+k时，开始检查是否满足条件
#         if end - start + 1 >= n1 + k:
#             # 检查滑动窗口中每个字母的出现次数是否满足条件
#             if all(count_window[i] >= count_s1[i] for i in range(26)):
#                 return start  # 返回最左侧子串的起始位置

#             # 将滑动窗口的起始位置右移一位，并更新字母出现次数
#             count_window[ord(s2[start]) - ord('a')] -= 1
#             start += 1

#         end += 1  # 滑动窗口的结束位置右移一位

#     return -1  # 没有找到满足条件的子串，返回-1

# # 读取输入
# s1 = input()
# s2 = input()
# k = int(input())

# # 调用函数查找最左侧满足条件的子串的首个元素下标
# result = find_leftmost_substring(s1, s2, k)

# # 输出结果
# print(result)

