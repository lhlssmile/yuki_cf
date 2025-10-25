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

void solve(int h, int w, const vector<vector<char>>& a) {
    int total = 0;
    For(i, h) For(j, w) if (a[i][j] == '#') total++;
    if (total == 0) {
        cout << 0 << endl;
        return;
    }
    vector<vector<int>> prefix(h + 1, vector<int>(w + 1, 0));
    For(i, h) FOR(j, 0, w) {
        int val = (a[i][j] == '#' ? 1 : 0);
        prefix[i + 1][j + 1] = prefix[i][j + 1] + prefix[i + 1][j] - prefix[i][j] + val;
    }
    auto rect_sum = [&](int r1, int c1, int r2, int c2) -> int {
        return prefix[r2][c2] - prefix[r2][c1 - 1] - prefix[r1 - 1][c2] + prefix[r1 - 1][c1 - 1];
    };
    vector<ll> divs;
    for (ll i = 1; i * i <= total; ++i) {
        if (total % i == 0) {
            divs.pb(i);
            if (i != total / i) divs.pb(total / i);
        }
    }
    SORT(divs);
    vector<int> poss_s;
    int mn = min(h, w);
    for (auto d : divs) {
        double sqd = sqrt((double)d);
        ll sq = (ll)(sqd + 0.5);
        if (sq * sq == d && sq >= 1 && sq <= mn) {
            poss_s.pb((int)sq);
        }
    }
    SORT(poss_s);
    reverse(ALL(poss_s));
    auto can_tile = [&](int s) -> bool {
        vector<vector<char>> covered(h, vector<char>(w, 0));
        For(i, h) {
            For(j, w) {
                if (a[i][j] != '#' || covered[i][j]) continue;
                if (i + s > h || j + s > w) return false;
                int r1 = i + 1, c1 = j + 1, r2 = i + s, c2 = j + s;
                if (rect_sum(r1, c1, r2, c2) != s * s) return false;
                bool ok = true;
                For(di, s) {
                    if (!ok) break;
                    For(dj, s) {
                        if (covered[i + di][j + dj]) {
                            ok = false;
                            break;
                        }
                    }
                }
                if (!ok) return false;
                For(di, s) For(dj, s) covered[i + di][j + dj] = 1;
            }
        }
        return true;
    };
    for (int s : poss_s) {
        if (can_tile(s)) {
            cout << s << endl;
            return;
        }
    }
    cout << 1 << endl;
}

int main() {
    int h, w;
    cin >> h >> w;
    V<V<char>> a(h, V<char>(w));
    For(i, h) For (j, w) cin >> a[i][j];
    solve(h, w, a);
    return 0;
}