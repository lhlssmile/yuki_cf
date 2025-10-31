from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

t = II()

def solve_simple():
    n, X = map(int, input().split())
    prices = list(map(int, input().split()))
    
    total = sum(prices)
    levels = total // X  # 总共能达到的等级数
    
    # 按价格降序排列
    prices.sort(reverse=True)
    
    # 前levels个最大的价格就是奖励积分
    bonus_points = sum(prices[:levels])
    
    # 构造一个有效的购买顺序
    # 策略：小的物品先买，大的物品在关键时刻买
    small_items = prices[levels:]
    large_items = prices[:levels]
    
    result = []
    current_sum = 0
    large_idx = 0
    
    for level in range(1, levels + 1):
        target = level * X
        
        # 添加小物品直到接近目标
        while current_sum < target - large_items[large_idx] and small_items:
            item = small_items.pop()
            result.append(item)
            current_sum += item
        
        # 添加大物品触发等级增加
        result.append(large_items[large_idx])
        current_sum += large_items[large_idx]
        large_idx += 1
    
    # 添加剩余物品
    result.extend(small_items)
    
    return bonus_points, result

for _ in range(t):
    p, r = solve_simple()
    print(p)
    print(*r)