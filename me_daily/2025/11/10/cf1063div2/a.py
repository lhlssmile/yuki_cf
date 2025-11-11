'''
想一个策略保证a赢 结果非递减那么a赢
a odd-round / b even-round
只能交换ai/ai+1 要么就跳过 
n = even b操作odd 次 a操作even次 a最后一次操作
n = odd a/b都操作 (n - 1)/ 2次  b最后一次操作
Two players, Souvlaki and Kalamaki, are given a sequence $a$ of $n$ integers.

They will play a game that consists of $n-1$ rounds, which are numbered from $1$ to $n-1$. Souvlaki plays on odd-numbered rounds, and Kalamaki on even-numbered rounds.

On the $i$\-th round, a player can choose to take exactly **one** of the following actions:

-   Skip his turn and proceed to round $i+1$ (or finish the game if round $i$ was the last one).
-   Swap elements $a_i$ and $a_{i+1}$.

Souvlaki wins if after the end of the last round, $a$ is sorted in **non-decreasing** order. In other words, he wins if $a_i \le a_{i+1}$ holds for every $1 \le i < n$. Otherwise, Kalamaki wins.

However, Souvlaki does not like losing, so **before** the start of the game, he may re-order the elements of $a$ in anyway he wants. Is it possible for him to do so such that he has a guaranteed winning strategy?
'''

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
    t = II()
    for _ in range(t):
        n = II()
        a = LII()
        a.sort()
        poss = True
        for i in range(1, n, 2):
            if i + 1 < n and a[i] != a[i + 1]:
                poss = False
                break
        print("YES" if poss else "NO")


if __name__ == '__main__':
    main()
