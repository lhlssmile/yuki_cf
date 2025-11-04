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
const int MAXN = 200'005;
int t, n; int a[MAXN];
map<int, int> cnt;
int main() {
    cin >> t;
    For(_, t) {
        cnt.clear();
        cin >> n;
        For(i, n) cin >> a[i];
        For(i, n) cnt[a[i]]++;
        vi odd, even;
        ll base = 0;
        for (auto& [x, c] : cnt) {
            base += (ll)x * (c / 2);
            if (c & 1) odd.pb(x);
            else if(c >= 2) even.pb(x);
        }
        if (base == 0) {cout << 0 << "\n"; continue;};
        ll ans = 0;
        for (auto x : odd) if (base * 2 > x) ans = max(ans, base * 2 + x);
        assert(is_sorted(ALL(odd)));
        FOR(i, 1, odd.size()) if (odd[i - 1] + 2 * base > odd[i]) ans = max(ans, odd[i - 1] + 2 *base + odd[i]);
        
        for (auto x : even) if (base -x > 0) ans = max(ans, 2 * base);
        cout << ans << "\n";
    }
    return 0;
}