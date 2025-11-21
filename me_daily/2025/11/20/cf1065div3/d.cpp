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
    int t, n; cin >> t;
    while (t--) {
        cin >> n;
        vi a(n), b(n);
        For(i, n) cin >> a[i];
        For(i, n) cin >> b[i];
        ll S = 0;
        For(i, n) S ^= (a[i] ^ b[i]);  // 或 S ^= (ll(a[i]) ^ b[i]); 确保类型
        if (S == 0) {
            cout << "Tie\n";
            continue;
        }
        int l = __builtin_clzll(S);  
        // cout << S << l << "\n";
        int bitpos = 63 - l;         
        ll mask = 1LL << bitpos;    
        int last = -1;
        For(i, n) {
            if ((a[i] ^ b[i]) & mask) {  
                last = i + 1;
            }
        }
        if (last & 1) {
            cout << "Ajisai\n";
        } else {
            cout << "Mai\n";
        }
    }
    return 0;
}