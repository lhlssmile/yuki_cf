from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()




t=II()
for _ in range(t):
   
    n,l,r=LII()
    

    prefix = list(range(n + 1))  
    prefix[r] = l - 1  
    

    a = [prefix[i] ^ prefix[i - 1] for i in range(1, n + 1)]
    
    # 输出
    print(' '.join(map(str, a)))



# t = II()

# for _ in range(t):
#     n,l,r = LII()
#     K = (1 << 29) - 1
#     prefix = [0] * (n + 1)

#     if l == 1:
#         prefix[0] = prefix[r] = 0
#         for i in range(1,r):
#             prefix[i] = K ^ i
#         for i in range(r+1,n+1):prefix[i] = K + i
#     else:
#         for i in range(l-1):prefix[i] = i
#         prefix[l-1]=K
#         for i in range(l,r):
#             prefix[i] = K ^ (i - (l - 1))
#         prefix[r]=K
#         for i in range(r+1,n+1):
#             prefix[i] = K + (i - r)
        

#         a = [0] * (n+1)
#         for i in range(1,n+1):
#             a[i] = prefix[i] ^ prefix[i-1]
    
#     print(*a[1:])
    
    

    