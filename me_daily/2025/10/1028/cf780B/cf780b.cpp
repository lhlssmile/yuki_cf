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

bool possible(double t, const vll& x, const vll& v) {
    double lmx = -1e18;
    double rmx = 1e18;
    int n = x.size();
    For(i, n) {
        double left = x[i] - v[i] * t;
        double right = x[i] + v[i] * t;
        lmx = max(lmx, left);
        rmx = min(rmx, right);
    }
    return lmx <= rmx;
}

int main() {
    int n; cin >> n;
    vll x(n), v(n);
    For(i, n) cin >> x[i];
    For(i, n) cin >> v[i];
    
    double lo = 0.0, hi = 2e9;
    FOR(i, 0, 100) {
        double mid = (lo + hi) / 2;
        if (possible(mid, x, v)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    cout << fixed << setprecision(12) << lo << '\n';
    return 0;
}