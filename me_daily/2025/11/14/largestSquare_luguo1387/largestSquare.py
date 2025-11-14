from sys import stdin
input = lambda: stdin.readline().strip()

n, m = map(int, input().split())
grid = [list(map(int, input().split())) for _ in range(n)]

# prefix[i][j]: grid 中 [0..i-1][0..j-1] 这一块的和
prefix = [[0] * (m + 1) for _ in range(n + 1)]

# 建前缀和
for i in range(n):
    for j in range(m):
        prefix[i+1][j+1] = (
            prefix[i+1][j] +
            prefix[i][j+1] -
            prefix[i][j] +
            grid[i][j]
        )

# 查询正方形和
def sum_square(x, y, k):
    # 左上(x, y)，边长 k
    x2 = x + k
    y2 = y + k
    return prefix[x2][y2] - prefix[x][y2] - prefix[x2][y] + prefix[x][y]

ans = 1  # 题目保证有至少一个 1

# 枚举边长（从大到小）
for k in range(min(n, m), 0, -1):
    found = False
    for i in range(n - k + 1):
        for j in range(m - k + 1):
            if sum_square(i, j, k) == k * k:  # 全为 1
                ans = k
                found = True
                break
        if found:
            break
    if found:
        break

print(ans)
