#include <bits/stdc++.h>
using namespace std;
#include <print>
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
int n, m;
int main() {
    cin >> n >> m;
    V grid(n, vi(m, 0));
    For(i, n) {
        For(j, m) {
            int x; cin >> x;
            grid[i][j] = x;
        }
    }
    V prefix(n + 1, vi(m + 1, 0));
    FOR(i, 1, n + 1) {
        FOR(j, 1, m + 1) {
            prefix[i][j] = prefix[i][j - 1] + prefix[i - 1][j] - prefix[i - 1][j - 1] + grid[i - 1][j - 1];
        }
    }
    auto sub_sqaure_sum = [&](int x, int y, int k) -> int {
        int x2 = x + k, y2 = y + k;
        return prefix[x2][y2] + prefix[x][y] - prefix[x2][y] - prefix[x][y2];
    };
    int ans = 1;
    for (int k = min(m, n); k > 0; k--) {
        bool found = false;
        For(i, n - k + 1) {
            For(j, m - k + 1){
                if (sub_sqaure_sum(i, j, k) == k * k) {
                    found = true;ans = k;
                    break;
                } 
            }
            if (found) break;
        }
        if (found) break;
    }
    cout << ans << "\n";
    return 0;
}