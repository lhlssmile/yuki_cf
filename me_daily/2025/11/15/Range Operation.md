# Range Operation

题意
- 给定数组 `a[1..n]`，允许一次选择区间 `[l, r]`，将其中每个元素替换为常数 `(l + r)`，目标最大化数组总和。

增量公式与拆分
- 操作对总和的增量：
  - `delta(l, r) = (r - l + 1) * (l + r) - (P[r] - P[l-1])`，其中 `P` 为前缀和。
- 可拆解为仅与 `l`、`r` 分别相关的两部分：
  - `A(l) = -l^2 + l + P[l-1]`
  - `B(r) = r^2 + r - P[r]`
  - `delta(l, r) = A(l) + B(r)`，约束 `l ≤ r`。

线性扫描算法（O(n)）
- 扫描 `r = 1..n`，维护 `maxA_r = max_{1≤l≤r} A(l)`：
  - 每次把 `A(r)` 纳入候选更新 `maxA_r`。
  - 计算候选增量 `cand = maxA_r + B(r)`，更新全局 `max_delta`。
- 最终答案为 `base_sum + max(0, max_delta)`（允许不操作）。

实现（Python）
```python
import sys

def solve():
    input = sys.stdin.readline
    t = int(input())
    out_lines = []
    for _ in range(t):
        n = int(input())
        a = list(map(int, input().split()))

        P = [0] * (n + 1)
        for i in range(1, n + 1):
            P[i] = P[i - 1] + a[i - 1]

        base_sum = P[n]
        max_delta = 0
        maxA = -10**30

        for r in range(1, n + 1):
            A_r = -r * r + r + P[r - 1]
            if A_r > maxA:
                maxA = A_r
            B_r = r * r + r - P[r]
            cand = maxA + B_r
            if cand > max_delta:
                max_delta = cand

        out_lines.append(str(base_sum + max(0, max_delta)))
    print("\n".join(out_lines))

if __name__ == "__main__":
    solve()
```

复杂度与注意事项
- 复杂度 `O(n)`；前缀和一次，扫描一次。
- 使用大整数语言避免溢出（Python OK）。
- 初值 `maxA` 可取极小数，例如 `-10**30`。