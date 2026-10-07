# while True:
#     try:
#         nums = list(map(str, input().split()))
#         count = [0] * 10  # 记录每个数字一共出现了多少次
#         for n in nums:
#             for j in n:
#                 count[int(j)] += 1
#         res = ""
#         # 一般来说，数字肯定是从大到小放，并且大的数字尽可能全部放在高位，所以将count中最大的数先放完，然后再放剩下的中最大的，一直到放完
#         # 特殊情况呢？ 如果只有0有count，那么答案就是0
#         # 还有没有其它特例呢？
#         if count[0] > 0 and all(count[i] == 0 for i in range(1, 10)):
#             print("0")
#             break
        
#         for c in range(9, -1, -1):
#             if count[c] == 0:
#                 continue
#             res += str(c)*count[c]
#             count[c] = 0
        
#         print(res)
#     except:
#         break

from functools import reduce
from math import isqrt
from operator import xor
from typing import List

class Solution:
    def xorAfterQueries(self, nums: List[int], queries: List[List[int]]) -> int:
        MOD = 1_000_000_007
        n = len(nums)
        B = isqrt(len(queries))
        diff = [None] * B
        has = [None] * B

        for l, r, k, v in queries:
            if k < B:
                # 懒初始化
                if not diff[k]:
                    diff[k] = [1] * (n + k)
                    has[k] = [False] * k
                has[k][l % k] = True
                diff[k][l] = diff[k][l] * v % MOD
                r = r - (r - l) % k + k
                diff[k][r] = diff[k][r] * pow(v, -1, MOD) % MOD
            else:
                for i in range(l, r + 1, k):
                    nums[i] = int(nums[i] * v % MOD)

        for k, d in enumerate(diff):
            if not d:
                continue
            for start, b in enumerate(has[k]):
                if not b:
                    continue
                mul_d = 1
                for i in range(start, n, k):
                    mul_d = mul_d * d[i] % MOD
                    nums[i] = int(nums[i] * mul_d % MOD)

        return reduce(xor, nums)

if __name__ == '__main__':
    nums = [1,1,1]
    queries = [[0,2,1,4]]
    print(Solution().xorAfterQueries(nums, queries))