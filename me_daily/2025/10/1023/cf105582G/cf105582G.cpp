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
using umplli = unordered_map<ll, int>;
const int inf = 0x3f3f3f3f;
const ll infl = 0x3f3f3f3f3f3f3f3fll;
const int mod = 1e9 + 7;

int fastio_init = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    int k1 = n / 2, k2 = n - k1;
    vi v1(k1), v2(k2);
    For(i, k1) {
        int m, t;
        cin >> m >> t;
        //：直接 m*b - t*a
        v1[i] = (ll)m * b - (ll)t * a;  
    }
    For(i, k2) {
        int m, t;
        cin >> m >> t;
        v2[i] = (ll)m * b - (ll)t * a;
    }
    umplli mp;
    For(mask, 1 << k1) {
        ll val = 0;
        For(j, k1) {
            if (mask & (1 << j)) {
                val += v1[j];
            }
        }
        mp[val]++;
    }
    ll ans = 0;

    For(mask, 1 << k2) {
        ll val = 0;
        For(j, k2) {
            if (mask & (1 << j)) {
                val += v2[j];
            }
        }
        auto it = mp.find(-val);
        if (it != mp.end()) {
            ans += it->second;
        }
    }
    cout << ans - 1 << "\n";
    return 0;
}