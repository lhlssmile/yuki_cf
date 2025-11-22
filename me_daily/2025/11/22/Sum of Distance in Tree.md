
## 问题概述
LeetCode 834: *Sum of Distances in Tree*  
- **输入**：无向树（n 个节点，n-1 条无权边），求每个节点 u 到树中所有其他节点 v 的距离之和（ans[u] = ∑ dist(u, v) for all v）。  
- **约束**：1 ≤ n ≤ 10^5，时间复杂度需 O(n)。  
- **核心挑战**：暴力 O(n²) 超时，如何利用树结构实现高效计算？  

本笔记聚焦**算法思维过程**：从问题拆解到状态设计、转移公式，再到框架实现。适用于类似“树上距离/贡献”问题。笔记强调“怎么想”，非代码细节（代码见附录）。

---

## 1. 问题拆解：从全局视角识别“距离线性变化”
### 暴力思路与瓶颈
- **直观方法**：对每个节点 u，DFS/BFS 计算到所有 v 的距离，总时间 O(n²)。  
- **瓶颈分析**：树是连通无环图，距离计算有大量重复（子树路径）。n=10^5 时不可行。  

### 关键洞察：Rerooting（换根）技巧
- **全局性质**：总距离和 S = (1/2) × ∑ ans[u]（每对 (u,v) 双向计数）。但需计算每个 ans[u]。  
- **换根脑洞**：  
  - 任意选根 r=0，先 O(n) 计算 ans[0] = ∑ dist(0, v) for all v。  
  - 然后“滑动根”：从当前根 u 转移到其子节点 v 时，距离如何变化？  
    - v 的子树（sz[v] 个节点，包括 v）：每个节点到 v 的距离比到 u 少 1（路径缩短 u-v 边）。贡献：-sz[v]。  
    - 树外部分（n - sz[v] 个节点，包括 u）：每个节点到 v 的距离比到 u 多 1（路径延长 u-v 边）。贡献：+(n - sz[v])。  
    - **转移公式**：ans[v] = ans[u] + n - 2 × sz[v]（无权边，距离单位 1）。  
- **为什么高效？**：转移 O(1)，通过 DFS 遍历全树一次即可推导所有 ans[u]，总 O(n)。  
  - 类比：线性前缀和 S[i+1] = S[i] + a[i+1] - a[0]；树版用 sz[v] 模拟“局部规模偏移”。  

**自问 checklist**：  
- 重复计算在哪里？（子树距离）→ 如何复用？（预计算 sz + 公式转移）。  
- 全局 vs. 局部：全局攒 ans[根]，局部推 ans[子树]。  

---

## 2. 状态设计：最小化信息，聚焦子树与全局
### 核心状态定义
- **sz[u]**：以 u 为根的子树节点数（包括 u）。  
  - 作用：量化“局部规模”，用于距离偏移计算。  
- **ans[u]**：以 u 为根，到所有 v 的距离之和。  
  - 目标：输出数组 ans。  

### 设计原则
- **最小化**：仅需 O(n) 空间。避免复杂状态（如“父方向距离”），公式全依赖 sz。  
- **树 DP 套路**：  
  - Bottom-up：攒子树信息（sz）。  
  - Top-down：推全局视角（ans）。  
- **扩展性**：sz 捕捉节点数（非边权），便于边权变体。  

**自问 checklist**：  
- 状态是否“自洽”？（sz 易 bottom-up 攒，ans 易 top-down 推）。  
- 像前缀和？（sz = “段长”，ans = “累积值”）。  

---

## 3. 算法框架：两次 DFS，实现攒 + 推
### DFS1：Bottom-Up 攒取根信息（O(n)）
- **目标**：计算 sz 全数组 + ans[0]。  
- **过程**：  
  - 从根 0 递归遍历，深度 d = dist(0, u)。  
  - 每个节点 u：total_dist += d（全局累加 ans[0]）。  
  - 回溯：sz[u] = 1 + ∑ sz[孩子]。  
