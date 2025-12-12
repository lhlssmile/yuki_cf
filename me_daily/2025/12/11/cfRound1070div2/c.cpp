#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vll a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        vll odd, even;
        for (auto x : a) {
            if (x & 1) odd.push_back(x);
            else even.push_back(x);
        }

        if (odd.empty()) {
            for (int i = 0; i < n; i++) cout << 0 << " ";
            cout << "\n";
            continue;
        }

        sort(even.begin(), even.end(), greater<ll>());
        int m = even.size();

        vll pre(m + 1, 0);
        for (int i = 0; i < m; i++) pre[i + 1] = pre[i] + even[i];

        ll mx_odd = *max_element(odd.begin(), odd.end());
        int o_p = odd.size() - 1;

        vll ans;

        for (int k = 1; k <= n; k++) {

            int L = max(0, k - 1 - m);
            int mx_ef = min(k - 1, m);

            int ef = -1;

            if (L % 2 == 0) {
                ef = mx_ef;
            } else {
                if (mx_ef - 1 < 0 || o_p <= L)
                    ef = -1;
                else
                    ef = mx_ef - 1;
            }

            if (ef == -1) ans.push_back(0);
            else ans.push_back(mx_odd + pre[ef]);
        }

        for (auto x : ans) cout << x << " ";
        cout << "\n";
    }
}
