from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


class ListNode:

    def __init__(self, val = 0, next = None):
        self.val = val
        self.next = next

def solve(nums: List[int], head: ListNode):
    dummy = ListNode(0, head)
    st = set(x for x in nums)
    cur = dummy
    while cur.next:
        nxt = cur.next
        if nxt.val in st:
            cur.next = nxt.next
        else:
            cur = cur.next
    return dummy.next
if __name__ == "__main__":
    nums = [1, 2, 3]
    head = [1, 2, 3, 4, 5]
    solve()