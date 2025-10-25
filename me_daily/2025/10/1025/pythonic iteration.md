# pythonic iteration

## 🚀 算法题中的实用遍历技巧

### 1. 快速初始化常用模式

#### 1.1 二维数组初始化
```python
# 传统方式 😢
matrix = []
for i in range(n):
    row = []
    for j in range(m):
        row.append(0)
    matrix.append(row)

# Pythonic 方式 ✨
matrix = [[0] * m for _ in range(n)]  # 正确！每行独立
# 错误示例：matrix = [[0] * m] * n  # 所有行共享同一个list！

# 带初始值的矩阵
matrix = [[i + j for j in range(m)] for i in range(n)]

# 无穷大矩阵（最短路径等）
dist = [[float('inf')] * n for _ in range(n)]
```

#### 1.2 字典/集合的快速初始化
```python
# 计数字典
from collections import defaultdict, Counter

# 传统方式
count = {}
for char in s:
    if char in count:
        count[char] += 1
    else:
        count[char] = 1

# Pythonic 方式
count = Counter(s)  # 一行搞定！
# 或者
count = defaultdict(int)
for char in s:
    count[char] += 1  # 不用检查key存在性

# 邻接表初始化
graph = defaultdict(list)
for u, v in edges:
    graph[u].append(v)
    graph[v].append(u)
```

### 2. 遍历技巧进阶

#### 2.1 enumerate 的高级用法
```python
# 找到所有峰值位置
peaks = [i for i, val in enumerate(arr[1:-1], 1) 
         if val > arr[i-1] and val > arr[i+1]]

# 同时遍历索引和值，还能自定义起始索引
for i, char in enumerate(s, 1):  # 从1开始计数
    print(f"第{i}个字符是{char}")
```

#### 2.2 zip 的神奇用法
```python
# 矩阵转置（行列互换）
matrix = [[1,2,3], [4,5,6]]
transposed = list(zip(*matrix))  # [(1,4), (2,5), (3,6)]
# 转回list形式
transposed = [list(row) for row in zip(*matrix)]

# 相邻元素配对
arr = [1, 2, 3, 4, 5]
pairs = list(zip(arr, arr[1:]))  # [(1,2), (2,3), (3,4), (4,5)]

# 多个数组同时遍历
for x, y, z in zip(arr1, arr2, arr3):
    result = x + y + z
```

#### 2.3 itertools 神器
```python
from itertools import product, combinations, permutations, chain

# 笛卡尔积（所有组合）
for i, j in product(range(n), range(m)):
    # 相当于双重循环，但更简洁
    matrix[i][j] = i * m + j

# 组合和排列
for combo in combinations([1,2,3,4], 2):  # 选2个的组合
    print(combo)  # (1,2), (1,3), (1,4), (2,3), (2,4), (3,4)

for perm in permutations([1,2,3]):  # 全排列
    print(perm)  # (1,2,3), (1,3,2), (2,1,3)...

# 扁平化嵌套列表
nested = [[1,2], [3,4], [5,6]]
flat = list(chain.from_iterable(nested))  # [1,2,3,4,5,6]
```

### 3. 条件遍历与过滤

#### 3.1 复杂条件的列表推导
```python
# 多条件过滤
valid_points = [(i, j) for i in range(n) for j in range(m) 
                if 0 <= i < n and 0 <= j < m and grid[i][j] != '#']

# 带else的条件表达式
processed = [x if x > 0 else 0 for x in arr]

# 嵌套条件
result = [x for x in arr if x > 0 if x % 2 == 0]  # 正数且偶数
```

#### 3.2 any() 和 all() 的妙用
```python
# 检查是否有解
has_solution = any(check_valid(state) for state in all_states)

# 检查所有条件
all_valid = all(x > 0 for x in arr)

# 矩阵中是否存在某个值
has_target = any(target in row for row in matrix)

# 检查回文
is_palindrome = all(s[i] == s[~i] for i in range(len(s)//2))
```

### 4. 高效的数据处理

#### 4.1 生成器表达式（内存友好）
```python
# 大数据量时用生成器，不占内存
total = sum(x*x for x in range(1000000))  # 不会创建百万元素的list

# 找第一个满足条件的元素
first_even = next((x for x in arr if x % 2 == 0), None)

# 惰性计算斐波那契数列
def fibonacci():
    a, b = 0, 1
    while True:
        yield a
        a, b = b, a + b

# 只取前10个
fib_10 = [next(fibonacci()) for _ in range(10)]
```

#### 4.2 字典推导的高级用法
```python
# 反转字典
original = {'a': 1, 'b': 2, 'c': 3}
reversed_dict = {v: k for k, v in original.items()}

# 过滤字典
filtered = {k: v for k, v in original.items() if v > 1}

# 字符串处理
char_positions = {char: i for i, char in enumerate(s)}

# 分组计数
from collections import defaultdict
groups = defaultdict(list)
for item in data:
    groups[item.category].append(item)
# 或者用字典推导
groups = {cat: [item for item in data if item.category == cat] 
          for cat in set(item.category for item in data)}
```

### 5. 算法题常见模式

#### 5.1 滑动窗口
```python
# 固定大小滑动窗口
window_sums = [sum(arr[i:i+k]) for i in range(len(arr)-k+1)]

# 或者更高效的方式
from collections import deque
window = deque(arr[:k])
result = [sum(window)]
for i in range(k, len(arr)):
    window.popleft()
    window.append(arr[i])
    result.append(sum(window))
```

#### 5.2 前缀和
```python
# 一维前缀和
prefix = [0]
for x in arr:
    prefix.append(prefix[-1] + x)

# 更简洁的方式
from itertools import accumulate
prefix = list(accumulate([0] + arr))

# 二维前缀和
prefix_2d = [[0] * (m + 1) for _ in range(n + 1)]
for i in range(1, n + 1):
    for j in range(1, m + 1):
        prefix_2d[i][j] = (matrix[i-1][j-1] + 
                          prefix_2d[i-1][j] + 
                          prefix_2d[i][j-1] - 
                          prefix_2d[i-1][j-1])
```

#### 5.3 图遍历
```python
# BFS 模板
from collections import deque

def bfs(start):
    queue = deque([start])
    visited = {start}
    
    while queue:
        node = queue.popleft()
        for neighbor in graph[node]:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)

# DFS 递归模板
def dfs(node, visited):
    if node in visited:
        return
    visited.add(node)
    for neighbor in graph[node]:
        dfs(neighbor, visited)
```

### 6. 性能优化小贴士

```python
# ❌ 慢：重复计算
result = [expensive_function(x) for x in arr for _ in range(n)]

# ✅ 快：缓存结果
cached_results = {x: expensive_function(x) for x in set(arr)}
result = [cached_results[x] for x in arr for _ in range(n)]

# ❌ 慢：字符串拼接
result = ""
for s in strings:
    result += s

# ✅ 快：join
result = "".join(strings)

# ❌ 慢：列表查找
if item in long_list:  # O(n)
    pass

# ✅ 快：集合查找
long_set = set(long_list)
if item in long_set:  # O(1)
    pass
```
