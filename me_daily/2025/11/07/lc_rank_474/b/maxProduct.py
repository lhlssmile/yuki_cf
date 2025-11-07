def max_of_three(a: int, b: int, c: int) -> int:
    if a > b:
        if a > c:
            return a
    else:
        if b > c:
            return b
    return c

class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        
        s = sorted(nums)
        p1 = s[0] * s[1]
        p2 = s[-1] * s[-2]
        p3 = s[0] * s[-1]
        max_two = max(p1, p2)
        min_two = min(p1, p2, p3)
        
        orig_max = max_of_three(
            s[0] * s[1] * s[-1],
            s[-3] * s[-2] * s[-1],
            0
        )
        
        cand1 = 100000 * max_two
        cand2 = -100000 * min_two
        
        return max_of_three(orig_max, cand1, cand2)