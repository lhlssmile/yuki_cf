from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()



def main() -> int:
        n = II()
        strs = [list(SI()) for _ in range(n)]
        # print(strs)
        m = len(strs[0])
        # print(n, m)
        a = [''] * n
        ans = 0
        for j in range(m):
            for i in range(n-1):
                if a[i] + strs[i][j] > a[i+1] + strs[i+1][j]:
                    ans+=1
                    break
            else:
                for i, s in enumerate(strs):
                    a[i] += s[j]
        print(ans)

if __name__ == "__main__":
    main()