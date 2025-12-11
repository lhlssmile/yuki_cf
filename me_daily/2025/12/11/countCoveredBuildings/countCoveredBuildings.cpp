#include <bits/stdc++.h>
using namespace std;

#define ALL(v) (v).begin(), (v).end()
#define For(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define Rof(i, n) for (int i = (n) - 1; i >= 0; --i)
#define ROF(i, a, b) for (int i = (b) - 1; i >= (a); --i)
#define EACH(x, v) for (auto& x : (v))
#define pb push_back
#define fi first
#define se second
#define V vector
#define SORT(v) sort(ALL(v))

using umpii = unordered_map<int, int>;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vs = vector<string>;

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
    int n, m;
    cin >> n >> m;
    V<pii> b(m);
    For(i, m) {
        int x, y;
        cin >> x >> y;
        b[i] = {x, y};
    }
    
    // 初始化 min/max：行 x 的 y_min/y_max，列 y 的 x_min/x_max
    V<int> row_min(n + 2, inf), row_max(n + 2, -inf);
    V<int> col_min(n + 2, inf), col_max(n + 2, -inf);
    EACH(a, b) {
        int x = a.fi, y = a.se;
        row_min[x] = min(row_min[x], y);
        row_max[x] = max(row_max[x], y);
        col_min[y] = min(col_min[y], x);
        col_max[y] = max(col_max[y], x);
    }
    
    int ans = 0;
    EACH(a, b) {
        int x = a.fi, y = a.se;
        // 可选：边界直接 skip
        if (x == 1 || x == n || y == 1 || y == n) continue;
        
        // 检查：行内 min_y < y && max_y > y，且列内 min_x < x && max_x > x
        if (row_min[x] < y && row_max[x] > y &&
            col_min[y] < x && col_max[y] > x) {
            ans++;
        }
    }
    cout << ans << "\n";
    return 0;
}