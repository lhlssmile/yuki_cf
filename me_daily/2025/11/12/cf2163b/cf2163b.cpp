#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i=(a); i<=(b); ++i)
using vi = vector<int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vi p(n + 1);
        int mn = 1, mx = 1;
        FOR(i,1,n) {
            cin >> p[i];
            if (p[i] < p[mn]) mn = i;
            if (p[i] > p[mx]) mx = i;
        }
        string x; cin >> x;
        x = " " + x; // 1-based
        
        if (x[1] == '1' || x[n] == '1') {
            cout << -1 << "\n";
            continue;
        }
        if (x[mn] == '1' || x[mx] == '1') {
            cout << -1 << "\n";
            continue;
        }

        cout << 5 << "\n";
        cout << 1 << " " << mn << "\n";
        cout << 1 << " " << mx << "\n";
        cout << mn << " " << n << "\n";
        cout << mx << " " << n << "\n";
        cout << min(mn, mx) << " " << max(mn, mx) << "\n";
    }
    return 0;
}