- **思维**：DFS 如“路径总账”——每个节点贡献其到根距离，全和即 ans[0]。  

伪代码：  
```
def dfs1(u, parent, depth):
    total_dist += depth
    sz[u] = 1
    for v in adj[u], v != parent:
        dfs1(v, u, depth + 1)
        sz[u] += sz[v]
dfs1(0, -1, 0)
ans[0] = total_dist
```

### DFS2：Top-Down 推导全 ans（O(n)）
- **目标**：从 ans[0] 转移到所有 u。  
- **过程**：  
  - 当前 u：ans[u] = curr_ans。  
  - 对每个孩子 v：new_ans = curr_ans + n - 2 * sz[v]，递归 dfs2(v, u, new_ans)。  
- **思维**：DFS 确保“上→下”顺序，无环。每个边遍历一次，O(1) 转移。  

伪代码：  
```
def dfs2(u, parent, curr_ans):
    ans[u] = curr_ans
    for v in adj[u], v != parent:
        new_ans = curr_ans + n - 2 * sz[v]
        dfs2(v, u, new_ans)
dfs2(0, -1, ans[0])
```

### 整体复杂度
- 时间：O(n)（两次 DFS）。  
- 空间：O(n)（adj + sz + ans）。  
- **验证技巧**：小树手算（如链状树 ans = [0,1,3,6,...]），检查 ∑ ans[u] = 2 × 总边贡献。  

**自问 checklist**：  
- 两次 DFS 顺序？（先攒后推）。  
- 公式来源？（子树 -1，外部 +1）。  

---

## 4. 扩展：边有权（Weighted Edges）变体
### 调整思路
- **无权特例**：每边 w=1。  
- **DFS1 改动**：深度 d 累加边权 w（u-v）。total_dist += 当前 d（到 u 的权路径和）。sz 不变（仍为节点数）。  
- **转移公式**：偏移 ±w（u-v 边权）。  
  - v 子树：-sz[v] × w。  
  - 外部：+(n - sz[v]) × w。  
  - **新公式**：ans[v] = ans[u] + (n - 2 × sz[v]) × w_{u-v}。  

### 实现提示
- 建图：adj[u] = [(v, w), ...]（edges 提供 [u,v,w]）。  
- DFS1：dfs1(v, u, d + w_uv)。  
- DFS2：new_ans = curr_ans + (n - 2 * sz[v]) * w_uv。  
- **复杂度**：仍 O(n)，sz 独立于权值。  
- **适用**：通用于“树上边权距离/贡献”问题（如网络延迟求和）。  

**自问 checklist**：  
- 权值影响？（DFS1 累加 w，公式乘 w）。  
- sz 作用？（节点数，非路径长）。  

---


### 模板复用
- 适用题：树上直径、节点贡献、rerooting DP。  
- **Checklist**：  
  - [ ] 暴力 O(n²) → sz + 公式。  
  - [ ] 状态：sz（局部）+ ans（全局）。  
  - [ ] 框架：DFS1 攒 + DFS2 推。  
  - [ ] 变体：× w（有权）。  


---

## Python 
```python
from typing import List

class Solution:
    def sumOfDistancesInTree(self, n: int, edges: List[List[int]]) -> List[int]:
        adj = [[] for _ in range(n)]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)
        
        ans = [0] * n
        sz = [0] * n
        total_dist = [0]
        
        def dfs1(u: int, p: int, d: int) -> None:
            total_dist[0] += d
            sz[u] = 1
            for v in adj[u]:
                if v != p:
                    dfs1(v, u, d + 1)
                    sz[u] += sz[v]
        
        dfs1(0, -1, 0)
        ans[0] = total_dist[0]
        
        def dfs2(u: int, p: int, curr_ans: int) -> None:
            ans[u] = curr_ans
            for v in adj[u]:
                if v != p:
                    new_ans = curr_ans + n - 2 * sz[v]
                    dfs2(v, u, new_ans)
        
        dfs2(0, -1, ans[0])
        return ans
```

---

