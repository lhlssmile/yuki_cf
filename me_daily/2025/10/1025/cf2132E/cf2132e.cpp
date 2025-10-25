
#include <bits/stdc++.h>
using namespace std;

#define ALL(v) (v).begin(), (v).end()
#define For(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
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

const int inf = 0x3f3f3f3f;
const ll infl = 0x3f3f3f3f3f3f3f3fll;
const int mod = 1e9 + 7;

int fastio_init = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();

int t, n, m, q;  // 加 q
vll a, b;  // 全局 ok
V<array<int, 3>> cc;

vll solve(int n, int m, vll& va, vll& ko, const V<array<int, 3>>& cl) {
    // team fst_ezik must choose zi cards in roundi & va cannot choose cards more than xi & ko cannot choose cards more than yi
    SORT(va); SORT(ko);
    reverse(ALL(va));
    reverse(ALL(ko));
    vll prefix_va(n + 1, 0), prefix_ko(m + 1, 0);
    For(i, n) prefix_va[i + 1] = prefix_va[i] + va[i];
    For(i, m) prefix_ko[i + 1] = prefix_ko[i] + ko[i];
    vll res;
    for (auto& query : cl) {  
        int x = query[0], y = query[1], z = query[2];
        if (z == 0) { res.pb(0); continue; }
        int L = max(0, z - y);
        int R = min(z, x);
        if (L > R) { res.pb(0); continue; }
        
        auto func = [&](int k) -> ll {
            return prefix_va[k] + prefix_ko[z - k];
        };
        
        // 三分
        int low = L, high = R;
        while (high - low >= 3) {
            int m1 = low + (high - low) / 3;
            int m2 = high - (high - low) / 3;
            if (func(m1) > func(m2)) {
                high = m2;
            } else {
                low = m1;
            }
        }
        ll mx = 0;
        for (int k = low; k <= high; ++k) {
            mx = max(mx, func(k));
        }
        res.pb(mx);
    }
    return res;  
}

int main() {
    cin >> t;
    while (t--) {
        cin >> n >> m >> q;  // 修复：一起读 n m q
        a.resize(n);  
        b.resize(m);
        For(i, n) cin >> a[i];
        For(i, m) cin >> b[i];
        cc.resize(q);  
        For(i, q) {
            cin >> cc[i][0] >> cc[i][1] >> cc[i][2];  // x y z
        }
        auto ans = solve(n, m, a, b, cc);  // 传 cc
        For(i, (int)ans.size()) cout << ans[i] << "\n";  // 修复：int cast
    }   
    return 0;
}
