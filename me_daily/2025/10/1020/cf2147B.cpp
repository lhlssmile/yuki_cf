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
int t, n;
vi solve(int n) {
    vi res(2 * n, 0);
    For(i, n) res[i] = n - i;
    for (int x = n; x >= 1; --x) {
        for (int j = n; j < 2 * n; j += x) {
            if (res[j] == 0) {
                res[j] = x;
                break;
            }
        }
    }
    return res;
}

int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        vi res = solve(n);
        For(i, 2 * n) {
            cout << res[i] << (i + 1 < 2 * n ? " " : "\n");
        }
    }
    return 0;
}