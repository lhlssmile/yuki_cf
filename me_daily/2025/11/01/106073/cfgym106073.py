from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()
MOD = 10 ** 9 + 7

def main(): 
    n, q = LII()
    nums = LII()
    mod = 10 ** 9 + 7
    rev2 = (mod + 1) // 2
    
    ans = [0] * (n + 1)
    
    cur = 0
    for v in reversed(nums):
        ans[v] = (ans[v] + cur * rev2) % mod
        cur = (cur + v) * rev2 % mod
    
    ans[1] = (ans[1] + cur) % mod
    
    print(*ans[1:], sep='\n')

if __name__ == "__main__":
    main()