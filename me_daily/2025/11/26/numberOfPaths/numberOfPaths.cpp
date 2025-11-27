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
using pii = pair<int,int>;
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
    int m,n,k;cin>>m>>n>>k; V grid(m, vi(n,0));
    For(i, m) For(j, n) cin>>grid[i][j];   
    V<V<vi>> f(m + 1, V<vi>(n+1,vi(k+1, 0)));
    f[0][1][0] = 1;
    For(i, m) {
        For(j, n) {
            For(s, k) {
                int new_s = (s + grid[i][j]) % k;
                f[i+1][j+1][s] = (f[i+1][j][new_s] +f[i][j+1][new_s]) %mod;
            }
        }
    }
    cout<<f[m][n][0]<<"\n";
    return 0;
}