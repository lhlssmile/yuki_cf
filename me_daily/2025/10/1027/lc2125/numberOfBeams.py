from collections import defaultdict
from typing import List
import sys
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()



def main():
    n = II()
    bank = [LSI() for _ in range(n)]
    cnts = [row.count('1') for row in bank if '1' in row]
    return sum(cnts[i - 1] * cnts[i] for i in range(1, len(cnts)))