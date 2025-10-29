from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

def main(): 
    n, m = LII()
    
    idxs1 = []
    idxs2 = []
    
    for i in range(1, m + 1):
        x, y = LII()
        if x < y: idxs1.append(i)
        else: idxs2.append(i)
    
    print('YES')
    
    if len(idxs1) > len(idxs2):
        print(len(idxs1))
        print(' '.join(map(str, idxs1)))
    else:
        print(len(idxs2))
        print(' '.join(map(str, idxs2)))
    
if __name__ == "__main__":
    main()