class Solution:
    def findMissingElements(self, nums: List[int]) -> List[int]:
        a = [0] * 101
        for x in nums:
            a[x] += 1
        mn, mx = min(nums), max(nums)
        ans = []
        for x in range(mn, mx):
            if a[x] == 0:
                ans.append(x)
        return ans