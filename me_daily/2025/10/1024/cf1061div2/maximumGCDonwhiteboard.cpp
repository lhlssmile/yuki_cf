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

int main() {
    int t;
    cin >> t;
    For(_t, t) {
        int n, k;
        cin >> n >> k;
        vi a(n);
        For(i, n) cin >> a[i];
        int maxn = *max_element(ALL(a));
        vector<int> freq(n+1, 0);
        For(i, n) {
            freq[a[i]]++;
        }
        vector<int> prefix(n+1, 0);
        FOR(i, 1, n+1) {
            prefix[i] = prefix[i-1] + freq[i];
        }
        int ans = 1;
        for (int d = n; d >= 1; --d) {
            ll up = min((ll)n, 4LL * d - 1);
            int num_small = prefix[(int)up];
            int num_small_good = 0;
            for (int m = 1; m <= 3; ++m) {
                ll val = (ll)m * d;
                if (val > n) break;
                num_small_good += freq[(int)val];
            }
            int cost = num_small - num_small_good;
            if (cost <= k) {
                ans = d;
                break;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}