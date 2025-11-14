import sys

input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

'''
L = 2n - 2, L - n = n - 2. 连续段共有l - n + 1个起始点
n = 4 -> 6 l - n + 1 = 3

'''

def count_ways(n: int) -> int:
    # 公式：答案 = (9n - 3) * 4^(n - 3)
    return (9 * n - 3) * pow(4, n - 3)

def solve():
    n = II()
    print(count_ways(n))

if __name__ == "__main__":
    solve()

