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
ll cost2(ll x, ll y) {
    return abs(x - y);
}
ll cost3(ll x, ll y, ll z) {
    array<ll, 3> a = {x, y, z};
    SORT(a);
    return abs(a[1] - a[0]) + abs(a[2] - a[1]);
}
ll solve(vll& re) {
    vll f(re.size() + 1, infl);
    f[0] = 0;
    FOR(i, 2, re.size() + 1) {
        f[i] = min(f[i], f[i - 2] + cost2(re[i - 2], re[i - 1]));
        if (i >= 3) {
            f[i] = min(f[i], f[i - 3] + cost3(re[i - 3], re[i - 2], re[i - 1]));
        }
    }
    return f[re.size()];
}
int main() {
    int t, n;
    cin >> t;
    For(_, t) {
        cin >>n; vll a(n);
        For(i, n) cin>>a[i];
        ll ans = infl;
        For(cut, 3) {
            if (cut >= n) continue;
            vll re(n);
            For(i, n) {
                re[i] = a[(i + cut) % n];
            }
            auto res = solve(re);
            ans = min(ans, res);
        }
        cout << ans << "\n";
    }   
    return 0;
}