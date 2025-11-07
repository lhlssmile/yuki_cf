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
int t, n, x;
int main() {
    cin >> t;
    while (t--) {
        cin >>n; vll a(n);
        ll mx = LLONG_MIN, mn = LLONG_MAX;
        For(i, n) {
            cin >>a[i];
            mx = max(mx, a[i]);
            mn = min(mn, a[i]);
        };
        cin >> x;
        if (x >= mn && x <= mx) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}