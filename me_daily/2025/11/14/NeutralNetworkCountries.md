# Neutral Network Countries

题意（简化版）
- 有 `l` 层，每层有 `n` 个城市。
- 从 `start` 到第一层城市 `j` 的代价为 `in[j]`。
- 从上一层任意城市到下一层“目的城市 j”的代价为 `between[j]`（只依赖目的城市，不依赖起点）。
- 从最后一层城市 `j` 到 `exit` 的代价为 `out[j]`。
- 统计所有路径的总代价对 `m` 取模等于 `0` 的条数，答案对 `1e9+7` 取模。

核心建模
- 只关心“当前总代价的模 `m` 余数”，用长度为 `m` 的向量表示状态。
- 起始一步（`start → 第1层`）：把 `in` 按余数分组，得到初始向量 `V1[r]`。
- 层间转移（`第i层 → 第i+1层`，仅依赖目的城市）：从当前余数 `b` 加上目的城市的代价余数 `r` 到达 `a` 的条件是 `a ≡ b + r (mod m)`。因此转移矩阵 `T` 是循环矩阵：
  - 令 `cnt_between[r]` 是 `between` 中余数为 `r` 的目的城市数。
  - 则 `T[a][b] = cnt_between[(a - b) mod m]`。
  - ex: T(0, 11/12) b=11/12,a = 0: 
- 共有 `l-2` 次中间层间转移（从第1层到第(l-1)层），用矩阵快速幂得到 `V_prev = T^(l-2) * V1`。
- 最后一跳（`第l层 → exit`）：目的城市还是同一个 `j`，这一步的增量是 `between[j] + out[j]`（必须绑定同一城市），把其按余数分组得到 `cnt_final[s]`，其中 `s = (between[j] + out[j]) % m`。
- 最终答案：`ans = sum_r V_prev[r] * cnt_final[(-r) % m]`。

为什么不是 `l-1` 次转移、也不是 `V_mid ⊗ out`？
- 如果把所有 `l-1` 次 between 都合并到矩阵里，再和 `out` 的余数计数做卷积，会丢失“最后一步目的城市是谁”的信息；`out[j]` 必须和同一个 `j` 的 `between[j]` 搭配使用。因此要把最后一步从矩阵转移中剥离出来，按 `between[j] + out[j]` 聚合后再与 `V_prev` 卷积。

边界与正确性
- `l == 1`：没有 between 步，初始向量 `V1` 与 `out` 做卷积即可（此时 `cnt_final[s]` 就是 `out` 的余数计数）。
- `l == 2`：没有中间转移，直接 `V_prev = V1`，最后一步用 `between[j] + out[j]` 聚合。
- 所有计数均对 `1e9+7` 取模；所有余数运算对 `m` 取模。

复杂度
- 矩阵乘法 `O(m^3)`，快速幂次数约 `O(log l)`，总体 `O(m^3 log l)`，在常见约束下可接受。

关键代码（Python 片段）
```python
mod = 10 ** 9 + 7

def count_residues(arr, m):
    cnt = [0] * m
    for x in arr:
        cnt[x % m] = (cnt[x % m] + 1) % mod
    return cnt

def mat_mul(A, B):
    n = len(A)
    C = [[0] * n for _ in range(n)]
    for i in range(n):
        for k in range(n):
            if A[i][k]:
                for j in range(n):
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod
    return C

def mat_pow(A, e):
    n = len(A)
    R = [[0] * n for _ in range(n)]
    for i in range(n):
        R[i][i] = 1
    while e:
        if e & 1:
            R = mat_mul(R, A)
        A = mat_mul(A, A)
        e >>= 1
    return R

# 构造初始向量与转移矩阵
V1 = count_residues(in_, m)
cnt_between = count_residues(between, m)
T = [[0] * m for _ in range(m)]
for a in range(m):
    for b in range(m):
        T[a][b] = cnt_between[(a - b) % m]

# 中间转移 l-2 次
steps_mid = l - 2
if steps_mid > 0:
    Tp = mat_pow(T, steps_mid)
    # 向量乘法
    Vprev = [sum(Tp[i][j] * V1[j] for j in range(m)) % mod for i in range(m)]
else:
    Vprev = V1

# 最后一跳按 between[j] + out[j] 聚合
if l == 1:
    cnt_final = count_residues(out, m)
else:
    cnt_final = [0] * m
    for j in range(n):
        s = (between[j] + out[j]) % m
        cnt_final[s] = (cnt_final[s] + 1) % mod

ans = sum(Vprev[r] * cnt_final[(-r) % m] for r in range(m)) % mod
```

示例自检
- 输入：`n=2, l=3, m=13; in=[4,6]; between=[2,1]; out=[3,4]`
- 初始向量：`V1[4]=1, V1[6]=1`。
- 中间一步：`l-2=1`，传播后得到 `Vprev` 余数为 `5,6,7,8` 各 `1`。
- 最后一跳：`s_j = (between[j] + out[j]) % 13`，两个城市均为 `5`，`cnt_final[5]=2`。
- 答案：`ans = Vprev[8] * 2 = 2`，与期望一致。

常见坑
- 把所有 `l-1` 次 between 都放进矩阵里、最后再与 `out` 卷积，会错误地忽略“最后一步目的城市与 out[j] 的绑定关系”，造成误计。
- 转移矩阵构造不需要额外乘以 `n`：每个目的城市只对应一条到它的边，按余数计数即可。

一句话总结
- 用余数向量表示状态，层间是循环矩阵，矩阵快速幂做 `l-2` 次中间转移，最后一步把 `between[j] + out[j]` 绑定在一起做卷积，保证目的城市一致。