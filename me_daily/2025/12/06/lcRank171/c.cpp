#include <bits/stdc++.h>
using namespace std;

#define ALL(v) (v).begin(), (v).end()
#define For(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define Rof(i, n) for (int i = (n) - 1; i >= 0; --i)
#define ROF(i, a, b) for (int i = (b) - 1; i >= (a); --i)
#define EACH(x, v) for (auto& x : (v))
#define pb push_back
#define fi first
#define se second
#define V vector
#define SORT(v) sort(ALL(v))

using umpii = unordered_map<int, int>;
using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vll = vector<ll>;
using vs = vector<string>;

const int inf = 0x3f3f3f3f;
const ll infl = 0x3f3f3f3f3f3f3f3fll;
const int mod = 1e9 + 7;

int fastio_init = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();

class FenwickTree {
private:
    vi tree;
    int n;
public:
    FenwickTree(int _n) {
        n = _n;
        tree.assign(n + 2, 0);
    }
    void update(int idx, int delta) {
        while (idx <= n) {
            tree[idx] += delta;
            idx += idx & -idx;
        }
    }
    int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & -idx;
        }
        return sum;
    }
    int query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

int main() {
    int n, k;
    cin >> n >> k;
    vi nums(n);
    For(i, n) cin >> nums[i];

    vi all_vals = nums;
    SORT(all_vals);
    auto it = unique(ALL(all_vals));
    all_vals.resize(distance(all_vals.begin(), it));
    int m = all_vals.size();

    vi ranks(n);
    For(i, n) {
        ranks[i] = lower_bound(ALL(all_vals), nums[i]) - all_vals.begin() + 1;
    }

    FenwickTree ft(m);

    ll inv = 0;
    For(i, k) {
        int rnk = ranks[i];
        inv += ft.query(rnk + 1, m);
        ft.update(rnk, 1);
    }

    ll min_inv = inv;

    For(start, n - k) {
        // remove left: nums[start]
        int lrnk = ranks[start];
        inv -= ft.query(1, lrnk - 1);
        ft.update(lrnk, -1);

        // add right: nums[start + k]
        int rrnk = ranks[start + k];
        inv += ft.query(rrnk + 1, m);
        ft.update(rrnk, 1);

        min_inv = min(min_inv, inv);
    }


    cout << min_inv << endl;
    return 0;
}