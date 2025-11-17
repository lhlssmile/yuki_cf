# 前缀和与子集和（SOS DP）

## 一维前缀和
- 定义：给定序列 `a[1..n]`，其前缀和 `S[i] = Σ_{j=1..i} a[j]`。
- 递推：`S[0] = 0`，`S[i] = S[i-1] + a[i]`。
- 区间查询：`sum(l, r) = S[r] - S[l-1]`，预处理 `O(n)`，单次查询 `O(1)`。

## 二维前缀和（容斥）
- 定义：矩阵前缀和 `S[i,j] = Σ_{i'≤i, j'≤j} A[i',j']`。
- 递推：`S[i,j] = A[i,j] + S[i-1,j] + S[i,j-1] - S[i-1,j-1]`。
- 子矩阵查询：左上 `(x1,y1)` 到右下 `(x2,y2)` 的和为：
  `sum = S[x2,y2] - S[x1-1,y2] - S[x2,y1-1] + S[x1-1,y1-1]`。

## 逐维前缀和（高维）
- 思想：将每一维依次做前缀累加，避免重复枚举所有维度组合。
- 复杂度：若维度为 `k`、每维大小为 `m`，总状态数 `N = m^k`，逐维累加总体 `O(k·N)`。

## 子集和（Sum Over Subsets, SOS）
- 场景：在大小为 `n` 的集合的全体子集上定义函数 `f`，要求 `g(S) = Σ_{T ⊆ S} f(T)`。
- 状压：用长度为 `n` 的二进制串表示子集 `S`，即 `mask ∈ [0, 2^n)`，第 `i` 位表示元素是否在集合中。
- 包含关系与坐标：`T ⊆ S ⇔ ∀i, t_i ≤ s_i`，因此对所有子集求和等价于在 `n` 维 0/1 数组上做逐维前缀和。
- 经典转移：令 `g = f` 初值，枚举位 `i` 和所有 `mask`，若 `mask` 的第 `i` 位为 1，则有
  `g[mask] += g[mask ^ (1<<i)]`，完成后 `g[mask] = Σ_{sub ⊆ mask} f[sub]`。
- 复杂度：`O(n · 2^n)`；空间 `O(2^n)`。

### 代码示例（C++）
```cpp
// g[mask] = Σ f[sub] (sub ⊆ mask)
vector<long long> sos_sum_subsets(vector<long long> f, int n) {
    int N = 1 << n;
    vector<long long> g = f;
    for (int i = 0; i < n; ++i) {
        for (int mask = 0; mask < N; ++mask) {
            if (mask & (1 << i)) {
                g[mask] += g[mask ^ (1 << i)];
            }
        }
    }
    return g;
}
```

### 常见变体
- 超集和：`g[mask] = Σ f[sup] (mask ⊆ sup)`，转移改为若第 `i` 位为 0，则 `g[mask] += g[mask | (1<<i)]`。
- 计数/最大值：将“加法”替换为其他幺半群操作（例如取最大、布尔或）也常见，但需保证操作满足逐维累积的可合并性。

### 典型应用
- 统计满足约束的子集数量或总权值（如字母集合、位约束、掩码兼容性）。
- 预处理所有子集的贡献，供后续 `O(1)` 查询某一掩码的累计值。

### 练习链接
- LeetCode 1178：Number of Valid Words for Each Puzzle — 位掩码与子集枚举，可用 SOS 思路优化。
- Codeforces 165E：Compatible Numbers — 经典 SOS DP。
- Codeforces 449D：Jzzhu and Numbers — 按位计数与 SOS 的组合。
- 洛谷镜像：CF165E https://www.luogu.com.cn/problem/CF165E，CF449D https://www.luogu.com.cn/problem/CF449D。

### 提示
- 输入规模常为 `n ≤ 20` 或 `n ≤ 22`，因此 `2^n` 级别可接受；注意 `long long` 防止溢出。
- 若只需要部分掩码的结果，可结合枚举子集 `sub = (sub-1) & mask` 技巧减少常数，但 SOS 更适合全量预处理。