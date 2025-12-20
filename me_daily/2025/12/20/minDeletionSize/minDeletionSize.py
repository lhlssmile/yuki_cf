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
    n = II()
    strs = [SI() for _ in range(n)]
    m = len(strs[0])
    # print(*strs)
    def is_sorted(col):
        for i in range(1, len(col)):
            if col[i] < col[i-1]:
                return False
        return True
    
    cnt = 0
    for j in range(m):
        col = [s[j] for s in strs]
        if not is_sorted(col):
            cnt += 1
    print(cnt)

if __name__ == "__main__":
    main()
