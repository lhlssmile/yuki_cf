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
int t, n, q;

int main() {
    cin >> t;
    For(_, t) {
        cin >> n >> q;
        vi a(n + 1);
        a[0] = -1;
        For(i, n) {
            int idx = i + 1;
            cin>>a[idx];
        }
        vi sum_0(n + 1, 0), sum_1(n + 1, 0);
        vi diff(n + 1, 0);
        For (i, n) {
            int idx = i + 1;
            sum_0[idx] = sum_0[idx - 1] + (a[idx] == 0);
            sum_1[idx] = sum_1[idx - 1] + (a[idx] == 1);
            int d = (a[idx] != a[idx - 1]);
            diff[idx] = diff[idx - 1] + d;
        }
        For(i, q) {
            int l, r; cin >> l >> r;
            int z = sum_0[r] - sum_0[l - 1];
            int o = sum_1[r] - sum_1[l - 1];
            if (z % 3 || o % 3) {
                cout << -1 << "\n";
                continue;
            }
            int ans = z / 3 + o /3;
            int num_pairs = r- l;
            int switches = diff[r] - diff[l];
            if (num_pairs == switches) ans++;
            cout << ans << "\n";
        }
    }    
    return 0;
}
