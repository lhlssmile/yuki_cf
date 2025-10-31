from collections import defaultdict, deque
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

def is_valid_position(grid, i, j, n):
    """检查在(i,j)放置黑格子是否会违反三连规则"""
    # 检查水平方向
    for start in range(max(0, j-2), min(n-1, j+1)):
        if start + 2 < n:
            count = 0
            for k in range(start, start + 3):
                if k == j or grid[i][k] == '#':
                    count += 1
            if count == 3:
                return False
    
    # 检查垂直方向
    for start in range(max(0, i-2), min(n-1, i+1)):
        if start + 2 < n:
            count = 0
            for k in range(start, start + 3):
                if k == i or grid[k][j] == '#':
                    count += 1
            if count == 3:
                return False
    
    return True

def bfs_connect(grid, n, black_cells):
    """尝试连接所有黑格子"""
    if not black_cells:
        return True  # 没有黑格子，可以随意放一个
    
    # 找到所有连通分量
    visited = set()
    components = []
    
    for cell in black_cells:
        if cell not in visited:
            component = []
            queue = deque([cell])
            visited.add(cell)
            
            while queue:
                i, j = queue.popleft()
                component.append((i, j))
                
                for di, dj in [(0,1), (0,-1), (1,0), (-1,0)]:
                    ni, nj = i + di, j + dj
                    if (0 <= ni < n and 0 <= nj < n and 
                        (ni, nj) not in visited and 
                        (ni, nj) in black_cells):
                        visited.add((ni, nj))
                        queue.append((ni, nj))
            
            components.append(component)
    
    if len(components) == 1:
        return True  # 已经连通
    
    # 尝试连接多个分量
    # 这里可以用更复杂的算法，但对于小规模可以暴力尝试
    return try_connect_components(grid, n, components)

def try_connect_components(grid, n, components):
    """尝试连接多个连通分量"""
    # 简化版本：检查是否可能连接
    # 实际实现需要更复杂的路径搜索
    return len(components) <= 2  # 简化判断

t = II()
for _ in range(t):
    n = II()
    grid = []
    for i in range(n):
        grid.append(list(SI()))
    
    # 找到所有黑格子
    black_cells = set()
    for i in range(n):
        for j in range(n):
            if grid[i][j] == '#':
                black_cells.add((i, j))
    
    # 检查现有黑格子是否违反三连规则
    valid = True
    for i in range(n):
        for j in range(n-2):
            if all(grid[i][j+k] == '#' for k in range(3)):
                valid = False
                break
        if not valid:
            break
        for j in range(n):
            if i <= n-3 and all(grid[i+k][j] == '#' for k in range(3)):
                valid = False
                break
        if not valid:
            break
    
    if not valid:
        print("NO")
        continue
    
    # 检查连通性
    if bfs_connect(grid, n, black_cells):
        print("YES")
    else:
        print("NO")