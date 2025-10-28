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

void solve(vi& a, int n, int k) {
    auto check = [&](int vi) -> pii {
        vector<int> s(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            int val = (a[i] >= vi ? 1 : -1);
            s[i] = s[i - 1] + val;
        }
        int pos = 0;
        for (int i = k; i <= n; i++) {
            if (s[i - k] < s[pos]) pos = i - k;
            if (s[i] - s[pos] >= 0) {
                return {pos + 1, i};
            }
        }
        return {0, 0};
    };
    int lo = 1, hi = n, ans = 0;
    pii res = {0, 0};
    while (lo <= hi) {
        int vi = lo + (hi - lo) / 2;
        auto lr = check(vi);
        if (lr.fi > 0) {
            ans = vi;
            res = lr;
            lo = vi + 1;
        } else {
            hi = vi - 1;
        }
    }
    cout << ans << " " << res.fi << " " << res.se << endl;
}

int main() {
    int t;
    cin >> t;
    For(i, t) {
        int n, k;
        cin >> n >> k;
        vi a(n + 1);
        FOR(j, 1, n + 1) cin >> a[j];
        solve(a, n, k);
    }
    return 0;
}