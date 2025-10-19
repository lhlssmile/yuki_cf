import sys
sys.setrecursionlimit(10 ** 7)
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

# def main():
#     n = II()
#     parent = [-1] + LII()
#     nums = LII()
#     for i in range(1, n):
#         if nums[i] >= 0 and (nums[parent[i]] == -1 or nums[parent[i]] >= nums[i]):
#             nums[parent[i]] = nums[i]
    
#     ans = 0
#     for i in range(n - 1, 0, -1):
#         if nums[i] != -1:
#             if nums[parent[i]] > nums[i]:
#                 print(-1)
#                 return
#             ans += nums[i] - nums[parent[i]]
#     print(ans + nums[0])
#     return
# if __name__ == "__main__":
#     main()

n = II()
par = [0] * (n + 1)
g = [[] for _ in range(n + 1)]
tmp = LII()
for i in range(2, n + 1):
    par[i] = tmp[i - 2]
    g[par[i]].append(i)
s = [0] + LII()

ans = 0
bad = False


def dfs(u, p):
    global ans, bad
    if s[u] == -1:
        if not g[u]:
            s[u] = s[p]
        else:
            mn = min(s[v] for v in g[u] if s[v] != -1)
            if mn < s[p]:
                bad = True
                return
            s[u] = mn
    ans += s[u] - s[p]
    if ans < 0:
        bad = True
        return
    for v in g[u]:
        dfs(v, u)
dfs(1, 0)
print(-1 if bad else ans)
            