from sys import stdin
input = lambda: stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))

def find_odd_pair(odds):
    m = len(odds)
    if m < 2:
        return None
    # 检查相邻奇数：是否有 y < 2x
    for i in range(m - 1):
        x, y = odds[i], odds[i + 1]
        if y < 2 * x:
            return (x, y)
    # 无，则 n 小，暴力
    for i in range(m):
        for j in range(i + 1, m):
            x, y = odds[i], odds[j]
            if (y % x) % 2 == 0:
                return (x, y)
    return None

t = II()
for _ in range(t):
    n = II()
    a = LII() 
    odds = [ai for ai in a if ai % 2 == 1]
    evens = [ai for ai in a if ai % 2 == 0]
    
    if len(evens) >= 2:
        print(evens[0], evens[1])
        continue
    
    pair = find_odd_pair(odds)
    if pair:
        print(*pair)
        continue
    
    if not evens:
        print(-1)
        continue
    
    e = evens[0]
    smaller_odds = [o for o in odds if o < e]
    found = False
    for x in smaller_odds:
        if (e % x) % 2 == 0:
            print(x, e)
            found = True
            break
    if not found:
        print(-1)