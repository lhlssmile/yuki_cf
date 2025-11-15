# Drifting Way

题意
- 给定长度为 `n` 的字符串 `s`，每格为 `'<', '>'` 或 `'*'`（无流）。每分钟：有流则被推向该方向，无流则可自行左右。可任选起点。
- 求能停留在河中的最长时间；若可无限航行，输出 `-1`。

判无限（充要条件）
- 存在相邻对 `i, i+1` 使得同时满足：
  - `s[i] != '<'`（第 `i` 格不强制左，允许右或自由），且
  - `s[i+1] != '>'`（第 `i+1` 格不强制右，允许左或自由）。
- 这对相邻格可以双向往返，形成环，答案即 `-1`。

有限时的最大时间
- 若不存在上述相邻对，结构被强约束：整个串最多只有一个 `'*'`，且整体为“若干连续 `<` + 可选 `'*'` + 若干连续 `>`”。
- 若存在 `'*'`，设其位置为 `j`（1-based），最大时间为 `max(j, n - j + 1)`（向左到岸或向右到岸）。
- 若不存在 `'*'`，答案为 `max(前缀连续 '<' 的长度, 后缀连续 '>' 的长度)`。

实现（Python）
```python
import sys

def max_time(s: str) -> int:
    n = len(s)
    for i in range(n - 1):
        if s[i] != '<' and s[i + 1] != '>':
            return -1
    j = s.find('*')
    if j != -1:
        return max(j + 1, n - j)
    left = 0
    while left < n and s[left] == '<':
        left += 1
    right = 0
    while right < n and s[n - 1 - right] == '>':
        right += 1
    return max(left, right)

def solve():
    input = sys.stdin.readline
    t = int(input())
    ans = []
    for _ in range(t):
        s = input().strip()
        ans.append(str(max_time(s)))
    print("\n".join(ans))
```

复杂度
- 线性 `O(n)` 检查与计算；多组数据总长度也线性。

常见误区
- 用 DFS/记忆化判环在本题不必要；相邻对判定是更直接也更严密的充要条件。