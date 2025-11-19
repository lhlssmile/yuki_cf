from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

'''
给定一个target sum 找出存在的路径 只能是父-> 子
'''

class TreeNode:
    def __init__(self,val = 0, left = None, right = None):
        self.val = val
        self.right = right
        self.left = left



def main():
    # 这里应该用前/中/后序 插入node
    root = LII()
    target_sum = II()
    if not root: return 0
    prefix = {0: 1}
    ans = 0
    def dfs(node, curr_sum):
        nonlocal prefix
        if not node:
            return 0
        curr_sum += node.val
        
        target_prefix = target_sum - curr_sum
        res = prefix.get(target_prefix, 0)

        prefix[curr_sum] = prefix.get(curr_sum, 0) + 1
        res += dfs(node.left, curr_sum)
        res += dfs(node.right, curr_sum)
        if prefix[curr_sum] == 0:
            del prefix[curr_sum]
        return res

    return dfs(root, 0)

if __name__ == "__main__":
    main()