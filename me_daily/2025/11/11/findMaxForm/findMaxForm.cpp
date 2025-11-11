#include <bits/stdc++.h>
using namespace std;

#define ALL(v) (v).begin(), (v).end()
#define For(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define ROF(i, a, b) for (int i = (b) - 1; i >= (a); --i)
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
    int x, m, n;
    cin >> x >> m >> n;
    V<string> s;
    For(_, x) {
        string si;
        cin >> si;
        s.pb(si);
    }   
    V f(m + 1, vi(n + 1, 0));
    for (auto& si : s) {
        int z = count(ALL(si), '0');
        int o = count(ALL(si), '1');
        ROF(i, z - 1, m) {
            ROF(j, o - 1, n) {
                f[i][j] = max(f[i][j], f[i - z][j - o] + 1);
            }
        }
    } 
    print("{}\n", f[m][n]);
    return 0;
}