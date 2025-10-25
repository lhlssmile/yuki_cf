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
const int MOD = 676767677;

int main() {
    int t;
    cin >> t;
    For(tt, t) {
        int n;
        cin >> n;
        vi a(n);
        For(i, n) cin >> a[i]; 
        
        if (n == 1) {
            cout << (a[0] == 1 ? 2 : 0) << '\n';
            continue;
        }
        
        vi s(n - 1);
        bool possible = true;
        For(i, n - 1) {
            int d = a[i] - a[i + 1];
            s[i] = 1 - d;
            if (s[i] < 0 || s[i] > 2) {
                possible = false;
            }
        }
        if (!possible) {
            cout << 0 << '\n';
            continue;
        }
        
        int ways = 0;
        For(start, 2) {  // 0 或 1
            vi x(n);
            x[0] = start;
            bool valid = true;
            For(i, n - 1) {
                int nxt_x = s[i] - x[i];
                if (nxt_x < 0 || nxt_x > 1) {
                    valid = false;
                    break;
                }
                x[i + 1] = nxt_x;
            }
            if (valid) {
                int S = 0;
                For(i, n - 1) S += x[i];
                int implied_an = 1 + S;
                if (implied_an == a[n - 1]) {
                    ways++;
                }
            }
        }
        cout << (ways % MOD) << '\n';  
    }
    return 0;
}