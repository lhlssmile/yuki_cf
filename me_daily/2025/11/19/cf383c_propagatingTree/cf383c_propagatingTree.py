from collections import defaultdict  # 备着
from typing import List  # 备着
import sys
from collections import Counter  # 备着

# 输入加速
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

# Fenwick Tree：点加 + 前缀sum（O(log n)）
class FenwickTree:
    def __init__(self, size):
        self.size = size  # Fix: self.size防全局n坑
        self.t = [0] * (size + 2)
    
    def add(self, i, w):  # 更新：i加w，向上爬树
        while i <= self.size:  # Fix: <= self.size
            self.t[i] += w
            i += i & -i
    
    def sum(self, i):  # 前缀sum(1~i)，向下爬树
        r = 0
        while i > 0:
            r += self.t[i]
            i -= i & -i
        return r

# 主逻辑（测试版：n m第一行，无q行）
n, m = LII()  # n节点, m操作

a = [0] + LII()  # a[1..n]初始值

g = [[] for _ in range(n + 1)]  # adj图
for _ in range(n - 1):
    u, v = LII()
    g[u].append(v)
    g[v].append(u)  # 双向

# 非递归DFS：栈模拟，算in/out/dep（Euler Tour时间戳）
in_, out_, dep_, state = [0] * (n + 1), [0] * (n + 1), [0] * (n + 1), [0] * (n + 1)
st = []  # 栈：(u, p)
st.append((1, 0))  # 根1, 假父0
timer = 1
while st:
    u, p = st[-1]; st.pop()  # pop最后（LIFO）
    if state[u] == 0:  # 第一次：进入
        state[u] = 1
        dep_[u] = dep_[p] + 1 if p else 0  # 深度（根0）
        in_[u] = timer  # in时间
        timer += 1
        st.append((u, p))  # 推回u，等孩子后出
        for v in g[u]:  # 正序push孩子（ok，DFS序仍保子树连续）
            if v != p:  # 防父回溯
                st.append((v, u))
    else:  # 第二次：离开
        out_[u] = timer  # out时间（下一个timer）

ft = FenwickTree(n)  # 建BIT，全0（path_sum初始0）

# 处理m操作
for _ in range(m):  # Fix: for _ in range(m): op = LII()
    op = LII()
    if op[0] == 1:  # 更新1 u w
        u, w = op[1], op[2]
        s = 1 if dep_[u] % 2 == 0 else -1  # 符号：even+1 odd-1（标准，可翻但一致）
        delta = w * s  # Fix: delta = w * s（统一交替）
        ft.add(in_[u], delta)  # +delta at in[u]
        if out_[u] <= n:  # 安全：out<=n才-
            ft.add(out_[u], -delta)  # -delta at out[u]（差分，子树范围加）
    else:  # 查询2 u
        u = op[1]
        s = 1 if dep_[u] % 2 == 0 else -1  # 同s
        delta = ft.sum(in_[u])  # path_sum = sum祖先delta
        print(a[u] + s * delta)  # 值 = 初始 + s[u] * path（交替公式）

# 工具验证：你的输入输出3\n3\n0（a1=1+2=3; a2=2+3-2=3; a4=1-3+2=0）