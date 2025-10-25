
## 1. 为什么Pythonic？
- **简洁**：一行顶三for，少缩进/嵌套。
- **高效**：生成器不存全list（内存O(1)），comp并行潜力大。
- **可读**：像英文“收集所有满足if的i,j”，一眼懂。
- **坏处**：超嵌套comp难读（>3层别强求，回for）；性能微差（但99%无感）。
- **何时用**：遍历/过滤/转换数据时；建list/dict/set；sum/count等聚合。

## 2. 基础：List/Dict/Set Comp
**语法**：`[expr for var in iterable if cond]`（expr=输出，var=变量，iterable=源，cond=滤）。
- 嵌套：`[expr for i in outer for j in inner if ...]`（扁平一层）。
- Dict：`{k: v for ...}`；Set：`{expr for ...}`。

**例1：总'#'数（total）**
- 老for：  
  ```python
  total = 0
  for i in range(h):
      for j in range(w):
          if a[i][j] == '#': total += 1
  ```
- Pythonic：  
  ```python
  total = sum(1 for i in range(h) for j in range(w) if a[i][j] == '#')  # 生成器+sum，内存神！
  # 或全list：total = len([1 for i in range(h) for j in range(w) if a[i][j] == '#'])  # 但sum更好
  ```
  **为什么牛**：一行！生成器懒算，只迭代'#'多时。

**例2：收集'#'位置（hash_pos = [(i,j)]）**
- 老for：  
  ```python
  hash_pos = []
  for i in range(h):
      for j in range(w):
          if a[i][j] == '#': hash_pos.append((i, j))
  ```
- Pythonic：  
  ```python
  hash_pos = [(i, j) for i in range(h) for j in range(w) if a[i][j] == '#']
  # 带条件变体：[(i,j) for i, row in enumerate(a) for j, cell in enumerate(row) if cell == '#']  # 无range！
  ```

**例3：Dict：按行'#'计数**
- Pythonic：  
  ```python
  row_counts = {i: sum(1 for j in range(w) if a[i][j] == '#') for i in range(h)}
  ```

## 3. 生成器表达式（GenExp）：懒猫的懒加载
- 像comp但用`()`：`(expr for var in iterable)`，不存list，按需yield。
- 完美sum/any/all/min/max，内存O(1)。

**例：检查每行全'#'？**
- 老for：  
  ```python
  full_rows = []
  for i in range(h):
      is_full = True
      for j in range(w):
          if a[i][j] != '#': is_full = False; break
      if is_full: full_rows.append(i)
  ```
- Pythonic：  
  ```python
  full_rows = [i for i in range(h) if all(a[i][j] == '#' for j in range(w))]  # all+genexp！
  # 超简：full_rows = [i for i, row in enumerate(a) if all(cell == '#' for cell in row)]
  ```

**例：链式
- 从divs滤s：  
  ```python
  poss_s = [s for d in divs if (s := int(math.sqrt(d)))**2 == d and s <= min(h,w)]
  # Walrus := (Py3.8+) 在if里算s复用！
  ```

## 4. enumerate & zip：
- **enumerate**：for i, item in enumerate(iterable[, start=0])  # 自动i！
- **zip**：for a,b in zip(seq1, seq2)  # 并行遍历。

**例：转置grid（a cols变rows）**
- 老for：  
  ```python
  transposed = [[] for _ in range(w)]
  for i in range(h):
      for j in range(w):
          transposed[j].append(a[i][j])
  ```
- Pythonic：  
  ```python
  transposed = [list(col) for col in zip(*a)]  # zip(*a)一键转置！list转list。
  # 详解：zip(a[0], a[1], ...) 但*a解包。
  ```

**例：比对两grid diff pos**
- Pythonic：  
  ```python
  diff_pos = [(i,j) for i in range(h) for j, (c1, c2) in enumerate(zip(a[i], b[i])) if c1 != c2]
  ```

## 5. map & filter：函数式风范
- **map(func, iterable)**：应用func每项，返iter。
- **filter(cond, iterable)**：滤True项，返iter。
- 转list：`list(map(...))`。

**例：grid全转0/1矩阵**
- 老for：  
  ```python
  nums = [[0]*w for _ in range(h)]
  for i in range(h):
      for j in range(w):
          nums[i][j] = 1 if a[i][j] == '#' else 0
  ```
- Pythonic：  
  ```python
  nums = [[1 if cell == '#' else 0 for cell in row] for row in a]  # comp最直！
  # map版：nums = list(map(lambda row: list(map(lambda c: 1 if c=='#' else 0, row)), a))
  # filter版（只'#'）：hash_cells = list(filter(lambda c: c=='#', [cell for row in a for cell in row]))
  ```

**例：divs（因子）优化**
- 老for：  
  ```python
  divs = []
  for i in range(1, total+1):
      if total % i == 0: divs.append(i)
  ```
- Pythonic：  
  ```python
  divs = list(filter(lambda i: total % i == 0, range(1, total+1)))  # 但O(total)慢
  # 更好：用sqrt如前，但filter思路。
  ```

## 6. 进阶：扁平2D & 嵌套转comp
- **扁平遍历**：`for i in range(h) for j in range(w)` → 单层`for i,j in product(range(h), range(w))`（from itertools）。
- **嵌套深**：>2层用itertools.chain/product；或递归gen（yield from）。

**例：所有s×s subgrid的top-left pos**
- Pythonic：  
  ```python
  from itertools import product
  sub_tops = [(i,j) for i in range(h - s + 1) for j in range(w - s + 1)]  # 简单comp
  # 产品：sub_tops = product(range(h - s + 1), range(w - s + 1))  # gen，list()转list
  ```

**坑警报**：
- **浅拷贝**：`[[0]*w for _ in range(h)]` ok；`[[0]*w]*h` 错（共享list）！
- **可变expr**：comp里append会错（immutable用）；用dict.setdefault。
- **性能**：comp慢于for（<1%case）；大N用numba。
- **可读阈**：3+条件→split多行：  
  ```python
  squares = [
      x**2 for x in range(10)
      if x % 2 == 0
      if x > 5
  ]
  ```
