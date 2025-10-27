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
const int MAX = 1000001;
int main() {
    int n;cin>>n;
    V<bool> exist(MAX, false);
    vi f(MAX, 0);
    int ans = 1;
    vi a(n, 0);
    For(i, n) {
        cin >> a[i];
        exist[a[i]] = true;
    }
    FOR(x, 1, MAX) {
        if (!exist[x]) continue;
        f[x] = max(f[x], 1);
        for (int y = x * 2; y < MAX; y += x) {
            if (exist[y]) f[y] = max(f[y], f[x] + 1);
        }
        ans = max(ans, f[x]);
    }
    cout << ans << "\n";
    
    return 0;
}