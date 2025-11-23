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
        MOD = 10**9 + 7
        q = II()
        s = SI()
        queries = [LII() for _ in range(q)]
        n = len(s)
        t = []           # 去0后的数字列表
        pos = [-1] * n   # s[i] 在 t 中的下标（如果不是0）
        
        for i, c in enumerate(s):
            if c != '0':
                pos[i] = len(t)
                t.append(int(c))
        
        m = len(t)
        if m == 0:
            return [0] * len(queries)
        
        
        prefix_sum = [0] * (m + 1)
        prefix_val = [0] * (m + 1)
        pow10 = [1] * (m + 2)
        
        for i in range(m):
            prefix_sum[i+1] = prefix_sum[i] + t[i]
            prefix_val[i+1] = (prefix_val[i] * 10 + t[i]) % MOD
            pow10[i+1] = pow10[i] * 10 % MOD
        
        def get_x(L: int, R: int) -> int:
            if L > R:
                return 0
            length = R - L + 1
            val = (prefix_val[R+1] - prefix_val[L] * pow10[length] % MOD + MOD) % MOD
            return val
        answer = []
        for l, r in queries:
            first = -1
            for i in range(l, r + 1):
                if s[i] != '0':
                    first = i
                    break
            if first == -1:
                answer.append(0)
                continue

            last = -1
            for i in range(r, l - 1, -1):
                if s[i] != '0':
                    last = i
                    break

            left_idx = pos[first]
            right_idx = pos[last]

            x = get_x(left_idx, right_idx)
            total_sum = prefix_sum[right_idx + 1] - prefix_sum[left_idx]
            answer.append(x * total_sum % MOD)
        
        return answer

    

if __name__ == "__main__":
    ans = main()
    print(*ans)