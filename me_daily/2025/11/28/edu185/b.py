from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()



t = II()

for _ in range(t):
    n = II()
    b = LII()
    
    s = sum(b)
    p = sum(1 for x in b if x > 0)
    ans = min(s - (n - 1), p)
    print(ans)

# 思路：
    # - 做 n 次区间加一，总增量之和等于区间长度之和 S = sum(b)
    # - 恰好 n 次操作，区间长度都是正整数，所以 S >= n
    # - 要最大化某次操作的区间长度 L_max。上界一：把其他 (n-1) 次都取长度 1，则 L_max <= S - (n-1)
    # - 还需可重排得到 b。构造法：先用 (n-1) 个单点操作产生一个向量 s，满足 sum(s)=n-1；
    #   再选 L 个位置各 +1（对应那一次长区间覆盖的 L 个点），得到最终 a。
    #   为了 s 非负，必须从 b 中挑出 L 个正数把它们各减 1，所以 L <= 正数个数 p。
    # - 结论：答案 = min( S - (n - 1), p )，且由存在性保证 S >= n、p >= 1。

# 走一遍示例：n=5, b=[0,5,1,0,1]
# 1) 计算：S=sum(b)=7，p=正数个数=3，故 L_max=min(7-(5-1),3)=min(3,3)=3
# 2) 构造：目标是某次操作区间长度为 3，其余 4 次为单点
#    - 先选最终排列 a' 的一个具体序：把 b 重排为 a'=[1,1,5,0,0]（只需保持同一多重集合）
#    - 我们让“长区间”一次覆盖位置 [1..3]，它对 a' 的贡献是把这些位置各 +1
#    - 为了让剩余 4 次单点操作合计为 s（满足 sum(s)=4，且非负），令 s = a' 在 [1,2,3] 各减 1：s=[0,0,4,0,0]
#    - 单点 4 次都加在位置 3，就得到 a'=[1,1,5,0,0]
#    - 这时重排 a' 的元素即可得到原 b 的顺序 [0,5,1,0,1]
# 3) 对应的具体操作（在原下标上）可取：
#    - 区间 [1,3] 一次（长度 3）
#    - 单点 [3,3] 四次（长度 1）
#    - 结果向量是 [1,1,5,0,0]，与 b 的元素多重集合一致，因此可重排成 b
