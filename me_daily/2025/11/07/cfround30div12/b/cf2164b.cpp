#include <bits/stdc++.h>
using namespace std;
#define ALL(v) (v).begin(), (v).end()
#define For(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define pb push_back
using pii = pair<int,int>;
using vi = vector<int>;

const int fastio_init = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}();

pii find_odd_pairs(vi& odd) {
    int m = odd.size();
    if (m < 2) return {0, 0};
    
    // 检查相邻奇数
    for (int i = 0; i < m - 1; ++i) {
        int x = odd[i], y = odd[i + 1];
        if (y < 2 * x) return {x, y};
    }
    // 暴力
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            int x = odd[i], y = odd[j];
            if ((y % x) % 2 == 0)
                return {x, y};
        }
    }
    return {0, 0};
}

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vi odd, even;
        For(i, n) {
            int x; cin >> x;
            if (x & 1) odd.pb(x);
            else even.pb(x);
        }

        if (even.size() >= 2) {
            cout << even[0] << " " << even[1] << "\n";
            continue;
        }

        auto p = find_odd_pairs(odd);
        if (p.first != 0 || p.second != 0) {
            cout << p.first << " " << p.second << "\n";
            continue;
        }

        if (even.empty()) {
            cout << -1 << "\n";
            continue;
        }
        int e = even[0];
        vi small_odd;
        for (int x : odd) if (x < e) small_odd.pb(x);

        bool found = false;
        for (int x : small_odd) {
            if ((e % x) % 2 == 0) {
                cout << x << " " << e << "\n";
                // print("{} {}\n", x, e);
                found = true;
                break;
            }
        }
        if (!found) cout << -1 << "\n";
    }
    return 0;
}
