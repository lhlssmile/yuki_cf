# Destruction of the Dandelion Fields

**提示：** 如何通过牺牲最少的元素来最大化剩余元素的和？

这是一道经典的贪心策略题。题目要求我们从数组中移除一些元素，使得剩余元素满足某种条件，并且剩余元素的和最大。

**核心思路：**

通过观察代码可以发现，这道题的关键在于处理奇数和偶数：
1. **偶数元素**：可以全部保留，直接加入答案
2. **奇数元素**：需要牺牲其中最小的 `⌊k/2⌋` 个（k为奇数个数）

**算法证明：**

设有k个奇数元素，题目的约束条件要求我们最多只能保留 `⌈k/2⌉` 个奇数。

为了最大化剩余元素的和：
- 偶数没有限制，全部保留：`sum_evens`
- 奇数需要牺牲 `⌊k/2⌋` 个，贪心选择最小的进行牺牲
- 保留的奇数和为：`sum_odds - sum_sacrificed`

因此最终答案为：`sum_evens + sum_odds - sum_sacrificed`

**贪心策略正确性：**

要使剩余元素和最大，就要使被移除元素和最小。在必须移除 `⌊k/2⌋` 个奇数的约束下，显然应该移除最小的那些奇数。

**边界情况：**
- 当k=0（没有奇数）时，直接返回0或所有偶数和
- 当k为奇数时，`⌊k/2⌋ = (k-1)/2`，保留 `(k+1)/2` 个奇数
- 当k为偶数时，`⌊k/2⌋ = k/2`，保留 `k/2` 个奇数

**时间复杂度：** O(n log n) - 主要是排序奇数数组  
**空间复杂度：** O(n) - 存储奇数和偶数数组

```cpp
ll solve(vll& a) {
    vll odds, evens;
    ll sum_e = 0;
    // 分离奇数和偶数
    for (auto x : a) {
        if (x % 2 == 0) {
            evens.pb(x);
            sum_e += x;  // 偶数全部保留
        } else {
            odds.pb(x);
        }
    }
    int k = odds.size();
    if (k == 0) return 0;
    
    SORT(odds);  // 排序，准备牺牲最小的
    ll sum_o = 0;
    for (auto x : odds) sum_o += x;
    
    int sac = k / 2;  // 需要牺牲的奇数个数
    ll sum_sac = 0;
    For(i, sac) sum_sac += odds[i];  // 牺牲最小的sac个
    
    return sum_o - sum_sac + sum_e;
}
```