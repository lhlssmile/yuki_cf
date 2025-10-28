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

bool check(ll r, ll x, const vll& a, int n, int kk) {
    ll d = (r == 0 ? -1LL : r - 1);
    ll cov = 0;
    int i = 0;
    while (i < n) {
        ll st = max(0LL, a[i] - d);
        ll en = min(x, a[i] + d);
        if (st > en) {
            i++;
            continue;
        }
        ll cur_en = en;
        i++;
        while (i < n && a[i] - d <= cur_en) {
            cur_en = max(cur_en, a[i] + d);
            i++;
        }
        cur_en = min(x, cur_en);
        cov += cur_en - st + 1;
    }
    ll tot = x + 1;
    return tot - cov >= (ll)kk;
}

int main() {
    int t;
    cin >> t;
    For(_, t) {
        int n, k;
        ll x;
        cin >> n >> k >> x;
        vll a(n);
        For(i, n) cin >> a[i];
        SORT(a);
        ll low = 0, high = x + 1;
        while (low < high) {
            ll mid = low + (high - low + 1) / 2;
            if (check(mid, x, a, n, k)) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        ll r = low;
        // build forb
        vll forb_st, forb_en;
        ll d = (r == 0 ? -1LL : r - 1);
        int i = 0;
        while (i < n) {
            ll st = max(0LL, a[i] - d);
            ll en = min(x, a[i] + d);
            if (st > en) {
                i++;
                continue;
            }
            ll cur_en = en;
            i++;
            while (i < n && a[i] - d <= cur_en) {
                cur_en = max(cur_en, a[i] + d);
                i++;
            }
            cur_en = min(x, cur_en);
            forb_st.pb(st);
            forb_en.pb(cur_en);
        }
        int m = forb_st.size();
        // safes
        vector<pair<ll, ll>> safes;
        ll prev_end = -1;
        For(j, m) {
            ll f_st = forb_st[j];
            ll f_en = forb_en[j];
            ll gst = prev_end + 1;
            ll gen = f_st - 1;
            if (gst <= gen) {
                safes.pb({gst, gen});
            }
            prev_end = f_en;
        }
        ll gst = prev_end + 1;
        ll gen = x;
        if (gst <= gen) {
            safes.pb({gst, gen});
        }
        // pick
        vll ans;
        ll need = k;
        for (auto& s : safes) {
            ll st = s.fi;
            ll en = s.se;
            ll av = en - st + 1;
            if (av >= need) {
                For(jj, need) {
                    ans.pb(st + jj);
                }
                need = 0;
                break;
            } else {
                For(jj, av) {
                    ans.pb(st + jj);
                }
                need -= av;
            }
        }
        // output
        For(j, k) {
            if (j > 0) cout << " ";
            cout << ans[j];
        }
        cout << '\n';
    }
    return 0;
}