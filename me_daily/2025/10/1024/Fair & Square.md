# Fair & Square

## 题目描述

**Codeforces Gym 106129 Problem F - Fair & Square**

给定一个 `h × w` 的网格，其中包含 `#`（障碍物）和 `.`（空地）。你需要找到**最大的正方形边长 `s`**，使得所有的 `#` 都可以被边长为 `s` 的正方形完全覆盖（无重叠）。

**输入格式：**
- 第一行：`h w`（网格的高和宽）
- 接下来 `h` 行：每行 `w` 个字符，表示网格

**输出：**
- 一个整数，表示最大的正方形边长

**示例：**
```
输入：
4 7
####...
####.##
.######
.####..

输出：
2
```

## 核心思路分析

### 1. 问题理解与建模

**问题本质：**
- 将所有 `#` 用若干个 `s×s` 的正方形完全覆盖
- 正方形之间不能重叠
- 求最大可能的 `s`

**关键观察：**
1. **总数约束**：如果总共有 `total` 个 `#`，那么需要 `total/(s*s)` 个正方形
2. **完美分割**：`total` 必须能被 `s*s` 整除
3. **贪心策略**：从大到小尝试可能的 `s` 值
4. **几何约束**：`s` 不能超过 `min(h, w)`

### 2. 算法设计

**分治 + 贪心 + 验证：**

1. **预处理**：统计总的 `#` 数量 `total`
2. **候选生成**：找出所有可能的 `s` 值（`s*s` 是 `total` 的因子）
3. **从大到小验证**：对每个候选 `s`，检查是否能完美覆盖
4. **贪心覆盖**：从左上角开始，遇到未覆盖的 `#` 就放置一个 `s×s` 正方形

## C++ 代码实现详解

### 核心算法结构：

```cpp
void solve(int h, int w, const vector<vector<char>>& a) {
    // 1. 统计总的 '#' 数量
    int total = 0;
    For(i, h) For(j, w) if (a[i][j] == '#') total++;
    
    if (total == 0) {
        cout << 0 << endl;
        return;
    }
    
    // 2. 构建前缀和数组（优化矩形求和）
    vector<vector<int>> prefix(h + 1, vector<int>(w + 1, 0));
    For(i, h) FOR(j, 0, w) {
        int val = (a[i][j] == '#' ? 1 : 0);
        prefix[i + 1][j + 1] = prefix[i][j + 1] + prefix[i + 1][j] 
                              - prefix[i][j] + val;
    }
    
    // 3. 找出所有可能的边长 s
    vector<ll> divs;
    for (ll i = 1; i * i <= total; ++i) {
        if (total % i == 0) {
            divs.pb(i);
            if (i != total / i) divs.pb(total / i);
        }
    }
    
    vector<int> poss_s;
    int mn = min(h, w);
    for (auto d : divs) {
        ll sq = (ll)(sqrt((double)d) + 0.5);
        if (sq * sq == d && sq >= 1 && sq <= mn) {
            poss_s.pb((int)sq);
        }
    }
    
    // 4. 从大到小验证
    SORT(poss_s);
    reverse(ALL(poss_s));
    
    for (int s : poss_s) {
        if (can_tile(s)) {
            cout << s << endl;
            return;
        }
    }
    cout << 1 << endl;
}
```

### 关键函数：验证函数 `can_tile(s)`

```cpp
auto can_tile = [&](int s) -> bool {
    vector<vector<char>> covered(h, vector<char>(w, 0));
    
    For(i, h) {
        For(j, w) {
            // 遇到未覆盖的 '#'
            if (a[i][j] != '#' || covered[i][j]) continue;
            
            // 检查是否能放置 s×s 正方形
            if (i + s > h || j + s > w) return false;
            
            // 使用前缀和快速检查正方形内是否全为 '#'
            int r1 = i + 1, c1 = j + 1, r2 = i + s, c2 = j + s;
            if (rect_sum(r1, c1, r2, c2) != s * s) return false;
            
            // 检查是否有重叠
            bool ok = true;
            For(di, s) {
                if (!ok) break;
                For(dj, s) {
                    if (covered[i + di][j + dj]) {
                        ok = false;
                        break;
                    }
                }
            }
            if (!ok) return false;
            
            // 标记为已覆盖
            For(di, s) For(dj, s) covered[i + di][j + dj] = 1;
        }
    }
    return true;
};
```

### 优化技巧：

1. **前缀和优化**：`O(1)` 时间计算矩形内 `#` 的数量
2. **因子枚举优化**：只枚举到 `√total`，避免重复
3. **浮点精度处理**：`sqrt((double)d) + 0.5` 避免精度误差
4. **贪心顺序**：从大到小尝试，找到第一个可行解即为最优

