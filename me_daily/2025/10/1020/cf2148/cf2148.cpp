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

int t, n;
vll a;

ll solve(vll& a) {
    vll odds, evens;
    ll sum_e = 0;
    for (auto x : a) {
        if (x % 2 == 0) {
            evens.pb(x);
            sum_e += x;
        } else {
            odds.pb(x);
        }
    }
    int k = odds.size();
    if (k == 0) return 0;
    SORT(odds);  // 升序，小的在前好牺牲
    ll sum_o = 0;
    for (auto x : odds) sum_o += x;
    int sac = k / 2;  // floor(k/2)
    ll sum_sac = 0;
    For(i, sac) sum_sac += odds[i];
    return sum_o - sum_sac + sum_e;
}

int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        a.resize(n); 
        For(i, n) cin >> a[i];
        ll ans = solve(a);
        cout << ans << "\n";
    }
    return 0;
}
