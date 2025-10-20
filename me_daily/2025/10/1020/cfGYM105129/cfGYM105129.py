import sys
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()



pre = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47]
to_check = [1] + []
def prehandle():
    for x in pre:
        k = len(to_check)
        for i in range(k):
            to_check.append(to_check[i] * x)
    to_check.sort()
t = II()
def gcd(a, b: int):
    while b:
        a, b = b, a % b        
    return a
prehandle()
for _ in range(t):
    n = II()
    vis = [0] * 51
    a = LII()
    for x in a: vis[x] = 1
    
    for v in to_check:
        flg = True
        for i in range(0, 51):
            if gcd(v, i) == 1 and vis[i]:
                flg = False
                break
        if flg:
            print(v)
            break