// Sum Over Subsets (SOS DP) 模板
// 解决：给定大小为 n 的集合所有子集上的函数 f，计算 g(S) = Σ_{T ⊆ S} f(T)
// 用法：
// 1) 将每个子集用长度为 n 的 0/1 位串表示为 mask，0..(1<<n)-1。
// 2) 准备数组 f[0..(1<<n)-1]，其中 f[mask] 是子集 mask 的函数值。
// 3) 调用 sos_sum_subsets(f, n) 返回 g 数组，满足 g[mask] = Σ_{sub ⊆ mask} f[sub]。
// 复杂度：O(n * 2^n)。空间：O(2^n)。

#include <bits/stdc++.h>
using namespace std;

// g[mask] = Σ f[sub] (sub ⊆ mask)
vector<long long> sos_sum_subsets(vector<long long> f, int n) {
    int N = 1 << n;
    vector<long long> g = f;
    for (int i = 0; i < n; ++i) {
        for (int mask = 0; mask < N; ++mask) {
            if (mask & (1 << i)) {
                g[mask] += g[mask ^ (1 << i)];
            }
        }
    }
    return g;
}

// 变体：g[mask] = Σ f[sup] (mask ⊆ sup) ——对子集的所有超集求和
// 将转移方向改为从低位向高位“加一位”。
vector<long long> sos_sum_supersets(vector<long long> f, int n) {
    int N = 1 << n;
    vector<long long> g = f;
    for (int i = 0; i < n; ++i) {
        for (int mask = 0; mask < N; ++mask) {
            if ((mask & (1 << i)) == 0) {
                g[mask] += g[mask | (1 << i)];
            }
        }
    }
    return g;
}

// 示例：读取 n 与 f，输出 g（对子集求和）
// 输入：
// n
// f[0] f[1] ... f[(1<<n)-1]
// 输出：
// g[0..(1<<n)-1]
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    if (!(cin >> n)) return 0;
    int N = 1 << n;
    vector<long long> f(N);
    for (int i = 0; i < N; ++i) cin >> f[i];

    auto g = sos_sum_subsets(f, n);
    for (int i = 0; i < N; ++i) {
        if (i) cout << ' ';
        cout << g[i];
    }
    cout << '\n';
    return 0;
}




using namespace std;
#define For(i, n) for (int i = 0; i < (n); ++i)
using ll = long long;
const int N = 20;
const int MAX = 1 << N;
ll f[MAX], dp[MAX];

void SOS_DP (int n) {
    For(i, MAX) dp[i] = f[i];

    For(i, n) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (mask &( 1 << i)) {
                dp[mask] += dp[mask ^ (1 << i)];
            }
        }
    }
}