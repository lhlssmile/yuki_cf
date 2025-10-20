import sys
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

t = II()

for _ in range(t):
    n = II()
    res = [n - i for i in range(n)] + [0] * n

    for x in range(n, 0, -1):
        for j in range(n, 2 * n, x):
            if res[j] == 0: 
                res[j] = x
                break

    print(*res)