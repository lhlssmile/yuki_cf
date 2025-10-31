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
    For(i, t) {
        int n;
        ll x;
        cin >> n >> x;
        vll a(n);
        For(j, n) cin >> a[j];
        ll sum = accumulate(ALL(a), 0LL);
        int levels = sum / x;
        SORT(a);
        reverse(ALL(a));
        ll bonus = accumulate(a.begin(), a.begin() + levels, 0LL);
        vll small(a.begin() + levels, a.end());
        vll res;
        ll cur_s = 0;
        int large_idx = 0;
        For(level, levels) {
            ll target = (ll)(level + 1) * x;
            while (cur_s < target - a[large_idx] && !small.empty()) {
                ll item = small.back();
                small.pop_back();
                res.pb(item);
                cur_s += item;
            }
            res.pb(a[large_idx]);
            cur_s += a[large_idx];
            large_idx++;
        }
        For(j, small.size()) {
            res.pb(small[j]);
        }
        cout << bonus << "\n";
        For(j, res.size()) {
            cout << res[j];
            if (j < (int)res.size() - 1) cout << " ";
            else cout << "\n";
        }
    }
    return 0;
}