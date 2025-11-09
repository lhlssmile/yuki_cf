// 题意：统计子数组数量，使得 target 在该子数组中出现次数严格大于子数组长度的一半（严格多数）。
// 关键转化：把等于 target 的元素记为 +1，不等于的记为 -1。
//   对子数组 [l..r]：target 严格多数 ⇔ (#target) > (len - #target)
//   ⇔ 2*#target > len ⇔ (#target) - (len - #target) > 0 ⇔ sum(+1/-1) > 0。
// 因此问题转化为：统计所有子数组的和 > 0 的数量。
// 记前缀和 P[k] = sum(vals[0..k-1])，则子数组 [l..r] 的和 = P[r+1] - P[l]。
// 和 > 0 ⇔ P[l] < P[r+1]。我们要统计所有有序对 (l, r+1) 满足 l < r+1 且 P[l] < P[r+1]。
// 这是经典的“前缀和对数计数”问题：依次遍历 j=r+1，从之前出现的前缀和值中数出严格小于 P[j] 的个数。
// 用坐标压缩 + Fenwick 树（树状数组）即可 O(n log n)。

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

struct Fenwick {
    int n;
    vector<long long> bit;
    Fenwick(int n) : n(n), bit(n + 1, 0) {}
    void add(int i, long long delta) {
        for (; i <= n; i += i & -i) bit[i] += delta;
    }
    long long sum(int i) const {
        long long s = 0;
        for (; i > 0; i -= i & -i) s += bit[i];
        return s;
    }
};

static int fastio_init = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}();

long long solve(const vi& a, int target) {
    int n = (int)a.size();
    // vals[i] = +1 if a[i] == target, else -1
    vector<int> vals(n);
    for (int i = 0; i < n; ++i) vals[i] = (a[i] == target) ? 1 : -1;

    // prefix sums P[0..n], P[0]=0
    vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + vals[i];

    // coordinate compression for prefix sums
    vector<long long> coords = pref;
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());

    auto get_idx = [&](long long x) {
        return int(lower_bound(coords.begin(), coords.end(), x) - coords.begin()) + 1; // 1-based
    };

    Fenwick fw((int)coords.size());
    // add P[0]
    fw.add(get_idx(pref[0]), 1);

    long long ans = 0;
    for (int j = 1; j <= n; ++j) {
        int idx = get_idx(pref[j]);
        // count previous i with P[i] < P[j]
        ans += fw.sum(idx - 1);
        fw.add(idx, 1);
    }
    return ans;
}

int main() {
    int n, target;
    if (!(cin >> n >> target)) {
        return 0;
    }
    vi a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    long long res = solve(a, target);
    cout << res << "\n";
    return 0;
}