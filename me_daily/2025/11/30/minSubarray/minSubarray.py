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
        n,p = LII()
        nums = LII()

        prefix = [0] * (n + 1)
        for i in range(n):prefix[i+1] = (prefix[i]+nums[i])%p 
        if prefix[n] == 0: return 0
        target = prefix[n]
        print(*prefix)
        print(target)
        mod_to_max_idx = {}
        mod_to_max_idx[0] = 0
        min_len = float('inf')
        print("--------")
        for i in range(1,n+1):
            needed = (prefix[i]-target+p)%p
            print(needed)
            if needed in mod_to_max_idx:
                l = i - mod_to_max_idx[needed]
                if 0 < l < n:
                    min_len = min(min_len, l)
                    print(min_len)
            mod_to_max_idx[prefix[i]] = i
        return min_len if min_len != float('inf') else -1


if __name__ == "__main__": print(main())