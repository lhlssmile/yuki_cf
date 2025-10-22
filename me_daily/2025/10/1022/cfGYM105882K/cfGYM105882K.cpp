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
int n;
int main() {
    cin >> n;

    V<pii> xy;
    if (n & 1) {
        xy.pb({0, 0});
        int x = 0, y = 0;
        for (int i = 0; i < n / 2 - 1; i++) {
            y += 25;
            xy.pb({x, y});
            x += 25;
            xy.pb({x, y});
        }
        x = max(x, 25);
        xy.emplace_back(x, 0);
        xy.emplace_back(x / 25 * 9, -x / 25 * 12);
    }else {
        xy.pb({0, 0});
        int x = 0, y = 0;
        for (int i = 0; i < n / 2 - 1; i++) {
            y += 25;
            xy.pb({x, y});
            x += 25;
            xy.pb({x, y});

        }
        xy.pb({x, 0});

    }
    int dx = 5, dy = 12;
    for (auto& [x, y] : xy) {
        cout << x * dx + y * dy << ' ' << x * (-dy) + y * dx << '\n';
    }
    return 0;
}