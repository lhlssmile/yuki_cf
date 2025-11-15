# Removal of a sequence

题意（easy 版）
- 初始序列为 `1..N`（`N = 10^{12}`）。重复 `x` 次操作：同时删除当前序列的第 `y, 2y, 3y, ...` 位置（基于当前长度）。
- 问最终序列的第 `k` 个数；若长度不足 `k`，输出 `-1`。

关键公式（单轮反向映射）
- 一轮删除后，保留下来的是每个长度为 `y` 的块中的前 `y-1` 个位置。
- 因此新序的第 `k` 个位置对应旧序索引：
  - `i = k + floor((k - 1) / (y - 1))`。

算法（迭代 x 次）
- 设 `idx = k`，重复 `x` 次执行 `idx ← idx + floor((idx - 1) / (y - 1))`，得到初始序列中的索引。
- 若过程中 `idx > N`，说明最终长度不足 `k`，输出 `-1`；否则输出 `idx`。
- 特判：`y = 1`，每轮都会删除所有位置，最终空，直接 `-1`。

实现（Python）
```python
import sys

def solve():
    input = sys.stdin.readline
    t = int(input())
    N = 10 ** 12
    for _ in range(t):
        x, y, k = map(int, input().split())
        if y == 1:
            print(-1)
            continue
        idx = k
        for _ in range(x):
            if idx > N:
                break
            idx += (idx - 1) // (y - 1)
        print(idx if idx <= N else -1)

if __name__ == "__main__":
    solve()
```

复杂度与示例
- easy 版给 `x ≤ 1e5`，每组迭代 `O(x)` 可承受。
- 例：`x=2, y=3, k=5`：`5 → 7 → 10`，答案 `10`。
- 大 `y` 时每轮增量约为 `idx/(y-1)`，若始终不越界则能给出大数结果；越界则输出 `-1`。