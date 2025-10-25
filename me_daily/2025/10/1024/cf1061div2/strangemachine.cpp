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

int t, n, q;
string s;
vi queries;

V<ll> solve(int n, string& a, vi& q) {
    bool allA = true;
    for (char c : a) if (c == 'B') { allA = false; break; }

    V<ll> res;
    res.reserve(q.size());

    if (allA) {
        for (int x : q) res.pb(1LL * x);
        return res;
    }

    vi chain(n, 0);
    for (int i = 0; i < n; ++i) {
        if (a[i] != 'A') continue;
        int len = 0;
        int p = i;
        while (len < n && a[p] == 'A') {
            ++len;
            p = (p + 1) % n;
        }
        chain[i] = len;
    }

    for (int qq : q) {
        ll x = qq;
        ll steps = 0;
        int pos = 0;
        while (x > 0) {
            if (a[pos] == 'B') {
                x /= 2;
                ++steps;
                if (x == 0) break;
                pos = (pos + 1) % n;
            } else {
                ll clen = chain[pos];
                if (x <= clen) {
                    steps += x;
                    x = 0;
                    break;
                } else {
                    steps += clen;
                    x -= clen;
                    pos = (pos + (int)clen) % n;
                }
            }
        }
        res.pb(steps);
    }
    return res;
}

int main() {
    cin >> t;
    while (t--) {
        cin >> n >> q;
        cin >> s;
        queries.resize(q);
        For(i, q) cin >> queries[i];
        auto ans = solve(n, s, queries);
        for (auto v : ans) cout << v << "\n";
    }
    return 0;
}